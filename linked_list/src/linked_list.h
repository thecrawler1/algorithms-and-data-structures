#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
  int value;
  struct node *next;
} node;

typedef struct {
  node *head;
  node *tail;
} linked_list;

linked_list *create_linked_list();

int is_empty(linked_list *);
int size(linked_list *);
int value_at(linked_list *, int);
int front(linked_list *);
int back(linked_list *);
int pop_front(linked_list *);
int pop_back(linked_list *);

void push_front(linked_list *, int);
void push_back(linked_list *, int);
void insert(linked_list *, int, int);
void erase(linked_list *, int);

#endif // !LINKED_LIST_H
