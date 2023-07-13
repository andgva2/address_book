#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <liblinkedlist.h>
#define DELIMETER ","

int exit_flag = 0;

void load_default_addresses(struct Address **list);
void load_addresses(FILE *file, struct Address **list);

void interuption_handler(int signum)
{
	printf("\n\n***Program was interupted***\n");
	printf("***Input anything, program will exit.***\n");
	exit_flag = 1;
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

int main(void)
{
	signal(SIGINT, interuption_handler);

	struct Address *address_list = NULL;

	load_default_addresses(&address_list);

	printf("Welcome to the address book\n\n");
	while (!exit_flag) {
		char user_input[2];
		user_input[1] = '\0';

		printf("\nCurrently there are %d records in the address book.\n", get_list_size(address_list));
		printf("Options menu:\n");
		print_menu();

		printf("Enter your choice: ");
		scanf("%1s", &user_input[0]);
		if (getchar() == EOF) {
			printf("\n\n***Exiting the program***\n");
			exit_flag = 1;
		};

		if (exit_flag) {
			goto cleanup;
		}

		switch (user_input[0]) {
		case '1':
			printf("\n***Displaying all records***\n");
			display_all_records(address_list);
			break;
		case '2':
			printf("\n***Adding new address***\n");
			printf("Enter name: ");
			char add_name[30];
			fgets(add_name, 30, stdin);
			add_name[strlen(add_name) - 1] = '\0';

			printf("Enter surname: ");
			char add_surname[30];
			fgets(add_surname, 30, stdin);
			add_surname[strlen(add_surname) - 1] = '\0';

			printf("Enter email: ");
			char add_email[30];
			fgets(add_email, 30, stdin);
			add_email[strlen(add_email) - 1] = '\0';

			printf("Enter phone: ");
			char add_phone[30];
			fgets(add_phone, 30, stdin);
			add_phone[strlen(add_phone) - 1] = '\0';

			if (add_to_list_end(&address_list, add_name, add_surname, add_email, add_phone)) {
				printf("\n***Error while adding new address***\n");
			}
			break;
		case '3':
			printf("\n***Adding new address at specified position***\n");
			printf("Enter position: ");
			int position_add;
			scanf("%d", &position_add);
			if (getchar() == EOF) {
				break;
			};

			
			if (position_add < 1 || position_add > get_list_size(address_list) + 1) {
				printf("\n***Invalid position***\n");
				break;
			}

			printf("Enter name: ");
			char add_at_name[30];
			fgets(add_at_name, 30, stdin);
			add_at_name[strlen(add_at_name) - 1] = '\0';

			printf("Enter surname: ");
			char add_at_surname[30];
			fgets(add_at_surname, 30, stdin);
			add_at_surname[strlen(add_at_surname) - 1] = '\0';

			printf("Enter email: ");
			char add_at_email[30];
			fgets(add_at_email, 30, stdin);
			add_at_email[strlen(add_at_email) - 1] = '\0';

			printf("Enter phone: ");
			char add_at_phone[30];
			fgets(add_at_phone, 30, stdin);
			add_at_phone[strlen(add_at_phone) - 1] = '\0';

			if (add_to_list_position(&address_list, add_at_name, add_at_surname, add_at_email,
						 add_at_phone, position_add)) {
				printf("\n***Error while adding new address***\n");
			}
			break;
		case '4':
			printf("\n***Deleting address from specified position***\n");
			printf("Enter position: ");
			int position_delete;
			scanf("%d", &position_delete);
			if (getchar() == EOF) {
				break;
			};

			if (position_delete < 1 || position_delete > get_list_size(address_list)) {
				printf("\n***Invalid position***\n");
				break;
			}

			if (delete_from_list_by_position(&address_list, position_delete)) {
				printf("\n***Error while deleting address***\n");
			}
			break;
		case '5':
			printf("\n***Deleting whole address book***\n");
			delete_all_records(&address_list);
			break;
		case '6':
			printf("\n***Finding address by position***\n");
			printf("Enter position: ");
			int position_find;
			scanf("%d", &position_find);
			if (getchar() == EOF) {
				break;
			};

			if (position_find < 1 || position_find > get_list_size(address_list)) {
				printf("\n***Invalid position***\n");
				break;
			}

			printf("\nAddress at position %d:\n", position_find);
			struct Address *address_find = NULL;
			address_find		     = search_by_position(address_list, position_find);
			if (address_find == NULL) {
				printf("\n***Error while finding address***\n");
				break;
			}

			printf("Name: \t\t%s\n", address_find->name);
			printf("Surname: \t%s\n", address_find->surname);
			printf("Email: \t\t%s\n", address_find->email);
			printf("Phone: \t\t%s\n", address_find->phone);
			break;
		case '7':
			printf("\n***Finding address by name, surname, email or phone number***\n");
			printf("Enter information or leave it empty:\n");

			printf("Enter name: ");
			char name[30];
			fgets(name, 30, stdin);
			name[strcspn(name, "\n")] = 0;
			if (name[0] == '\n') {
				name[0] = '\0';
			}

			printf("Enter surname: ");
			char surname[30];
			fgets(surname, 30, stdin);
			surname[strcspn(surname, "\n")] = 0;
			if (surname[0] == '\n') {
				surname[0] = '\0';
			}

			printf("Enter email: ");
			char email[30];
			fgets(email, 30, stdin);
			email[strcspn(email, "\n")] = 0;
			if (email[0] == '\n') {
				email[0] = '\0';
			}

			printf("Enter phone: ");
			char phone[30];
			fgets(phone, 30, stdin);
			phone[strcspn(phone, "\n")] = 0;
			if (phone[0] == '\n') {
				phone[0] = '\0';
			}

			struct Address *found_addresses = NULL;
			found_addresses = search_records(address_list, name, surname, email, phone);
			if (get_list_size(found_addresses) == 0 || get_list_size(found_addresses) == -1) {
				printf("\n***No addresses found***\n");
				break;
			} else {
				printf("\n***Found %d addresses***\n", get_list_size(found_addresses));
				display_all_records(found_addresses);
			}

			delete_all_records(&found_addresses);
			break;
		case '8':
			printf("\n***Exiting***\n");
			goto cleanup;
			break;

		default:
			printf("\n***Invalid input***\n");
			break;
		}
	}

cleanup:
	delete_all_records(&address_list);

	return exit_flag;
}

void load_default_addresses(struct Address **list)
{
	char *address_file_path = "";
	char *file_name		= "/addresses.csv";

	address_file_path = malloc(strlen(getenv("HOME")) + strlen(file_name) + 1);
	strcpy(address_file_path, getenv("HOME"));
	strcat(address_file_path, file_name);

	FILE *address_file = NULL;
	address_file	   = fopen(address_file_path, "r");

	if (address_file == NULL) {
		fprintf(stderr, "\nWARNING:\n");
		fprintf(stderr, "There was a problem opening %s\n\n", address_file_path);
		free(address_file_path);
	} else {
		load_addresses(address_file, list);
		fclose(address_file);
		free(address_file_path);
	}
}

void load_addresses(FILE *file, struct Address **list)
{
	char line[128];
	int line_no = 0;
	while (fgets(line, sizeof(line), file)) {
		line_no++;

		if (strcmp(line, "\n") == 0) {
			continue;
		}

		char name[30];
		strcpy(name, strtok(line, DELIMETER));
		char surname[30];
		strcpy(surname, strtok(NULL, DELIMETER));
		char email[30];
		strcpy(email, strtok(NULL, DELIMETER));
		char phone[30];
		strcpy(phone, strtok(NULL, DELIMETER));
		phone[strcspn(phone, "\n")] = 0;

		if (add_to_list_end(list, name, surname, email, phone)) {
			fprintf(stderr, "\nWARNING:\n");
			fprintf(stderr, "[LINE: %d] Unable to add a record from data file to list.\n\n",
				line_no);
			break;
		}
	}
}
