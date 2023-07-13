#include "liblinkedlist.h"

/// creates a new node that takes name, surname, email, phone
struct Address *create_new_node(char *name, char *surname, char *email, char *phone)
{
	struct Address *new_node = NULL;
	new_node		 = (struct Address *)malloc(sizeof(struct Address));
	if (new_node == NULL) {
		fprintf(stderr, "\nWARNING:\n");
		fprintf(stderr, "Error: memory allocation failed\n\n");
		return NULL;
	}

	strcpy(new_node->name, name);
	strcpy(new_node->surname, surname);
	strcpy(new_node->email, email);
	strcpy(new_node->phone, phone);
	new_node->position = -1;
	new_node->next	   = NULL;

	return new_node;
}

/// display all records
void display_all_records(struct Address *list)
{
	struct Address *current_node = list;
	while (current_node != NULL) {
		printf("Name: \t\t%s\n", current_node->name);
		printf("Surname: \t%s\n", current_node->surname);
		printf("Email: \t\t%s\n", current_node->email);
		printf("Phone: \t\t%s\n", current_node->phone);
		printf("Position:    %5d\n", current_node->position);
		printf("--------------------------------------------------\n");
		current_node = current_node->next;
	}
}

/// display all records withoud position
void display_all_records_without_position(struct Address *list)
{
	struct Address *current_node = list;
	while (current_node != NULL) {
		printf("Name: \t\t%s\n", current_node->name);
		printf("Surname: \t%s\n", current_node->surname);
		printf("Email: \t\t%s\n", current_node->email);
		printf("Phone: \t\t%s\n", current_node->phone);
		printf("--------------------------------------------------\n");
		current_node = current_node->next;
	}
}

/// add new record to the end of the list
int add_to_list_end(struct Address **list, char *name, char *surname, char *email, char *phone)
{
	struct Address *new_node = create_new_node(name, surname, email, phone);

	if (new_node == NULL) {
		return 1;
	}
	if (*list == NULL) {
		new_node->position = 1;
		*list		   = new_node;
		return 0;
	}

	struct Address *current_node = *list;
	while (current_node->next != NULL) {
		current_node = current_node->next;
	}
	current_node->next = new_node;
	new_node->position = current_node->position + 1;
	return 0;
}

/// add new record at specific position and correct positions of other records
int add_to_list_position(struct Address **list, char *name, char *surname, char *email, char *phone,
			 int position)
{
	struct Address *new_node = NULL;
	new_node		 = create_new_node(name, surname, email, phone);
	if (new_node == NULL) {
		return 1;
	}

	if (*list == NULL) {
		new_node->position = 1;
		*list		   = new_node;
		return 0;
	}

	struct Address *current_node  = *list;
	struct Address *previous_node = NULL;

	while (current_node->next != NULL && current_node->position != position) {
		previous_node = current_node;
		current_node  = current_node->next;
	}
	// If the position is 1
	if (previous_node == NULL) {
		new_node->next = current_node;
		*list	       = new_node;
	} // If the position is [size + 1]
	else if (position == current_node->position + 1) {
		current_node->next = new_node;
		new_node->next	   = NULL;
		new_node->position = position;
		return 0;
	} // If the position is [2, size]
	else {
		new_node->next	    = current_node;
		previous_node->next = new_node;
	}
	position_correction(&new_node->next, 1);
	new_node->position = position;

	return 0;
}

/// position correction method with increment or decrement flag for the rest of the list
void position_correction(struct Address **list, int increment)
{
	struct Address *current_node = *list;
	while (current_node != NULL) {
		if (increment) {
			current_node->position++;
		} else {
			current_node->position--;
		}
		current_node = current_node->next;
	}
}

/// delete record at specific position and correct positions of other records
int delete_from_list_by_position(struct Address **list, int position)
{
	if (*list == NULL) {
		return 1;
	}

	struct Address *current_node  = *list;
	struct Address *previous_node = NULL;
	while (current_node->next != NULL && current_node->position != position) {
		previous_node = current_node;
		current_node  = current_node->next;
	}
	if (previous_node == NULL) {
		*list = current_node->next;
	} else {
		previous_node->next = current_node->next;
	}
	position_correction(&current_node->next, 0);

	free(current_node);
	return 0;
}

/// delete all records
void delete_all_records(struct Address **list)
{
	if (*list == NULL) {
		return;
	}

	struct Address *current_node = *list;
	struct Address *next_node    = NULL;
	while (current_node != NULL) {
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*list = NULL;
}

/// search record by position
struct Address *search_by_position(struct Address *list, int position)
{
	if (list == NULL) {
		return NULL;
	}

	struct Address *current_node = list;
	while (current_node != NULL) {
		if (current_node->position == position) {
			return current_node;
		}
		current_node = current_node->next;
	}
	return NULL;
}

/// search record by name, surname, email or phone number and return sublist of found records
struct Address *search_records(struct Address *list, char *name, char *surname, char *email, char *phone)
{
	if (list == NULL) {
		return NULL;
	}

	struct Address *current_node = list;
	struct Address *sublist	     = NULL;
	while (current_node != NULL) {
		int include = 1;
		// Comparing each and every field with the search parameters
		if (strlen(name) != 0 && strcmp(current_node->name, name) != 0) {
			include = 0;
		}
		if (strlen(surname) != 0 && strcmp(current_node->surname, surname) != 0) {
			include = 0;
		}
		if (strlen(email) != 0 && strcmp(current_node->email, email) != 0) {
			include = 0;
		}
		if (strlen(phone) != 0 && strcmp(current_node->phone, phone) != 0) {
			include = 0;
		}

		if (include) {
			add_existing_retain_position(&sublist, current_node);
		}

		current_node = current_node->next;
	}
	return sublist;
}

/// add existing record to the end of the list withoud changing it's position
int add_existing_retain_position(struct Address **list, struct Address *node)
{
	if (node == NULL) {
		return 1;
	}

	struct Address *new_node = NULL;
	new_node		 = create_new_node(node->name, node->surname, node->email, node->phone);
	new_node->position	 = node->position;

	if (*list == NULL) {
		*list = new_node;
		return 0;
	}

	struct Address *current_node = *list;
	while (current_node->next != NULL) {
		current_node = current_node->next;
	}
	current_node->next = new_node;

	return 0;
}

/// get size of the list
int get_list_size(struct Address *list)
{
	int size = 0;

	if (list == NULL) {
		return size;
	}

	struct Address *current_node = list;

	while (current_node != NULL) {
		size++;
		current_node = current_node->next;
	}
	return size;
}