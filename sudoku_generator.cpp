#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstring>

#define setBit(var, bit)    var |= 1 << bit
#define checkBit(var, bit)  var & (1 << bit)

enum { CLEAN = -1, LINE, ROW, SECTOR };

struct _cell {
  uint8_t  value, line, row, sector;
  uint16_t used;
};

typedef struct _cell t_cell;

t_cell *checkBox[3][9][9];
t_cell  sol[81];

int checkCell(int cell);

int
main(int argc, char **argv)
{
  register int i, j = 0;
  int u = 0;

  memset(checkBox, 0, sizeof(checkBox));
  memset(sol, 0, sizeof(sol));

  /* Initialization */
  for(i = 0; i < 81; i++) {
    sol[i].line   = i / 9;
    sol[i].row    = i % 9;
    sol[i].sector = (((i / 9) / 3) * 3) + ((i % 9) / 3);
    checkBox[LINE][i / 9][i % 9] = &sol[i];
    checkBox[ ROW][i % 9][i / 9] = &sol[i];
    while(checkBox[SECTOR][sol[i].sector][j])
      ++j;
    checkBox[SECTOR][sol[i].sector][j] = &sol[i];
    j = 0;
  }

  srand(time(NULL));

  /* Generate solution */
  for(i = 0; i < 81; i++) {
    do {
      do {
        u = 0;
        if(sol[i].used == 511) {
          setBit(sol[i-1].used, (sol[i-1].value - 1));
          sol[i].used = sol[i].value = 0;
          i -= 2;
          u = 1;
          break;
        }
        sol[i].value = 1 + rand() % 9;
      } while((checkBit(sol[i].used, (sol[i].value - 1))));
      if(u)
        break;
    } while(checkCell(i) != CLEAN);
  }

  /* Display result */
  for(i = 0; i < 9; i++) {
    printf(" %d   %d   %d   %d   %d   %d   %d   %d   %d \n",
      sol[i*9].value,   sol[i*9+1].value, sol[i*9+2].value,
      sol[i*9+3].value, sol[i*9+4].value, sol[i*9+5].value,
      sol[i*9+6].value, sol[i*9+7].value, sol[i*9+8].value
    );
  }
  printf("-------------------------\n");

  return 0;
}

int
checkCell(int cell)
{
  register int i;
  int result = CLEAN;

  for(i = 0; i < 9; i++) {
    if(&sol[cell] != checkBox[LINE][sol[cell].line][i]) {
      if(sol[cell].value == checkBox[LINE][sol[cell].line][i]->value)
        result = LINE;
    }
    if(&sol[cell] != checkBox[ROW][sol[cell].row][i]) {
      if(sol[cell].value == checkBox[ROW][sol[cell].row][i]->value)
        result = ROW;
    }
    if(&sol[cell] != checkBox[SECTOR][sol[cell].sector][i]) {
      if(sol[cell].value == checkBox[SECTOR][sol[cell].sector][i]->value)
        result = SECTOR;
    }
  }
  if(result != CLEAN) {
    setBit(sol[cell].used, (sol[cell].value - 1));
  }

  return result;
}
