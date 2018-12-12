#include <stdio.h>
#include <stdint.h>
#include <string.h>

void quicksort(int * data, int min, int max) {
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
    return 0;
  }
  
  float div = (float)fsize / 100.0;
  int data[256] = {0};
  int sort[256] = {0};
  float procent;  
  int c;
  
  while ((c = fgetc(f)) != EOF)
    data[c] += 1;

  memcpy(sort, data, 256 * sizeof(int));
  quicksort(sort, 0, 256);

  fclose(f);

  printf("--------------------------------------\n");
  printf("| HEX | DEC | CHAR | COUNT | PROCENT |\n");
  printf("--------------------------------------\n");

  for (int i = 255, j = 0; (sort[i] > 0) && (j < 256); i--) {

  	j = 0;
    
    while (sort[i] != data[j])
      j++;

    if (sort[i] == 0 && data[j] == 0)
      continue;

    procent = (float)sort[i] / div;
    printf("|  %2.2X | %3d |    %c | %5d |  %5.2f%% |\n", (uint8_t)j, j, (chrcrt(j) ? (uint8_t)j : ' '), sort[i], procent);
  
    sort[i] = data[j] = 0;
  }

  printf("--------------------------------------\n");

  memset(data, 0, 256 * sizeof(int));
  return 0;
}