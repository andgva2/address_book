#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void *data;
	int position;
	struct node *next;
} Node;

typedef struct list {
	int size;
	Node *head;
} List;

List *create_list();
void add_to_list_start(List *list, void *data);
void add_to_list_end(List *list, void *data);
void add_to_list_at(List *list, void *data, int position);
void *remove_from_list_start(List *list);
void *remove_from_list_end(List *list);
void *remove_from_list_at(List *list, int position);
void *remove_from_list_by(List *list, void *data, int (*fptr)());
void *get_from_list_at(List *list, int position);
List *get_sublist_by(List *list, void *data, int (*fptr)());
int get_position_by(List *list, void *data, int (*fptr)());
int get_list_size(List *list);
void free_list(List *list);
void print_list_by(List *list, void (*fptr)());
