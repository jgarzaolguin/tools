/* Program to read a geometry from a NWChem Output
 * Jorge Garza 
 * Initial Version Sept/2003
 * Current Version April/2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_optimization(FILE *file_1, char *word1, int *c1) {
  do
    *c1 = fscanf(file_1,"%s",word1);
  while (strcmp(word1,"Optimization") != 0 && *c1 != EOF);
  return 0;
}

int search_optimization_or_failed(FILE *file_1, char *word1) {
  int c1, geometries;
  geometries = 0;
  do {
    c1 = fscanf(file_1,"%s",word1);
    if (strcmp(word1,"@") == 0) geometries++; 
  } while (strcmp(word1,"Optimization") != 0 && strcmp(word1,"Failed") != 0 && c1 != EOF);
  return geometries;
}

int read_opt_energy(int iter, int c1, FILE *file_1) {
  int i, c2, j, number, total;
  char atom[5], name_2[80], word1[80], word5[80], scratch[80];
  double nucleus, x, y, z, TE;

  FILE *file_2;

  if ( c1 != EOF ) {
     do
       c2 = fscanf(file_1,"%s",word1); 
     while (strcmp(word1,"atoms") != 0 && c2 != EOF);
     if (c2 != EOF) fscanf(file_1, "%s %d", word1, &total);
   }
   do {
    c1 = fscanf(file_1,"%s",word1);
   } while (strcmp(word1,"Optimization") != 0 && strcmp(word1,"Failed") != 0 && c1 != EOF);
   do {
    c1 = fscanf(file_1,"%s",word1);
   } while (strcmp(word1,"Walltime") != 0 && c1 != EOF);
   for (i = 1; i <= 10; i++) {
     fscanf(file_1,"%s", scratch);
   }
   fscanf(file_1,"%lf", &TE);
   if (iter == 1)
     strcpy(name_2,"geom_tmp_1.xyz");
   else
     strcpy(name_2,"geom_tmp_2.xyz");
   file_2 = fopen(name_2, "w");
   fprintf(file_2,"%d\n", total);
   fprintf(file_2,"TE=%.8f\n", TE);
   do {
    c1 = fscanf(file_1,"%s",word1);
   } while (strcmp(word1,"Geometry") != 0 && c1 != EOF);
   for (i = 1; i <= 7 ; i++) fgets(word5,100,file_1);
   for (j = 1; j <= total; j++) {
      fscanf(file_1,"%d %s %lf %lf %lf %lf",&number, atom, &nucleus, &x, &y, &z);
      fprintf(file_2,"%3s %16.8f %16.8f %16.8f\n", atom, x, y, z);
   }
   close(file_2);
}

int main( )
{
 FILE *file_1, *file_2;
 int i, j, c, c1, c2, one, entry, geometries, number, total, tot_geom, 
     iter;
 double nucleus, x, y, z, TE;

 char name[80], name_2[80], name_3[80], word1[80], word5[80], atom[5], scratch[80];

 printf("Utility to get any structure from a NWChem output\n");
 printf("Give me the NWChem output file name: ");
 scanf("%s", name);

 file_1 = fopen(name, "r");

 string_optimization(file_1, word1, &c1);

 if (c1 != EOF) {
   printf("Optimizaion job\n");
   iter = 1;
   geometries = search_optimization_or_failed(file_1, word1);
   if (c1 != EOF) {
     if (strcmp(word1,"Optimization") == 0)  {
       printf("The geometry process was reached in %d steps.\n", geometries - 3);
       string_optimization(file_1, word1, &c1);
       if (strcmp(word1,"Optimization") == 0)  {
         printf("There is another optimization process\n"); 
         iter++;
         geometries = search_optimization_or_failed(file_1, word1);
         if (strcmp(word1,"Optimization") == 0)  
           printf("The geometry process was reached in %d steps.\n", geometries - 3);
       }
     } 
     else
       printf("Maximum number of steps in the optimization process.\n");
   } else
     printf("The geometry process was not reached in %d steps.\n", geometries - 3);
   rewind(file_1);
   for (i = 1; i <= iter; i++) {
     string_optimization(file_1, word1, &c1);
     read_opt_energy(i, c1, file_1);
   }
 } else {
   printf("This job is not an optimization process, I cannot do nothig for you!\n");
 }

 close(file_1);
 return (1);
 }
