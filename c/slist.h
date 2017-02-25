#pragma once

#ifndef __SLIST_H__
#define __SLIST_H__
#include "node.h"

#define E_SLIST_OK     0
#define E_SLIST_ARGS  -1
#define E_SLIST_FULL  -2

struct slist
{
  struct snode* head;
  struct snode* tail;
  unsigned int  size;
  unsigned int  cmax;
};

int slist_init(struct slist* pl, const unsigned int cmax);
int slist_add_head(struct slist* pl, struct snode* pn);
int slist_add_tail(struct slist* pl, struct snode* pn);
int slist_is_empty(struct slist* pl);
int slist_is_fully(struct slist* pl);
struct snode* slist_get_head(struct slist* pl);
struct snode* slist_get_tail(struct slist* pl);
struct snode* slist_del_head(struct slist* pl);
struct snode* slist_del_tail(struct slist* pl);
int slist_insert_a(struct slist* pl, struct snode* pos, struct snode* pn); //insert a new node pn after the pos;
int slist_insert_b(struct slist* pl, struct snode* pos, struct snode* pn); //insert a new node pn before the pos;
struct snode* slist_remove(struct slist* pl, struct snode* pn);            //delete the node pn;

//mptr:member pointer; cptr: container pointer; type:user defined; member:the member of user defined type;
#ifndef slist_entry
#define slist_entry(type,member,mptr) BASEOF(type,member,(mptr))
#endif

#ifndef slist_head_entry
#define slist_head_entry(type,member,cptr) BASEOF(type,member,((cptr)->head))
#endif

#ifndef slist_tail_entry
#define slist_tail_entry(type,member,cptr) BASEOF(type,member,((cptr)->tail))
#endif

#ifndef slist_for_each
#define slist_for_each(pos,cptr) for(pos = (cptr)->head; pos; pos = pos->next)
#endif

#endif
