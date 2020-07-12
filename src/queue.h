#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>


struct queue_t
{
    uint8_t *buffer;
    unsigned int size;
    uint8_t head_idx;
    uint8_t tail_idx;
};


void queue_init(struct queue_t* q);
void queue_push_back(struct queue_t* q, uint8_t c);
uint8_t queue_pop_front(struct queue_t* q);
int queue_empty(struct queue_t* q);
unsigned int queue_size(struct queue_t* q);


#endif /* QUEUE_H_ */
