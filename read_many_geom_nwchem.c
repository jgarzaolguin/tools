#include <stdio.h>
#include <string.h>

int main() {
  int i, count, count_opt, count_char, test, test_2, test_Freq,
      flag, flag_opt, flag_atoms, flag_geom, flag_freq, flag_imag, atoms,
      int_1;
  double TE, dble_1, x, y, z;
  char word_1[200], word_2[200], word_3[200], word_4[200], symbol[200],
       name[100][200];
  FILE *archivo;

  flag = 0;
  count = 0;
  count_opt = 0;
  do {
    test = scanf("%s",word_1);
    if (test != EOF) {
      if (strcmp(word_1,"vectors") == 0 && flag == 0) {
        for (i = 1; i <= 4; i++) scanf("%s",word_2);
        count_char = 0;
        while(word_2[count_char] != '.') {
          name[count][count_char] = word_2[count_char];
          count_char++;
        }
        name[count][count_char] = '.';
        name[count][count_char+1] = 'x';
        name[count][count_char+2] = 'y';
        name[count][count_char+3] = 'z';
        printf("%s\n", name[count]);
        count++;
      }
      if (strcmp(word_1,"Optimization") == 0) {
        flag = 1;
        flag_atoms = 0;
        flag_opt = 0;
        flag_geom = 0;
        flag_freq = 0;
        flag_imag = 0;
        archivo = fopen(name[count_opt],"w");
        do {
          test_2 = scanf("%s",word_2);
          if (test_2 != EOF) {
            for (i = 1; i <= 2; i++) scanf("%s",word_3);
            if (strcmp(word_3,"atoms") == 0) {
              scanf("%s", word_4);
              scanf("%d",&atoms);
              fprintf(archivo,"%d\n", atoms);
              flag_atoms = 1;
            }
          }
        } while(test_2 != EOF && flag_atoms == 0);
        do {
          test_2 = scanf("%s",word_2);
          if (test_2 != EOF && strcmp(word_2,"Optimization") == 0) {
            for (i = 1; i <= 21; i++) scanf("%s",word_3);
            scanf("%lf", &TE);
            fprintf(archivo,"TE=%.10f\n", TE);
            flag_opt = 1;
          }
        } while(test_2 != EOF && flag_opt == 0);
        do {
          test_2 = scanf("%s",word_2);
          if (test_2 != EOF && strcmp(word_2,"Z") == 0) {
            for (i = 1; i <= 6; i++) scanf("%s",word_3);
            for (i = 1; i <= atoms; i++) {
              scanf("%d %s %lf %lf %lf %lf",&int_1, symbol, &dble_1, &x, &y, &z);
              fprintf(archivo,"%3s %12.8f %12.8f %12.8f\n", symbol, x, y, z);
            }
            flag_geom = 1;
          }
        } while(test_2 != EOF && flag_geom == 0);
        do {
          test_2 = scanf("%s",word_2);
          if (test_2 != EOF && strcmp(word_2,"Zero-Point") == 0) {
            for (i = 1; i <= 4; i++) scanf("%s",word_3);
            scanf("%lf", &dble_1);
            fprintf(archivo,"ZPE= %10.5f\n", dble_1);
            for (i = 1; i <= 19; i++) scanf("%s",word_3);
            scanf("%lf", &dble_1);
            fprintf(archivo,"H= %10.5f\n", dble_1);
            for (i = 1; i <= 7; i++) scanf("%s",word_3);
            scanf("%lf", &dble_1);
            fprintf(archivo,"S= %10.5f\n", dble_1);
            flag_freq = 1;
          }
        } while(test_2 != EOF && flag_freq == 0);
        do {
          test_2 = scanf("%s",word_2);
          if (test_2 != EOF && strcmp(word_2,"P.Frequency") == 0){
            scanf("%lf", &dble_1);
            fprintf(archivo,"Imag= %10.5f\n", dble_1);
            flag_imag = 1;
          }
        } while(test_2 != EOF && flag_imag == 0);
        fclose(archivo);
        count_opt++;
      }
    }
  } while (test != EOF);

  return 0;
}
