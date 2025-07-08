#ifndef SNAKE_TYPES
#define SNAKE_TYPES

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int head;
  int tail;
  int length;
  int capacity;
  int *elements;
} Queue;

void tqueue_init(Queue *queue);
void tqueue_add(Queue *queue, int val);
int tqueue_pop(Queue *queue);
static void tqueue_grow(Queue *queue);
static void tqueue_display(Queue *queue);
#endif
