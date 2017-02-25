#include "slist.h"

//DEFINE_NODE(struct snode,MyData)
//  int iField1;
//  int iField2;
//DEFINE_NODE_END(MyData);

int slist_init(struct slist* pl, const unsigned int cmax)
{
  if(NULL == pl)
  {
    return E_SLIST_ARGS;
  }
  
  pl->head = NULL;
  pl->tail = NULL;
  pl->cmax = cmax;
  pl->size = 0;
  return E_SLIST_OK;
}

int slist_add_head(struct slist* pl, struct snode* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_SLIST_ARGS;
  }
  
  if(pl->size >= pl->cmax)
  {
    return E_SLIST_FULL;
  }
  
  if(slist_is_empty(pl)) //for the first node;
  {
    pn->next = NULL;
    pl->head = pn;
    pl->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = pl->head;
    pl->head = pn;
  }
  pl->size++;
  return E_SLIST_OK;
}

int slist_add_tail(struct slist* pl, struct snode* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_SLIST_ARGS;
  }
  
  if(pl->size >= pl->cmax)
  {
    return E_SLIST_FULL;
  }
  
  if(slist_is_empty(pl)) //for the first node;
  {
    pn->next = NULL;
    pl->head = pn;
    pl->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = NULL;
    pl->tail->next = pn;
    pl->tail = pn;
  }
  pl->size++;
  return E_SLIST_OK;
}

int slist_is_empty(struct slist* pl)
{
  return (((NULL == pl->head) && (NULL == pl->tail)) || (0 == pl->size));
}

int slist_is_fully(struct slist* pl)
{
  return (pl->size >= pl->cmax);
}

struct snode* slist_get_head(struct slist* pl)
{
  return (pl ? pl->head : NULL);
}

struct snode* slist_get_tail(struct slist* pl)
{
  return (pl ? pl->tail : NULL);
}

struct snode* slist_del_head(struct slist* pl)
{
  struct snode* pn = NULL;
  
  if(NULL == pl)
  {
    return NULL;
  }
  
  if(slist_is_empty(pl)) //slist is empty;
  {
    return NULL;
  }
  
  pn = pl->head;
  pl->head = pn->next;
  pn->next = NULL;
  pl->size--;
  return pn;
}

struct snode* slist_del_tail(struct slist* pl)
{
  struct snode* pn = NULL;
  
  if(NULL == pl)
  {
    return NULL;
  }
  
  if(slist_is_empty(pl)) //slist is empty;
  {
    return NULL;
  }
  
  for(pn = pl->head; pn->next != pl->tail; pn = pn->next){}
  pl->tail = pn;
  pn = pl->tail->next;   //tail-node;
  pl->tail->next = NULL;
  pl->size--;
  return pn;
}

int slist_insert_a(struct slist* pl, struct snode* pos, struct snode* pn)
{
  if((NULL == pl) || (NULL == pn))
  {
    return E_SLIST_ARGS;
  }
  
  if(slist_is_fully(pl))
  {
    return E_SLIST_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->next) || (pos == pl->tail) || slist_is_empty(pl))
  {
    return slist_add_tail(pl, pn);
  }
  
  //insart the new node pn after the pos;
  pn->next = pos->next;
  pos->next = pn;
  pl->size++;
  return E_SLIST_OK;
}

int slist_insert_b(struct slist* pl, struct snode* pos, struct snode* pn)
{
  struct snode* cur = NULL;
  if((NULL == pl) || (NULL == pn))
  {
    return E_SLIST_ARGS;
  }
  
  if(slist_is_fully(pl))
  {
    return E_SLIST_FULL;
  }
  
  if((NULL == pos) || (pos == pl->head) || slist_is_empty(pl))
  {
    return slist_add_head(pl, pn);
  }
  
  //insart the new node pn before the pos;
  for(cur = pl->head; NULL != cur && cur->next != pos; cur = cur->next);
  if(NULL == cur)
  {
    return slist_add_head(pl, pn);
  }
  
  // |_cur_|_next_|      |_pn_|_next_|      |_pos_|_next_|
  if(cur->next == pos)
  {
    pn->next = pos;
    cur->next = pn;
    pl->size++;
  }
  return E_SLIST_OK;
}

struct snode* slist_remove(struct slist* pl, struct snode* pn)
{
  struct snode* cur = NULL;
  if((NULL == pl) || (NULL == pn))
  {
    return NULL;
  }
  
  if(slist_is_empty(pl))
  {
    return NULL;
  }
  
  if(pn == pl->head)
  {
    return slist_del_head(pl);
  }
  
  if(pn == pl->tail)
  {
    return slist_del_tail(pl);
  }
  
  for(cur = pl->head; NULL != cur && cur->next != pn; cur = cur->next);
  if(NULL == cur)
  {
    return NULL;
  }
  
  // |_cur_|_next_|      |_pn_|_next_|      |_pos_|_next_|
  if(cur->next == pn)
  {
    cur->next = pn->next;
    pl->size--;
  }
  return pn;
}
