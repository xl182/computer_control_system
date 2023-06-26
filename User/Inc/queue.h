#ifndef __QUEUE_H__
#define __QUEUE_H__

//
// Created by ALIEN on 2023/3/27.
//
#include "main.h"

typedef struct queue {
    uint16_t *nums;
    int N;
    int head;
    int tail;
    uint16_t sum;
    int length;

    uint16_t (*get_average)(struct queue *);

    uint16_t (*pop_head)(struct queue *);

    int (*push)(struct queue *, uint16_t);

    uint16_t (*get)(struct queue *);
    uint16_t (*get_tail)(struct queue *);

    uint16_t (*get_val)(struct queue *, int);

    void (*set_val)(struct queue *, int, uint16_t);
} queue;

typedef struct symbol_queue {
    int positive_symbols;
    int negative_symbols;
} symbol_counter;

void init_queue(queue *q, int N);

#endif //TEST_N_QUEUE_H
