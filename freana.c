#include <stdio.h>
#include <stdint.h>
#include <string.h>

void quicksort(long int * data, int min, int max) {
  if (min < max) {
    int left = min, right = max, middle = data[(left + right) / 2];
      do {
        while (data[left] < middle)
          left++;
        
        while (data[right] > middle)
          right--;
        
        if (left <= right) {
          int tmp = data[left];
          data[left] = data[right];
          data[right] = tmp;
          left++;
          right--;
        }
      } while (left <= right);

    quicksort(data, min, right);
    quicksort(data, left, max);
  }
}

int chrcrt (int c) {
  if (c <  33 || c >  126)
    return 0;
  else
  if (c >= 33 && c <= 126)
    return c;
}

int main (int argc, uint8_t * argv[]) {

  if (argc != 2) {
    printf("[#] Incorrect arguments!\n");
    printf("[#] Enter: %s [filename]\n", argv[0]);
    return 0;
  }
  
  FILE * f = fopen(argv[1], "rb");
 
  if (f == NULL) {
    printf("[#] File \"%s\" not openned!\n", argv[1]);
    return 0;
  }

  fseek(f, 0, SEEK_END);
  long int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  
  if (fsize <= 0) {
    printf("[#] Size of file \"%s\" not more 0 byte!", argv[1]);
    fclose(f);
    return 0;
  }
  
  float div = (float)fsize / 100.0;
  long int data[256] = {0};
  long int sort[256] = {0};
  float procent;  
  int c;
  
  while ((c = fgetc(f)) != EOF)
    data[c] += 1;

  memcpy(sort, data, 256 * sizeof(long int));
  quicksort(sort, 0, 256);

  fclose(f);

  printf("------------------------------------------\n");
  printf("| HEX | DEC | CHR |  FREQUENCY | PROCENT |\n");
  printf("------------------------------------------\n");

  for (int i = 255, j = 255; (i >= 0) && (j >= 0) && (sort[i] > 0); i--) {

    j = 255;

    while ((j > 0) && (sort[i] != data[j]))
      j--;

    if ((j < 0) || (data[j] == -1))
      continue;

    procent = (float)sort[i] / div;
    printf("|  %2.2X | %3d |   %c | %10ld |  %5.2f%% |\n", (uint8_t)j, j, (chrcrt(j) ? (uint8_t)j : ' '), sort[i], procent);
    fflush(stdin);

    sort[i] = data[j] = -1;
  }

  printf("------------------------------------------\n");

  memset(data, 0, 256 * sizeof(long int));
  memset(sort, 0, 256 * sizeof(long int));
  return 0;
}