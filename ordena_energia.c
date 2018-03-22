// Program to sort entries in second column
// Jorge Garza. March, 2018
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( ) {
  int i, j, imin, c1, count, iter, intern;
  double temp, convert, trash_dble_1, trash_dble_2, trash_dble_3,
         min;

  double array_energ[10000];
  char word[200], word2[200], name[300][30];

  convert = 627.509608f;

  count = 0;
  do {
    c1 = scanf("%s", word);
    if (c1 != EOF) {
        scanf("%lf", &trash_dble_1);
        array_energ[count] = trash_dble_1;
        strcpy(name[count],word);
        count++;
      }
  } while(c1 != EOF);

  printf("%d isomers\n", count);

  for (i = 0; i < count; i++) {
    for (j = i+1; j < count; j++) {
      if (array_energ[j] <= array_energ[i]) {
        temp = array_energ[i];
        strcpy(word,name[i]);
        array_energ[i] = array_energ[j];
        strcpy(name[i],name[j]);
        array_energ[j] = temp;
        strcpy(name[j],word);
      }
    }
  }
//
  for (i = 0; i < count; i++) {
    printf("%30s %16.6f %6.1f\n", name[i], array_energ[i], 627.51f*(array_energ[i] - array_energ[0]));
  }
 
  return 1;
}
