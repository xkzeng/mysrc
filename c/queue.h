#pragma once

#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "node.h"

#define E_QUEUE_OK      0
#define E_QUEUE_ARGS   -1
#define E_QUEUE_FULL   -2
#define E_QUEUE_EMPTY  -3

struct queue
{
  struct node* head;
  struct node* tail;
  unsigned int size;
  unsigned int cmax;
};

int queue_init(struct queue* pq, const unsigned int cmax);
int queue_add_head(struct queue* pq, struct node* pn);
int queue_add_tail(struct queue* pq, struct node* pn);
int queue_is_empty(struct queue* pq);
int queue_is_fully(struct queue* pq);
struct node* queue_get_head(struct queue* pq);
struct node* queue_get_tail(struct queue* pq);
struct node* queue_del_head(struct queue* pq);
struct node* queue_del_tail(struct queue* pq);
int queue_insert_a(struct queue* pq, struct node* pos, struct node* pn); //insert a new node pn after the pos;
int queue_insert_b(struct queue* pq, struct node* pos, struct node* pn); //insert a new node pn before the pos;
struct node* queue_remove(struct queue* pq, struct node* pn);                     //delete the node pn;

//mptr:member pointer; cptr: container pointer; type:user defined; member:the member of user defined type;
#ifndef queue_entry
#define queue_entry(type,member,mptr) BASEOF(type,member,(mptr))
#endif

#ifndef queue_head_entry
#define queue_head_entry(type,member,cptr) BASEOF(type,member,((cptr)->head))
#endif

#ifndef queue_tail_entry
#define queue_tail_entry(type,member,cptr) BASEOF(type,member,((cptr)->tail))
#endif

#ifndef queue_for_each
#define queue_for_each(pos,cptr) for(pos = (cptr)->head; pos; pos = pos->next)
#endif

#ifndef queue_for_each_r
#define queue_for_each_r(pos,cptr) for(pos = (cptr)->tail; pos; pos = pos->prev)
#endif

#endif
