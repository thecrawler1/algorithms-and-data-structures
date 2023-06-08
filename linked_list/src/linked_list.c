#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

linked_list *create_linked_list() {
  linked_list *list = malloc(sizeof(linked_list));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

int is_empty(linked_list *list) {
  return list->head == NULL && list->tail == NULL;
}

int size(linked_list *list) {
  int size = 0;

  for (node *current = list->head; current != NULL; current = current->next) {
    size++;
  }

  return size;
}

void _validate_if_index_is_out_of_the_bounds(linked_list *list, int index) {
  if (index < 0 || index >= size(list)) {
    fprintf(stderr, "List index out of the bounds!");
    exit(1);
  }
}

node *_node_at(linked_list *list, int index) {
  int count = 0;

  for (node *current = list->head; current != NULL; current = current->next) {
    if (count == index) {
       return current;
    }

    count++;
  }

  return NULL;
}

int value_at(linked_list *list, int index) {
  _validate_if_index_is_out_of_the_bounds(list, index);

  return _node_at(list, index)->value;
}

void _validate_if_list_is_empty(linked_list *list) {
  if (is_empty(list)) {
    fprintf(stderr, "The list is empty!");
    exit(1);
  }
}

int front(linked_list *list) {
  _validate_if_list_is_empty(list);

  return list->head->value;
}

int back(linked_list *list) {
  _validate_if_list_is_empty(list);

  return list->tail->value;
}

int pop_front(linked_list *list) {
  _validate_if_list_is_empty(list);

  node *new_first = list->head->next;
  int removed_value = list->head->value;

  if (list->head == list->tail) {
    list->tail = NULL;
  }

  free(list->head);

  list->head = new_first;

  return removed_value;
}

int pop_back(linked_list *list) {
  _validate_if_list_is_empty(list);

  node *new_last = NULL;
  node *current = list->head;

  while (current->next != NULL) {
    new_last = current;
    current = current->next;
  }

  if (new_last) {
    new_last->next = NULL;
  }

  int removed_value = list->tail->value;

  if (list->head == list->tail) {
    list->head = NULL;
  }

  free(list->tail);

  list->tail = new_last;

  return removed_value;
}

node *_create_new_node(int value) {
  node *new_node = malloc(sizeof(node));
  new_node->value = value;

  return new_node;
}

void push_front(linked_list *list, int value) {
  node *new_node = _create_new_node(value);

  if (is_empty(list)) {
    list->tail = new_node;
  }

  new_node->next = list->head;
  list->head = new_node;
}

void push_back(linked_list *list, int value) {
  node *new_node = _create_new_node(value);

  if (is_empty(list)) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
}

void insert(linked_list *list, int index, int value) {
  _validate_if_index_is_out_of_the_bounds(list, index);

  node *new_node = _create_new_node(value);
  node *prev_node = _node_at(list, index - 1);
  node *next_node = _node_at(list, index);

  if (prev_node) {
    prev_node->next = new_node;
  } else {
    list->head = new_node;
  }

  if (next_node) {
    new_node->next = next_node;
  } else {
    list->tail = new_node;
  }
}

void erase(linked_list *list, int index) {
  _validate_if_index_is_out_of_the_bounds(list, index);

  node *prev_node = _node_at(list, index - 1);
  node *curr_node = _node_at(list, index);

  if (prev_node) {
    prev_node->next = curr_node->next;
  } else {
    list->head = curr_node->next;
  }

  if (list->tail == curr_node) {
    list->tail = prev_node;
  }

  free(curr_node);
}
