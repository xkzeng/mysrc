#pragma once

#ifndef __LIST_H__
#define __LIST_H__
#include "node.h"

#define E_LIST_OK      0
#define E_LIST_ARGS   -1
#define E_LIST_FULL   -2
#define E_LIST_EMPTY  -3

struct list
{
  struct node* head;
  struct node* tail;
  unsigned int size;
  unsigned int cmax;
};

int list_init(struct list* pl, const unsigned int cmax);
int list_add_head(struct list* pl, struct node* pn);
int list_add_tail(struct list* pl, struct node* pn);
int list_is_empty(struct list* pl);
int list_is_fully(struct list* pl);
struct node* list_get_head(struct list* pl);
struct node* list_get_tail(struct list* pl);
struct node* list_del_head(struct list* pl);
struct node* list_del_tail(struct list* pl);
int list_insert_a(struct list* pl, struct node* pos, struct node* pn); //insert a new node pn after the pos;
int list_insert_b(struct list* pl, struct node* pos, struct node* pn); //insert a new node pn before the pos;
int list_remove(struct list* pl, struct node* pn);                     //delete the node pn;

//mptr:member pointer; cptr: container pointer; type:user defined; member:the member of user defined type;
#ifndef list_entry
#define list_entry(type,member,mptr) BASEOF(type,member,(mptr))
#endif

#ifndef list_head_entry
#define list_head_entry(type,member,cptr) BASEOF(type,member,((cptr)->head))
#endif

#ifndef list_tail_entry
#define list_tail_entry(type,member,cptr) BASEOF(type,member,((cptr)->tail))
#endif

#ifndef list_for_each
#define list_for_each(pos,cptr) for(pos = (cptr)->head; pos; pos = pos->next)
#endif

#ifndef list_for_each_r
#define list_for_each_r(pos,cptr) for(pos = (cptr)->tail; pos; pos = pos->prev)
#endif

#endif
