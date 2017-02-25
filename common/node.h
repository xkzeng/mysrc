#pragma once

#ifndef __NODE_H__
#define __NODE_H__

struct node
{
  struct node* prev;
  struct node* next;
};

struct dnode
{
  struct dnode* prev;
  struct dnode* next;
};

struct snode
{
  struct snode* next;
};

#ifndef DEFINE_NODE
#define DEFINE_NODE(NODE_TYPE,NAME) \
struct ##NAME \
{ \
  NODE_TYPE* node;
#endif

#ifndef DEFINE_NODE_END
#define DEFINE_NODE_END(NAME) };
#endif

#ifndef DEFINE_NODE_PACK
#define DEFINE_NODE_PACK(NODE_TYPE,NAME,ALIGN) \
#pragma pack(ALIGN) \
struct ##NAME \
{ \
  NODE_TYPE* node;
#endif

#ifndef DEFINE_NODE_PACK_END
#define DEFINE_NODE_PACK_END(NAME) \
};\
#pragma pack()
#endif

#endif
