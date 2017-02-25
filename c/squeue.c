#include "squeue.h"

//DEFINE_NODE(struct snode,MyData)
//  int iField1;
//  int iField2;
//DEFINE_NODE_END(MyData);

int squeue_init(struct squeue* pq, const unsigned int cmax)
{
  if(NULL == pq)
  {
    return E_SQUEUE_ARGS;
  }
  
  pq->head = NULL;
  pq->tail = NULL;
  pq->cmax = cmax;
  pq->size = 0;
  return E_SQUEUE_OK;
}

int squeue_add_head(struct squeue* pq, struct snode* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_SQUEUE_ARGS;
  }
  
  if(pq->size >= pq->cmax)
  {
    return E_SQUEUE_FULL;
  }
  
  if(squeue_is_empty(pq)) //for the first node;
  {
    pn->next = NULL;
    pq->head = pn;
    pq->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = pq->head;
    pq->head = pn;
  }
  pq->size++;
  return E_SQUEUE_OK;
}

int squeue_add_tail(struct squeue* pq, struct snode* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_SQUEUE_ARGS;
  }
  
  if(pq->size >= pq->cmax)
  {
    return E_SQUEUE_FULL;
  }
  
  if(squeue_is_empty(pq)) //for the first node;
  {
    pn->next = NULL;
    pq->head = pn;
    pq->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = NULL;
    pq->tail->next = pn;
    pq->tail = pn;
  }
  pq->size++;
  return E_SQUEUE_OK;
}

int squeue_is_empty(struct squeue* pq)
{
  return (((NULL == pq->head) && (NULL == pq->tail)) || (0 == pq->size));
}

int squeue_is_fully(struct squeue* pq)
{
  return (pq->size >= pq->cmax);
}

struct snode* squeue_get_head(struct squeue* pq)
{
  return (pq ? pq->head : NULL);
}

struct snode* squeue_get_tail(struct squeue* pq)
{
  return (pq ? pq->tail : NULL);
}

struct snode* squeue_del_head(struct squeue* pq)
{
  struct snode* pn = NULL;
  
  if(NULL == pq)
  {
    return NULL;
  }
  
  if(squeue_is_empty(pq)) //squeue is empty;
  {
    return NULL;
  }
  
  pn = pq->head;
  pq->head = pn->next;
  pn->next = NULL;
  pq->size--;
  return pn;
}

struct snode* squeue_del_tail(struct squeue* pq)
{
  struct snode* pn = NULL;
  
  if(NULL == pq)
  {
    return NULL;
  }
  
  if(squeue_is_empty(pq)) //squeue is empty;
  {
    return NULL;
  }
  
  for(pn = pq->head; pn->next != pq->tail; pn = pn->next){}
  pq->tail = pn;
  pn = pq->tail->next;   //tail-node;
  pq->tail->next = NULL;
  pq->size--;
  return pn;
}

int squeue_insert_a(struct squeue* pq, struct snode* pos, struct snode* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_SQUEUE_ARGS;
  }
  
  if(squeue_is_fully(pq))
  {
    return E_SQUEUE_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->next) || (pos == pq->tail) || squeue_is_empty(pq))
  {
    return squeue_add_tail(pq, pn);
  }
  
  //insart the new node pn after the pos;
  pn->next = pos->next;
  pos->next = pn;
  pq->size++;
  return E_SQUEUE_OK;
}

int squeue_insert_b(struct squeue* pq, struct snode* pos, struct snode* pn)
{
  struct snode* cur = NULL;
  if((NULL == pq) || (NULL == pn))
  {
    return E_SQUEUE_ARGS;
  }
  
  if(squeue_is_fully(pq))
  {
    return E_SQUEUE_FULL;
  }
  
  if((NULL == pos) || (pos == pq->head) || squeue_is_empty(pq))
  {
    return squeue_add_head(pq, pn);
  }
  
  //insart the new node pn before the pos;
  for(cur = pq->head; NULL != cur && cur->next != pos; cur = cur->next);
  if(NULL == cur)
  {
    return squeue_add_head(pq, pn);
  }
  
  // |_cur_|_next_|      |_pn_|_next_|      |_pos_|_next_|
  if(cur->next == pos)
  {
    pn->next = pos;
    cur->next = pn;
    pq->size++;
  }
  return E_SQUEUE_OK;
}

struct snode* squeue_remove(struct squeue* pq, struct snode* pn)
{
  struct snode* cur = NULL;
  if((NULL == pq) || (NULL == pn))
  {
    return NULL;
  }
  
  if(squeue_is_empty(pq))
  {
    return NULL;
  }
  
  if(pn == pq->head)
  {
    return squeue_del_head(pq);
  }
  
  if(pn == pq->tail)
  {
    return squeue_del_tail(pq);
  }
  
  for(cur = pq->head; NULL != cur && cur->next != pn; cur = cur->next);
  if(NULL == cur)
  {
    return NULL;
  }
  
  // |_cur_|_next_|      |_pn_|_next_|      |_pos_|_next_|
  if(cur->next == pn)
  {
    cur->next = pn->next;
    pq->size--;
  }
  return pn;
}


