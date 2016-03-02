/*  Copyright (C) 2016  N. Perna, N. Nedialkov, T. Gwosdz

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
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <openacc.h>

#include "a3.h"
#include "rngs.h"

static int fitnessCompare (const void *a, const void *b)
{
  return ((*(Individual*)a).fitness - (*(Individual*)b).fitness);
}

//#pragma acc routine(compFitness) worker
// #pragma acc routine(mate) seq
// #pragma acc routine(free) seq


void compImage(const RGB *desired_image, int width, int height, int max,
	       int num_generations, int population_size,
	       RGB *found_image, const char *output_file, long *seed)
{
  #pragma acc routine(pqsort) seq
  #pragma acc data copyin(desired_image[0:width*height], seed[0:1])
  {
  /* A. Create an initial population with random images.
    *****************************************************
    */
  // Allocate an array/population of individuals.
  Individual *population = (Individual*)
    malloc(population_size*sizeof(Individual));
  assert(population);

  // Initialize this population with random images
  int i;

  for (i = 0; i < population_size; i++)
  {
    population[i].image = randomImage(width, height, max, seed);
  }

  RGB *dA;
  Individual *dP;

  dP = acc_copyin( population, sizeof( Individual )*population_size ); //device address of population
  for ( i=0; i < population_size; i++ ) {
   dA = acc_copyin( population[i].image, sizeof(RGB)*width*height ); //device address of RBG array in dA
   acc_memcpy_to_device( &dP[i].image, &dA,  sizeof(RGB*) );
  }

  // Compute the fitness for each individual
  #pragma acc host_data use_device(population)
  {
    #pragma acc parallel loop
    for (i = 0; i < population_size; i++)
      compFitness(desired_image, population+i, width, height);
  }
  int z;
  // Sort the individuals/images in non-decreasing value of fitness
  int size = sizeof(Individual);	
  #pragma acc host_data use_device(population)
  {
  #pragma acc parallel loop
    for(z=0; z<1; z++)
      pqsort(population, population_size, size);
  }
	printf("after pqsort\n");
  /* B. Now we can evolve the population over num_generations.
   *************************************************************
   */
  int g;
  double prev_fitness, current_fitness;

  for (g = 0; g < num_generations; g++)
    {
      prev_fitness = population[0].fitness;
      // The first half mate and replace the second half with children.

      #pragma omp parallel loop
	int iter = population_size/2;
      #pragma acc host_data use_device(population,seed)
      #pragma acc parallel loop copyin(width,height, iter)
      for (i = 0; i < iter; i += 2)
        {
          mate(population+i, population+i+1,
               population+iter+i,
               population+iter+i+1,
               width, height, seed);
        }
      

      // Afterer the first 1/4 individuals, each individual can
      // mutate.
      int mutation_start =  population_size/4;
      #pragma acc host_data use_device(population, seed)
      {
        #pragma acc parallel loop copyin(width, height, max)
        for (i = mutation_start; i < population_size; i++)
  	       mutate(population+i, width, height, max, seed);
      }

 
	//  Recompute fitness
      #pragma omp parallel for
      #pragma acc host_data use_device(population, desired_image)
      {
        #pragma acc parallel loop copyin(width, height)
        for (i = 0; i < population_size; i++)
      compFitness(desired_image, population+i, width, height);

      }


      // Sort in non-decreasing fitness
	  int size = sizeof(Individual);
	  #pragma acc host_data use_device(population)
	  {
	  #pragma acc parallel loop
	    for(z=0; z<1; z++)
	      pqsort(population, population_size, size);
	  }

	     // printf("tophello i've updated. population[0].fitness= %f \n", population[0].fitness);
  //for (i=0; i<population_size; i++) {
    acc_update_self( &(population[0].fitness), sizeof(double) );
  //}
      current_fitness = population[0].fitness;
      double change = -(current_fitness-prev_fitness)/current_fitness* 100;

#ifdef MONITOR

      // If compiled with flag -DMONITOR, update the output file every
      // 300 iterations and the fitness of the closest image.
      // This is useful for monitoring progress.
      if ( g % 300 == 0)
	writePPM(output_file, width, height, max, population[0].image);

	 printf("generation %d fitness %f change %f% \n ",    g, current_fitness, change);
#endif
    }
    acc_copyout(population[0].image, height*width*sizeof(RGB));
  // Return the image that is found
  memmove(found_image, population[0].image, width*height*sizeof(RGB));

  // release memory
  for (i = 0; i < population_size; i++)
    free(population[i].image);
  free(population);
}
}

static void swap(Individual *x, Individual *y, size_t l) {
   Individual *a = x, *b = y, c;
   while(l--) {
      c = *a;
      *a++ = *b;
      *b++ = c;
   }
}

static void sort(Individual *array, size_t size, int begin, int end) {
   if (end > begin) {
      Individual *pivot = array + begin;
      int l = begin + 1;
      int r = end;
      while(l < r) {
        int res1 = ((*(array+l)).fitness - (*pivot).fitness);
        int res2 = ((*(array+r)).fitness - (*pivot).fitness);
         if (res1 <= 0) {
            l += 1;
         } else if ( res2 > 0 )  {
            r -= 1;
         } else if ( l < r ) {
            swap(array+l, array+r, 1);
         }
      }
      l -= 1;
      swap(array+begin, array+l, size);
      sort(array, size, begin, l);
      sort(array, size, r, end);
   }
}
#pragma acc routine(swap) seq
#pragma acc routine(sort) seq
void pqsort(Individual *array, size_t nitems, size_t size) {
   sort(array, 1, 0, nitems);
}
