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

#include "a3.h"

static int fitnessCompare (const void *a, const void *b) 
{
  return ((*(Individual*)a).fitness - (*(Individual*)b).fitness);
}

void compImage(const RGB *desired_image, int width, int height, int max,
	       int num_generations, int population_size,
	       RGB *found_image, const char *output_file)
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
    population[i].image = randomImage(width, height, max);
  
  // Compute the fitness for each individual
  for (i = 0; i < population_size; i++) 
    compFitness(desired_image, population+i, width, height);
  
  // Sort the individuals/images in non-decreasing value of fitness
  qsort(population, population_size, sizeof(Individual), fitnessCompare);
  
  /* B. Now we can evolve the population over num_generations.
   *************************************************************
   */
  int g;
  double prev_fitness, current_fitness;
  for (g = 0; g < num_generations; g++) 
    {
      prev_fitness = population[0].fitness;
      // The first half mate and replace the second half with children.
      for (i = 0; i < population_size/2; i += 2) 
	{
	  mate(population+i, population+i+1, 
	       population+population_size/2+i,
	       population+population_size/2+i+1,
	       width, height);
	}
	  
      // Afterer the first 1/4 individuals, each individual can
      // mutate.
      int mutation_start =  population_size/4;
      for (i = mutation_start; i < population_size; i++) 
	mutate(population+i, width, height, max);
      
      //  Recompute fitness 
      for (i = 0; i < population_size; i++) 
	compFitness(desired_image, population+i, width, height);
      
      // Sort in non-decreasing fitness
      qsort(population, population_size, sizeof(Individual), fitnessCompare);
      current_fitness = population[0].fitness;

      double change = -(current_fitness-prev_fitness)/current_fitness* 100;
	
#ifdef MONITOR
      // If compiled with flag -DMONITOR, update the output file every
      // 300 iterations and the fitness of the closest image.
      // This is useful for monitoring progress.
      if ( g % 300 == 0)
	writePPM(output_file, width, height, max, population[0].image);
            
      printf(" generation % 5d fitness %e  change from prev %.2e%c \n",
	     g, current_fitness, change, 37);
#endif
    }

  // Return the image that is found
  memmove(found_image, population[0].image, width*height*sizeof(RGB));
  
  // release memory
  for (i = 0; i < population_size; i++) 
    free(population[i].image);
  free(population);
}
