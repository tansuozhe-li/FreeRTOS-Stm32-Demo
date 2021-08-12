//环形队列
#include "common.h"
#include "ring_queue.h"


//初始化队列
int InitRingQueue(RingQueue *q, RQ_ElementType *buff, int size)
{
   q->elems = buff;
   q->size  = size;
   q->front = q->rear = 0;
   return RQ_OK;
}

//遍历队列
int ShowRingQueue(RingQueue *q)
{
  int rear = q->rear;
  
  if(q->front == rear)
  {
    return RQ_ERROR;  //队列为空
  }
  return RQ_OK;
}

//向队尾插入元素e
int InRingQueue(RingQueue *q,RQ_ElementType e)
{
  if(RingQueueFull(q))
  {
    return RQ_OVERFLOW; //队列溢出
  }
  q->elems[q->rear] = e;
  q->rear = (q->rear+1) % q->size;
  return RQ_OK;  
}

//从队首取回并删除元素
int OutRingQueue(RingQueue *q,RQ_ElementType *e)
{
  if(RingQueueEmpty(q))
  {
    return RQ_ERROR;
  }
  *e = q->elems[q->front];
  q->front = (q->front+1) % q->size;
  return RQ_OK;
}

//队列中元素的个数
int RingQueueLength(RingQueue *q)
{
  return ((q->rear - q->front) + q->size) % q->size;
}
