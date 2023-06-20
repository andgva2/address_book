#include "liblinkedlist.h"

List *create_list()
{
	List *new_list = (List *)malloc(sizeof(List));
	new_list->size = 0;
	new_list->head = NULL;
	return new_list;
}

void add_to_list_start(List *list, void *data)
{
	Node *new_node	   = (Node *)malloc(sizeof(Node));
	new_node->data	   = data;
	new_node->position = 1;
	new_node->next	   = list->head;
	if (list->head != NULL) {
		Node *current_node = list->head;
		while (current_node != NULL) {
			current_node->position++;
			Node *next_node = current_node->next;
			current_node	= next_node;
		}
	}
	list->head = new_node;
	list->size++;
}

void add_to_list_end(List *list, void *data)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	if (list->size == 0) {
		list->head = new_node;
		list->size++;
		new_node->position = 1;
		return;
	}
	Node *current_node = list->head;
	while (current_node->next != NULL) {
		Node *next_node = current_node->next;
		current_node	= next_node;
	}
	current_node->next = new_node;
	list->size++;
	new_node->position = list->size;
}

void add_to_list_at(List *list, void *data, int position)
{
	if (position < 1 || position > list->size + 1) {
		return;
	}
	if (position == 1) {
		add_to_list_start(list, data);
		return;
	}
	if (position == list->size + 1) {
		add_to_list_end(list, data);
		return;
	}
	Node *new_node	   = (Node *)malloc(sizeof(Node));
	new_node->data	   = data;
	new_node->position = position;
	Node *current_node = list->head;
	while (current_node->position != position - 1) {
		current_node = current_node->next;
	}
	Node *next_node	   = current_node->next;
	current_node->next = new_node;
	new_node->next	   = next_node;
	list->size++;
	while (next_node != NULL) {
		next_node->position++;
		next_node = next_node->next;
	}
}

void *remove_from_list_start(List *list)
{
	if (list->size == 0) {
		return NULL;
	}
	Node *node_to_remove = list->head;
	void *data	     = node_to_remove->data;
	list->head	     = node_to_remove->next;
	free(node_to_remove);
	list->size--;
	Node *current_node = list->head;
	while (current_node != NULL) {
		current_node->position--;
		Node *next_node = current_node->next;
		current_node	= next_node;
	}
	return data;
}

void *remove_from_list_end(List *list)
{
	if (list->size == 0) {
		return NULL;
	} else if (list->size == 1) {
		Node *node_to_remove = list->head;
		void *data	     = node_to_remove->data;
		list->head	     = node_to_remove->next;
		free(node_to_remove);
		list->size--;
		return data;
	}
	Node *current_node = list->head;
	while (current_node->next->next != NULL) {
		current_node->position--;
		Node *next_node = current_node->next;
		current_node	= next_node;
	}
	void *data = current_node->next->data;
	free(current_node->next);
	list->size--;
	return data;
}

void *remove_from_list_at(List *list, int position)
{
	if (list->size == 0 || position > list->size || position < 1) {
		return NULL;
	}
	if (position == 1) {
		Node *node_to_remove = list->head;
		void *data	     = node_to_remove->data;
		list->head	     = node_to_remove->next;
		free(node_to_remove);
		list->size--;
		Node *current_node = list->head;
		while (current_node != NULL) {
			current_node->position--;
			Node *next_node = current_node->next;
			current_node	= next_node;
		}
		return data;
	}
	Node *current_node = list->head;
	while (current_node->next->position != position) {
		Node *next_node = current_node->next;
		current_node	= next_node;
	}
	void *data	     = current_node->next->data;
	Node *node_to_remove = current_node->next;
	current_node->next   = node_to_remove->next;
	free(node_to_remove);
	list->size--;
	if (current_node->next != NULL) {
		current_node = current_node->next;
		while (current_node != NULL) {
			current_node->position--;
			Node *next_node = current_node->next;
			current_node	= next_node;
		}
	}

	return data;
}

void *remove_from_list_by(List *list, void *data, int (*fptr)())
{
	if (list->size == 0) {
		return NULL;
	}
	Node *current_node = list->head;
	while (current_node != NULL) {
		if ((*fptr)(current_node->data, data) == 1) {
			return remove_from_list_at(list, current_node->position);
		}
		current_node = current_node->next;
	}
	return NULL;
}

void remove_all_from_list(List *list)
{
	Node *current_node = list->head;
	while (list->size != 0) {
		Node *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
		list->size--;
	}
}

void *get_from_list_at(List *list, int position)
{
	if (list->size == 0 || position > list->size || position < 1) {
		return NULL;
	}
	Node *current_node = list->head;
	while (current_node->position != position) {
		current_node = current_node->next;
	}
	return current_node->data;
}

List *get_sublist_by(List *list, void *data, int (*fptr)())
{
	List *sublist	   = create_list();
	Node *current_node = list->head;
	while (current_node != NULL) {
		if ((*fptr)(current_node->data, data) == 1) {
			add_to_list_end(sublist, current_node->data);
		}
		current_node = current_node->next;
	}
	return sublist;
}

int get_position_by(List *list, void *data, int (*fptr)())
{
	Node *current_node = list->head;
	while (current_node != NULL) {
		if ((*fptr)(current_node->data, data) == 1) {
			return current_node->position;
		}
		current_node = current_node->next;
	}
	return -1;
}

int get_list_size(List *list)
{
	return list->size;
}

void free_list(List *list)
{
	if (list->size == 0) {
		free(list);
		return;
	}
	Node *current_node = list->head;
	while (current_node != NULL) {
		Node *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	free(list);
}

void print_list_by(List *list, void (*fptr)())
{
	if (list->size == 0) {
		return;
	}
	Node *current_node = list->head;
	while (current_node != NULL) {
		(*fptr)(current_node->data, current_node->position);
		current_node = current_node->next;
	}
}
