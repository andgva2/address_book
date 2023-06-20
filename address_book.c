#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "liblinkedlist.c"
#define DELIMETER ","

struct Address {
	char name[30];
	char surname[30];
	char email[50];
	char phone[30];
};

void load_default_addresses(List *list);
void load_addresses(FILE *file, List *list);
struct Address *create_address_from_csv_line(char *address_line);
void free_list_addresses(List *list);
void free_address(struct Address *address);
int compare_addresses(void *data1, void *data2);
void print_address(void *data, int position);
void print_menu();

int main()
{
	List *address_list = create_list();
	load_default_addresses(address_list);
	int running = 1;
	printf("Welcome to the address book\n\n");
	while (running) {
		char user_input[1];
		printf("\nOptions menu:\n");
		print_menu();
		printf("Enter your choice: ");
		scanf("%s", user_input);
		switch (user_input[0]) {
		case '1':
			printf("\n***Displaying all records***\n");
			print_list_by(address_list, print_address);
			break;
		case '2':
			printf("\n***Adding new address***\n");
			struct Address *new_address = (struct Address *)malloc(sizeof(struct Address));
			printf("Enter name: ");
			scanf("%s", new_address->name);
			printf("Enter surname: ");
			scanf("%s", new_address->surname);
			printf("Enter email: ");
			scanf("%s", new_address->email);
			printf("Enter phone: ");
			scanf("%s", new_address->phone);
			add_to_list_end(address_list, new_address);
			break;
		case '3':
			printf("\n***Adding new address at specified position_add***\n");
			printf("Enter position_add: ");
			int position_add;
			scanf("%d", &position_add);
			if (position_add < 1 || position_add > address_list->size + 1) {
				printf("\n***Invalid position_add***\n");
				break;
			}
			struct Address *new_address_at = (struct Address *)malloc(sizeof(struct Address));
			printf("Enter name: ");
			scanf("%s", new_address_at->name);
			printf("Enter surname: ");
			scanf("%s", new_address_at->surname);
			printf("Enter email: ");
			scanf("%s", new_address_at->email);
			printf("Enter phone: ");
			scanf("%s", new_address_at->phone);
			add_to_list_at(address_list, new_address_at, position_add);
			break;
		case '4':
			printf("\n***Deleting address from specified position***\n");
			printf("Enter position: ");
			int position_delete;
			scanf("%d", &position_delete);
			if (position_delete < 1 || position_delete > address_list->size) {
				printf("\n***Invalid position***\n");
				break;
			}
			free_address(remove_from_list_at(address_list, position_delete));
			break;
		case '5':
			printf("\n***Deleting whole address book***\n");
			free_list_addresses(address_list);
			remove_all_from_list(address_list);
			break;
		case '6':
			printf("\n***Finding address by position***\n");
			printf("Enter position: ");
			int position_find;
			scanf("%d", &position_find);
			if (position_find < 1 || position_find > address_list->size) {
				printf("\n***Invalid position***\n");
				break;
			}
			struct Address *address_find = (struct Address *)get_from_list_at(address_list, position_find);
			printf("Name: %s\n", address_find->name);
			printf("Surname: %s\n", address_find->surname);
			printf("Email: %s\n", address_find->email);
			printf("Phone: %s\n", address_find->phone);
			break;
		case '7':
		// TODO: Fix user input, accept empty inputs. Enter name autoenters??
			printf("\n***Finding address by name, surname, email or phone number***\n");
			printf("Enter information or leave it empty:\n");
			struct Address *search_address = (struct Address *)malloc(sizeof(struct Address));
			printf("Enter name: \n");
			char *name;			
			fgets (name, 30, stdin);
			name[strlen(name) - 1] = '\0';
			strcpy(search_address->name, name);
			printf("Enter surname: ");
			char *surname;
			fgets (surname, 30, stdin);
			surname[strlen(surname) - 1] = '\0';
			strcpy(search_address->surname, surname);
			printf("Enter email: ");
			char *email;
			fgets (email, 50, stdin);
			email[strlen(email) - 1] = '\0';
			strcpy(search_address->email, email);
			printf("Enter phone: ");
			char *phone;
			fgets (phone, 30, stdin);
			phone[strlen(phone) - 1] = '\0';
			strcpy(search_address->phone, phone);
			print_address(search_address, 0);		
			List *found_addresses = get_sublist_by(address_list, search_address, compare_addresses);
			if (found_addresses->size == 0) {
				printf("\n***No addresses found***\n");
				break;
			} else {
				printf("\n***Found addresses***\n");
				print_list_by(found_addresses, print_address);
			}
			free_list(found_addresses);
			break;
		case '8':
			printf("\n***Exiting***\n");
			running = 0;
			break;

		default:
			printf("\n***Invalid input***\n");
			break;
		}
	}

	free_list_addresses(address_list);
	free_list(address_list);
	return 0;
}

void print_menu()
{
	printf("\n1. \tDisplay all records in the address book\n");
	printf("2. \tAdd new address to the book\n");
	printf("3. \tAdd new address at specified position\n");
	printf("4. \tDelete address from specified position\n");
	printf("5. \tDelete whole address book\n");
	printf("6. \tFind address by position\n");
	printf("7. \tFind address by name, surname, email or phone number\n");
	printf("8. \tExit\n\n");
}

void load_default_addresses(List *list)
{
	char *address_file_path = "";
	char *file_name		= "/addresses.csv";
	address_file_path	= malloc(strlen(getenv("HOME")) + strlen(file_name) + 1);
	strcpy(address_file_path, getenv("HOME"));
	strcat(address_file_path, file_name);
	FILE *address_file = NULL;
	address_file	   = fopen(address_file_path, "r");
	if (address_file == NULL) {
		fprintf(stderr, "WARNING:\n");
		fprintf(stderr, "There was a problem opening %s\n", address_file_path);
		free(address_file_path);
	} else {
		load_addresses(address_file, list);
		fclose(address_file);
		free(address_file_path);
	}
}

void load_addresses(FILE *file, List *list)
{
	char line[128];
	while (fgets(line, sizeof(line), file)) {
		if (strcmp(line, "\n") == 0) {
			continue;
		}
		struct Address *address = NULL;
		address			= create_address_from_csv_line(line);
		if (address != NULL) {
			add_to_list_end(list, address);
		}
	}
}

struct Address *create_address_from_csv_line(char *address_line)
{
	struct Address *address = NULL;
	address			= malloc(sizeof(struct Address));
	char name[30];
	char surname[30];
	char email[50];
	char phone[30];
	strcpy(name, strtok(address_line, DELIMETER));
	strcpy(surname, strtok(NULL, DELIMETER));
	strcpy(email, strtok(NULL, DELIMETER));
	strcpy(phone, strtok(NULL, DELIMETER));
	phone[strcspn(phone, "\n")] = 0;
	if (address != NULL) {
		strcpy(address->name, name);
		strcpy(address->surname, surname);
		strcpy(address->email, email);
		strcpy(address->phone, phone);
	}
	return address;
}

void free_list_addresses(List *list)
{
	struct Address *address = NULL;
	for (int i = 1; i <= get_list_size(list); i++) {
		address = get_from_list_at(list, i);
		free(address);
	}
}

void free_address(struct Address *address)
{
	free(address);
}

int compare_addresses(void *data1, void *data2)
{
	struct Address address1 = *(struct Address *)data1;
	struct Address address2 = *(struct Address *)data2;
	int ret_val		= 1;
	if (address2.name[0] != '\0' && strcmp(address1.name, address2.name) != 0) {
		ret_val = 0;
	}
	if (address2.surname[0] != '\0' && strcmp(address1.surname, address2.surname) != 0) {
		ret_val = 0;
	}
	if (address2.email[0] != '\0' && strcmp(address1.email, address2.email) != 0) {
		ret_val = 0;
	}
	if (address2.phone[0] != '\0' && strcmp(address1.phone, address2.phone) != 0) {
		ret_val = 0;
	}
	if (address2.name[0] == '\0' && address2.surname[0] == '\0' && address2.email[0] == '\0' &&
	    address2.phone[0] == '\0') {
		ret_val = 0;
	}
	return ret_val;
}

void print_address(void *data, int position)
{
	if (data == NULL) {
		return;
	}
	struct Address address = *(struct Address *)data;
	printf("Vardas: \t\t%s\n", address.name);
	printf("Pavardė: \t\t%s\n", address.surname);
	printf("El. paštas: \t\t%s\n", address.email);
	printf("Tel. numeris: \t\t%s\n", address.phone);
	printf("Pozicija sąraše: \t%5d\n", position);
	printf("--------------------------------------------------\n");
}