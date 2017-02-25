#include "stack.h"

//DEFINE_NODE(struct node,MyData)
//  int iField1;
//  int iField2;
//DEFINE_NODE_END(MyData);

static struct node stack_base_node = {NULL, NULL};
static struct node* const BASE_OF_STACK = &stack_base_node;

int stack_init(struct stack* ps, const unsigned int cmax)
{
  if(NULL == ps)
  {
    return E_STACK_ARGS;
  }
  
  ps->ss = BASE_OF_STACK;
  ps->sp = BASE_OF_STACK;
  ps->cmax = cmax;
  ps->size = 0;
  return E_STACK_OK;
}

int stack_push(struct stack* ps, struct node* pn)
{
  if((NULL == ps) || (NULL == pn))
  {
    return E_STACK_ARGS;
  }
  
  if(ps->size >= ps->cmax)
  {
    return E_STACK_FULL; //stack is full;
  }
  
  pn->next = NULL;
  pn->prev = ps->sp;
  ps->sp->next = pn;
  ps->sp = pn; //sp++;
  ps->size++;
  return E_STACK_OK;
}

struct node* stack_pop(struct stack* ps)
{
  struct node* pn = NULL;
  
  if(NULL == ps)
  {
    return NULL;
  }
  
  if(stack_is_empty(ps))
  {
    return NULL; //stack is empty;
  }
  
  pn = ps->sp;
  ps->sp = pn->prev; //sp--;
  ps->sp->next = NULL;
  pn->prev = NULL;
  ps->size--;
  return pn;
}

int stack_is_empty(struct stack* ps)
{
  return (((BASE_OF_STACK == ps->sp) && (BASE_OF_STACK == ps->ss)) || (ps->size <= ps->cmax));
}

int stack_is_fully(struct stack* ps)
{
  return (ps->size >= ps->cmax);
}
