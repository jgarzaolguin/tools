/* Program to read ONE optimized geometry from a NWChem Output
 * Jorge Garza 
 * Initial Version Sept/2003
 * Current Version April/2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( )
{
 int i, j, c, c1, c2, one, entry, geometries, number, total, tot_geom, 
     iter;
 double nucleus, x, y, z, TE;

 char name[80], name_2[80], name_3[80], word1[80], word2[80], atom[5], scratch[80];

 iter = 0;
 c = 0;

 do {
   c2 = scanf("%s",word1);
 } while (strcmp(word1,"Wavefunction") != 0 && c2 != EOF);

 do {
   c2 = scanf("%s",word1);
 } while (strcmp(word1,"atoms") != 0 && c2 != EOF);
 if (c2 != EOF) {
   scanf("%s %d", word1, &total);
   printf("%d\n", total);
 }

 do {
   c1 = scanf("%s",word1);
   if (c1 != EOF) {
     if (c == 0 && strcmp("Optimization",word1) == 0) c = 1;
     if (c == 1 && strcmp("Optimization",word1) == 0) c = 2;
     if (c == 2) {
       if (strcmp(word1,"Walltime") == 0) {
         c = 3;
         for (i = 1; i <= 10; i++) {
           scanf("%s", scratch);
         }
         scanf("%lf", &TE);
         printf("TE=%16.8f\n", TE);
         do {
    c2 = scanf("%s",word1);
   } while (strcmp(word1,"Geometry") != 0 && c2 != EOF);
   for (i = 1; i <= 27 ; i++) scanf("%s",word2);
   for (j = 1; j <= total; j++) {
      scanf("%d %s %lf %lf %lf %lf",&number, atom, &nucleus, &x, &y, &z);
      printf("%3s %16.8f %16.8f %16.8f\n", atom, x, y, z);
   }
       }
     }
   }
 } while (c1 != EOF);

 return 1;
 }
