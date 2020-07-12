#include <src/queue.h>


void queue_init(struct queue_t* q)
{
    q->head_idx = 0;
    q->tail_idx = 0;
    q->size = 0;
    q->buffer = 0;
}


void queue_push_back(struct queue_t* q, uint8_t c)
{
    q->buffer[q->head_idx++] = c;
    if (q->head_idx >= q->size) {
        q->head_idx = 0;
    }

    // If buffer is full, remove oldest
    if (q->head_idx == q->tail_idx) {
        q->tail_idx++;
        if (q->tail_idx >= q->size) {
            q->tail_idx = 0;
        }
    }
}


uint8_t queue_pop_front(struct queue_t* q)
{
    uint8_t c;

    c = q->buffer[q->tail_idx++];
    if (q->tail_idx >= q->size) {
        q->tail_idx = 0;
    }

    return c;
}


int queue_empty(struct queue_t* q)
{
    if (q->head_idx == q->tail_idx)
         return 1;
     return 0;
}


unsigned int queue_size(struct queue_t* q)
{
    return q->size;
}

