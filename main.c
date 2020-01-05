#include <stdio.h>
#include <stdlib.h>


int e_resistance(float orig_resistance, float *res_array) {

  const float resistors[] = {820000, 680000, 560000, 470000, 390000, 330000, 270000, 220000, 180000, 150000, 120000, 100000, 82000, 68000, 56000.0, 47000, 39000, 33000, 27000, 22000, 18000, 15000, 12000, 10000, 8200, 6800, 5600, 4700, 3900, 3300, 2700, 2200, 1800, 1500, 1200, 1000, 820, 680, 560, 470, 390, 330, 270, 220, 180, 150, 120, 100, 82, 68, 56, 47, 39, 33, 27,22, 18, 15, 12, 10, 8.2, 6.8, 5.6, 4.7, 3.9, 3.3, 2.7, 2.2, 1.8, 1.5, 1.2, 1.0, 0};
  int count = 0;
  int i = 0;
  int j = 0;
  int k = 0;

  float resistance;
  float best_resistance_diff = 100000; //arbitrary large number

  // Find the best combination of resistors
  for (i = 0; i < 74; ++i) {
    for (j = 0; j < 74; ++j) {
      for (k = 0; k < 74; ++k) {

        resistance = resistors[i] + resistors[j] + resistors[k];

        if (abs(orig_resistance - resistance) < best_resistance_diff) {
          best_resistance_diff = abs(orig_resistance - resistance);
          res_array[0] = resistors[i];
          res_array[1] = resistors[j];
          res_array[2] = resistors[k];
        }
      }
    }
  }

  // Check how many resistors there are in the best combination
  for (i = 0; i < 3; ++i) {
    if (res_array[i] != 0) {
      count = count + 1;
    }
  }

  return count;
}

float calc_power_r(float volt, float resistance) {
  return volt*volt / resistance;
}

float calc_power_i(float volt, float current) {
  return volt*current;
}

float calc_resistance(int count, char conn, float *array) {

  if (!array) {
    printf("Array of resistances is empty. Exiting.");
    return -1;
  }

  float sum = 0;
  int i = 0;

  if (conn == 'S') {
    for(i = 0; i < count; ++i) {
      sum += *(array + i);
    }
    return sum;

  } else if (conn == 'P') {
    for(i = 0; i < count; ++i) {
      if (*(array + i) == 0) {
        return 0;
      } else {
        sum += 1 / *(array + i);
      }
    }
    return 1 / sum;
 
  } else {
    printf("Unknown connection type. Use 'S' for series and 'P' for parallel. This program does not support mixed circuits.");
    return -1;
  }
}


int main(void) {
  float volt;
  printf("Ange spänningskälla i V: ");
  scanf("%f", &volt);

  char conn;
  printf("Ange koppling [S|P]: ");
  scanf("%s", &conn);

  int count;
  printf("Antal komponenter: ");
  scanf("%i", &count);

  float* array;
  array = malloc(sizeof(float)*count);
  int i = 0;
  for (i = 0; i < count; ++i) {
    printf("Komponent %i i ohm: ", i + 1);
    scanf("%f", array+i);
  }

  float orig_resistance;
  orig_resistance = calc_resistance(count, conn, array);
  printf("Ersättningsresistans:\n");
  printf("%.1f ohm\n", orig_resistance);
  free(array);

  float power;
  power = calc_power_r(volt, orig_resistance);
  printf("Effekt:\n");
  printf("%.2f W\n", power);

  float* res_array;
  res_array = malloc(sizeof(float)*count);
  i = 0;
  count = e_resistance(orig_resistance, res_array);
  printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");
  for (i = 0; i < count; ++i) {
    printf("%.0f\n", *(res_array+i));
  }
  free(res_array);

  return 0;
}
