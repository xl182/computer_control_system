#include "queue.h"
#include <assert.h>
#include <stdlib.h>

int push(queue *q, uint16_t val) {
    q->length += 1;
    q->sum += val;
    q->nums[q->tail] = val;
    q->tail = (q->tail + 1) % (q->N + 1);
}

uint16_t get(queue *q) {
    return q->nums[q->head];
}

uint16_t get_tail(queue *q) {
    return q->nums[q->tail];
}

uint16_t pop_head(queue *q) {
    uint16_t val;
    q->length -= 1;
    val = q->nums[q->head];
    q->sum -= val;
    q->head = (q->head + 1) % (q->N + 1);
    return val;
}

uint16_t get_average(queue *q) {
    assert(q->length > 0);
    uint16_t val = q->sum / (uint16_t) q->length;
    return val;
}

uint16_t get_val(queue *q, int index) {
    return q->nums[(q->head + index + q->N) % q->N];
}

void set_val(queue *q, int index, uint16_t val)
{
    q->nums[(q->head + index + q->N) % q->N] = val;
}

void init_queue(queue *q, int N) {
    q->N = N;
    q->nums = (uint16_t *) malloc(N * sizeof(uint16_t));
    q->head = 0;
    q->tail = 0;
    q->sum = 0;
    q->get = get;
    q->get_tail = get_tail;
    q->push = push;
    q->pop_head = pop_head;
    q->get_average = get_average;
    q->get_val = get_val;
    q->set_val = set_val;
}


void reset_queue(queue *q) {
    // reset queue
    q->nums = (uint16_t *) malloc(q->N * sizeof(uint16_t));
    q->sum = 0;
    q->length = 0;
    q->head = 0;
    q->tail = 0;
}
