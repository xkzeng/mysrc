#pragma once

#ifndef __STACK_H__
#define __STACK_H__
#include "node.h"

#define E_STACK_OK      0
#define E_STACK_ARGS   -1
#define E_STACK_FULL   -2
#define E_STACK_EMPTY  -3

#ifndef stack_entry
#define stack_entry(type,member,mptr) BASEOF(type,member,mptr)
#endif

struct stack
{
  struct node* sp;
  struct node* ss;
  unsigned int size;
  unsigned int cmax;
};

int stack_init(struct stack* ps, const unsigned int cmax);
int stack_push(struct stack* ps, struct node* pn);
struct node* stack_pop(struct stack* ps);
int stack_is_empty(struct stack* ps);
int stack_is_fully(struct stack* ps);

//mptr:member pointer; cptr: container pointer; type:user defined; member:the member of user defined type;
#ifndef stack_entry
#define stack_entry(type,member,mptr) BASEOF(type,member,(mptr))
#endif

#endif
