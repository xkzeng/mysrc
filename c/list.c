#include "list.h"

//DEFINE_NODE(struct node,MyData)
//  int iField1;
//  int iField2;
//DEFINE_NODE_END(MyData);

int list_init(struct list* pl, const unsigned int cmax)
{
  if(NULL == pl)
  {
    return E_LIST_ARGS;
  }
  
  pl->head = NULL;
  pl->tail = NULL;
  pl->cmax = cmax;
  pl->size = 0;
  return E_LIST_OK;
}

int list_add_head(struct list* pl, struct node* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_LIST_ARGS;
  }
  
  if(pl->size >= pl->cmax)
  {
    return E_LIST_FULL;
  }
  
  if(list_is_empty(pl)) //for the first node;
  {
    pn->prev = NULL;
    pn->next = NULL;
    pl->head = pn;
    pl->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->prev = NULL;
    pn->next = pl->head;
    pl->head->prev = pn;
    pl->head = pn;
  }
  pl->size++;
  return E_LIST_OK;
}

int list_add_tail(struct list* pl, struct node* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_LIST_ARGS;
  }
  
  if(pl->size >= pl->cmax)
  {
    return E_LIST_FULL;
  }
  
  if(list_is_empty(pl)) //for the first node;
  {
    pn->prev = NULL;
    pn->next = NULL;
    pl->head = pn;
    pl->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = NULL;
    pn->prev = pl->tail;
    pl->tail->next = pn;
    pl->tail = pn;
  }
  pl->size++;
  return E_LIST_OK;
}

int list_is_empty(struct list* pl)
{
  return (((NULL == pl->head) && (NULL == pl->tail)) || (0 == pl->size));
}

int list_is_fully(struct list* pl)
{
  return (pl->size >= pl->cmax);
}

struct node* list_get_head(struct list* pl)
{
  return (pl ? pl->head : NULL);
}

struct node* list_get_tail(struct list* pl)
{
  return (pl ? pl->tail : NULL);
}

struct node* list_del_head(struct list* pl)
{
  struct node* pn = NULL;
  
  if(NULL == pl)
  {
    return NULL;
  }
  
  if(list_is_empty(pl)) //list is empty;
  {
    return NULL;
  }
  
  pn = pl->head;
  pl->head = pn->next;
  pl->head->prev = NULL;
  pn->next = NULL;
  pl->size--;
  return pn;
}

struct node* list_del_tail(struct list* pl)
{
  struct node* pn = NULL;
  
  if(NULL == pl)
  {
    return NULL;
  }
  
  if(list_is_empty(pl)) //list is empty;
  {
    return NULL;
  }
  
  pn = pl->tail;
  pl->tail = pn->prev;
  pl->tail->next = NULL;
  pn->prev = NULL;
  pl->size--;
  return pn;
}

int list_insert_a(struct list* pl, struct node* pos, struct node* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_LIST_ARGS;
  }
  
  if(list_is_fully(pl))
  {
    return E_LIST_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->next) || list_is_empty(pl))
  {
    return list_add_tail(pl, pn);
  }
  
  //insart the new node pn after the pos;
  pn->prev = pos;
  pn->next = pos->next;
  //pn->next->prev = pn;
  pos->next->prev = pn;
  pos->next = pn;
  pl->size++;
  return E_LIST_OK;
}

int list_insert_b(struct list* pl, struct node* pos, struct node* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_LIST_ARGS;
  }
  
  if(list_is_fully(pl))
  {
    return E_LIST_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->prev) || list_is_empty(pl))
  {
    return list_add_head(pl, pn);
  }
  
  //insart the new node pn befare the pos;
  pn->prev = pos->prev;
  pn->next = pos;
  //pn->prev->next = pn;
  pos->prev->next = pn;
  pos->prev = pn;
  pl->size++;
  return E_LIST_OK;
}

int list_remove(struct list* pl, struct node* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_LIST_ARGS;
  }
  
  if(list_is_empty(pl))
  {
    return E_LIST_EMPTY;
  }
  
  if(NULL == pn->next)  //tail node
  {
    return list_del_tail(pl);
  }
  
  if(NULL == pn->prev)  //head node
  {
    return list_del_head(pl);
  }
  
  pn->prev->next = pn->next;
  pn->next->prev = pn->prev;
  pl->size--;
  return E_LIST_OK;
}
