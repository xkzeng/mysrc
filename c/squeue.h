#pragma once

#ifndef __SQUEUE_H__
#define __SQUEUE_H__
#include "node.h"

#define E_SQUEUE_OK     0
#define E_SQUEUE_ARGS  -1
#define E_SQUEUE_FULL  -2

struct squeue
{
  struct snode* head;
  struct snode* tail;
  unsigned int  size;
  unsigned int  cmax;
};

int squeue_init(struct squeue* pq, const unsigned int cmax);
int squeue_add_head(struct squeue* pq, struct snode* pn);
int squeue_add_tail(struct squeue* pq, struct snode* pn);
int squeue_is_empty(struct squeue* pq);
int squeue_is_fully(struct squeue* pq);
struct snode* squeue_get_head(struct squeue* pq);
struct snode* squeue_get_tail(struct squeue* pq);
struct snode* squeue_del_head(struct squeue* pq);
struct snode* squeue_del_tail(struct squeue* pq);
int squeue_insert_a(struct squeue* pq, struct snode* pos, struct snode* pn); //insert a new node pn after the pos;
int squeue_insert_b(struct squeue* pq, struct snode* pos, struct snode* pn); //insert a new node pn before the pos;
struct snode* squeue_remove(struct squeue* pq, struct snode* pn);            //delete the node pn;

//mptr:member pointer; cptr:container pointer; type:user defined type; member:the member of user defined type;
#ifndef squeue_entry
#define squeue_entry(type,member,mptr) BASEOF(type,member,(mptr))
#endif

#ifndef squeue_head_entry
#define squeue_head_entry(type,member,cptr) BASEOF(type,member,((cptr)->head))
#endif

#ifndef squeue_tail_entry
#define squeue_tail_entry(type,member,cptr) BASEOF(type,member,((cptr)->tail))
#endif

#ifndef squeue_for_each
#define squeue_for_each(pos,cptr) for(pos = (cptr)->head; pos; pos = pos->next)
#endif

#endif
