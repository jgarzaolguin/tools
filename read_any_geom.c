/* Program to read a geometry from a NWChem Output
 * Jorge Garza 
 * Initial Version Sept/2003
 * Current Version April/2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( )
{
 FILE *file_1, *file_2;
 int i, j, c, c1, c2, one, entry, geometries, number, total;
 double nucleus, x, y, z;

 char name[80], name_2[80], name_3[80], word1[80], word5[80], atom[5], scratch[80];

 printf("Utility to get any structure from a NWChem output\n");
 printf("Give me the NWChem output file name: ");
 scanf("%s", name);

 file_1 = fopen(name, "r");

 do
  c1 = fscanf(file_1,"%s",word1);
 while (strcmp(word1,"Optimization") != 0 && c1 != EOF);
 if ( c1 != EOF ) {
   do
     c2 = fscanf(file_1,"%s",word1);
   while (strcmp(word1,"atoms") != 0 && c1 != EOF);
   if (c2 != EOF) fscanf(file_1, "%s %d", word1, &total); 
 }

 if (c1 != EOF && c2 != EOF) {
   printf("Optimization module\n");
   printf("Number of atoms = %d\n", total);

   geometries = 0;
   do {
     c = fscanf(file_1,"%s",word1);
     one = strcmp(word1,"Geometry");
     if (one == 0) 
       geometries++;
   } while (c != EOF);
   rewind(file_1);

   printf("I found %d geometries, which one you want?:", geometries);
   scanf("%d", &entry);
   entry = entry + 2;
   geometries = 0;
   do {
     c = fscanf(file_1,"%s",word1);
     one = strcmp(word1,"Geometry");
     if (one == 0){
       geometries++;
       if (geometries == entry) {
         strcpy(name_2,"geom_tmp_");
         sprintf(name_3, "%d", entry - 2);
         strcat(name_2,name_3);
         strcat(name_2,".xyz");
         printf("Name of the output file : %s\n", name_2);
         file_2 = fopen(name_2, "w");
         fprintf(file_2,"%d\n", total);
         fprintf(file_2,"\n");
         for (i = 1; i <= 7 ; i++) fgets(word5,100,file_1);
         for (j = 1; j <= total; j++) {
            fscanf(file_1,"%d %s %lf %lf %lf %lf",&number, atom, &nucleus, &x, &y, &z);
            fprintf(file_2,"%s %f %f %f\n", atom, x, y, z);
         }
         close(file_2);
       }
     }
   } while (c != EOF);
  
 } else 
   printf("Please check the file because this is not a nwchem output file\n");
 close(file_1);
 return (1);
 }
