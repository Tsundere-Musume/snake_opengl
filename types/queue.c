#include "./types.h"

void tqueue_init(Queue *queue) {
  queue->head = 0;
  queue->tail = 0;
  queue->length = 0;
  queue->capacity = 0;
  queue->elements = NULL;
}

void tqueue_add(Queue *queue, int val) {
  if (queue->capacity == queue->length) {
    tqueue_grow(queue);
  }

  queue->length++;
  queue->elements[queue->tail] = val;
  queue->tail = (queue->tail + 1) % queue->capacity;
}


int tqueue_pop(Queue *queue) {
  if (queue->length <= 0) {
    fprintf(stderr, "ERROR::QUEUE::EMPTY");
    return -1;
  }
  int val = queue->elements[--queue->length];
  queue->head = (queue->head + 1) % queue->capacity;
  return val;
}


static void tqueue_grow(Queue *queue) {
  const int init_size = 8;
  int new_cap = queue->capacity < init_size ? init_size : queue->capacity * 2;

  int *arr = (int *)malloc(new_cap * sizeof(int));
  if (arr == NULL) {
    fprintf(stderr, "ERROR::QUEUE::GROW \"can't grow array\"");
    exit(74);
  }

  int i = 0, j = 0;
  while (i < queue->length) {
    arr[j++] = queue->elements[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    i++;
  }

  free(queue->elements);
  queue->elements = arr;

  queue->head = 0;
  queue->tail = queue->length;
  queue->capacity = new_cap;
}


static void tqueue_display(Queue *queue) {
  int h = queue->head, count = 0;
  while (count < queue->length) {
    printf("%d ", queue->elements[h]);
    h = (h + 1) % queue->capacity;
    count++;
  }
  printf("\n");
}

