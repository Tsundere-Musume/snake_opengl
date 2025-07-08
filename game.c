#include "types/types.h"
#include <stdbool.h>
#include <stdio.h>

#define TILE_COUNT 20

int tiles[TILE_COUNT][TILE_COUNT];

void game_render() {
  printf("%2s ", "");
  for (int i = 0; i < TILE_COUNT; ++i) {
    printf("%2d ", i);
  }
  printf("\n");
  for (int i = 0; i < TILE_COUNT; ++i) {
    printf("%2d ", i);
    for (int j = 0; j < TILE_COUNT; ++j) {
      printf("%2s ", "-");
    }
    printf("\n");
  }
}

int main(){
	while (true){
	}
}
