#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
	char name[30];
	char surname[30];
	char email[30];
	char phone[30];
	int position;
	struct Address *next;
};

struct Address *create_new_node(char *name, char *surname, char *email, char *phone);
void display_all_records(struct Address *list);
void display_all_records_without_position(struct Address *list);
int add_to_list_end(struct Address **list, char *name, char *surname, char *email, char *phone);
int add_existing_retain_position(struct Address **list, struct Address *node);
int add_to_list_position(struct Address **list, char *name, char *surname, char *email, char *phone, int position);
void position_correction(struct Address **list, int increment);
int delete_from_list_by_position(struct Address **list, int position);
void delete_all_records(struct Address **list);
struct Address *search_by_position(struct Address *list, int position);
struct Address *search_records(struct Address *list, char *name, char *surname, char *email, char *phone);
int get_list_size(struct Address *list);