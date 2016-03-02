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


#include "a3.h"
#include "rngs.h"
#include <omp.h>
#include <stdio.h>

//#include <curand_kernel.h>
#include <cuda.h>
#include <curand.h>
#include <openacc.h>


#pragma acc routine seq
void mate (Individual *parent1, Individual *parent2,
	   Individual *child1, Individual *child2, int width, int height)
{

//	curand_init(1234, 0, 0, 0);
	//curandGenerator_t g;

  int crossover = 5 % (width*height);
  int i;
  int imageSize = width*height;
//	curandCreateGenerator(&g, CURAND_RNG_PSEUDO_DEFAULT);
  #pragma omp parallel for
  for (i = 0; i < crossover; i++)
    {
      child1->image[i] = parent1->image[i];
      child2->image[i] = parent2->image[i];
    }
  //#pragma acc parallel loop copy(child1Image[1:imageSize], child2Image[1:imageSize], parent1Image[1:imageSize], parent2Image[1:imageSize])
  for (i = crossover; i < imageSize; i++)
    {
      child1->image[i] = parent2->image[i];
      child2->image[i] = parent1->image[i];
    }
}
