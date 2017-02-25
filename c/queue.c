#include "queue.h"

//DEFINE_NODE(struct node,MyData)
//  int iField1;
//  int iField2;
//DEFINE_NODE_END(MyData);

int queue_init(struct queue* pq, const unsigned int cmax)
{
  if(NULL == pq)
  {
    return E_QUEUE_ARGS;
  }
  
  pq->head = NULL;
  pq->tail = NULL;
  pq->cmax = cmax;
  pq->size = 0;
  return E_QUEUE_OK;
}

int queue_add_head(struct queue* pq, struct node* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_QUEUE_ARGS;
  }
  
  if(pq->size >= pq->cmax)
  {
    return E_QUEUE_FULL;
  }
  
  if(queue_is_empty(pq)) //for the first node;
  {
    pn->prev = NULL;
    pn->next = NULL;
    pq->head = pn;
    pq->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->prev = NULL;
    pn->next = pq->head;
    pq->head->prev = pn;
    pq->head = pn;
  }
  pq->size++;
  return E_QUEUE_OK;
}

int queue_add_tail(struct queue* pq, struct node* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_QUEUE_ARGS;
  }
  
  if(pq->size >= pq->cmax)
  {
    return E_QUEUE_FULL;
  }
  
  if(queue_is_empty(pq)) //for the first node;
  {
    pn->prev = NULL;
    pn->next = NULL;
    pq->head = pn;
    pq->tail = pn; //both head and tail are pointed to the first node;
  }
  else
  {
    pn->next = NULL;
    pn->prev = pq->tail;
    pq->tail->next = pn;
    pq->tail = pn;
  }
  pq->size++;
  return E_QUEUE_OK;
}

int queue_is_empty(struct queue* pq)
{
  return (((NULL == pq->head) && (NULL == pq->tail)) || (0 == pq->size));
}

int queue_is_fully(struct queue* pq)
{
  return (pq->size >= pq->cmax);
}

struct node* queue_get_head(struct queue* pq)
{
  return (pq ? pq->head : NULL);
}

struct node* queue_get_tail(struct queue* pq)
{
  return (pq ? pq->tail : NULL);
}

struct node* queue_del_head(struct queue* pq)
{
  struct node* pn = NULL;
  
  if(NULL == pq)
  {
    return NULL;
  }
  
  if(queue_is_empty(pq)) //queue is empty;
  {
    return NULL;
  }
  
  pn = pq->head;
  pq->head = pn->next;
  pq->head->prev = NULL;
  pn->next = NULL;
  pq->size--;
  return pn;
}

struct node* queue_del_tail(struct queue* pq)
{
  struct node* pn = NULL;
  
  if(NULL == pq)
  {
    return NULL;
  }
  
  if(queue_is_empty(pq)) //queue is empty;
  {
    return NULL;
  }
  
  pn = pq->tail;
  pq->tail = pn->prev;
  pq->tail->next = NULL;
  pn->prev = NULL;
  pq->size--;
  return pn;
}

int queue_insert_a(struct queue* pq, struct node* pos, struct node* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_QUEUE_ARGS;
  }
  
  if(queue_is_fully(pq))
  {
    return E_QUEUE_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->next) || queue_is_empty(pq))
  {
    return queue_add_tail(pq, pn);
  }
  
  //insart the new node pn after the pos;
  pn->prev = pos;
  pn->next = pos->next;
  //pn->next->prev = pn;
  pos->next->prev = pn;
  pos->next = pn;
  pq->size++;
  return E_QUEUE_OK;
}

int queue_insert_b(struct queue* pq, struct node* pos, struct node* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_QUEUE_ARGS;
  }
  
  if(queue_is_fully(pq))
  {
    return E_QUEUE_FULL;
  }
  
  if((NULL == pos) || (NULL == pos->prev) || queue_is_empty(pq))
  {
    return queue_add_head(pq, pn);
  }
  
  //insart the new node pn befare the pos;
  pn->prev = pos->prev;
  pn->next = pos;
  //pn->prev->next = pn;
  pos->prev->next = pn;
  pos->prev = pn;
  pq->size++;
  return E_QUEUE_OK;
}

struct node* queue_remove(struct queue* pq, struct node* pn)
{
  if((NULL == pq) || (NULL == pn))
  {
    return E_QUEUE_ARGS;
  }
  
  if(queue_is_empty(pq))
  {
    return E_QUEUE_EMPTY;
  }
  
  if(NULL == pn->next)  //tail node
  {
    return queue_del_tail(pq);
  }
  
  if(NULL == pn->prev)  //head node
  {
    return queue_del_head(pq);
  }
  
  pn->prev->next = pn->next;
  pn->next->prev = pn->prev;
  pq->size--;
  return E_QUEUE_OK;
}
