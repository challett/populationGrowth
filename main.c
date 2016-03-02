/*
    Copyright (C) 2016  N. Perna, N. Nedialkov, T. Gwosdz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdlib.h>
#include <assert.h>
#include "a3.h"
#include "rngs.h"
#include <omp.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
  long seed = 2342324 ;

  clock_t starttime, endtime;
  double runtime;

  const char *input_file  = argv[1];
  const char *output_file = argv[2];

  int num_generations = atoi(argv[3]);
  int population_size = atoi(argv[4]);
  // population size, must be multiple of 4 right now
  assert(population_size % 4 == 0);

  // Load the desired image
  RGB *desired_image;
  int width, height, max;
  desired_image = readPPM(input_file, &width, &height, &max);

  // Compute an image
  starttime = clock();

  double ctime1;
  #ifdef _OPENMP
  ctime1 = omp_get_wtime();
  #endif
	printf("starting compImage%d\n", 0);
  RGB *found_image = (RGB*)malloc(width*height*sizeof(RGB));
  compImage(desired_image, width, height, max,
	    num_generations, population_size, found_image, output_file, &seed);

  double ctime2;
  #ifdef _OPENMP
    ctime2 = omp_get_wtime();
  #endif
  printf("%f seconds.\n", ctime2 - ctime1);

  endtime = clock();
  // Write it back into an output file
  writePPM(output_file, width, height, max, found_image);

  runtime = (double)(endtime-starttime)/CLOCKS_PER_SEC;
  printf("Computation time %f seconds\n", runtime);
  free(found_image);
  free(desired_image);

  return(0);
}
