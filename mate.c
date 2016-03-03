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
#ifdef _OPENACC
	#include <openacc.h>
#endif

void mate (Individual *parent1, Individual *parent2,
	   Individual *child1, Individual *child2, int width, int height, long *seed)
{

  int imageSize = width*height;
  int crossover = Random(imageSize, seed);
  int i;

	{
  #pragma omp parallel for
	#pragma acc loop independent worker
  for (i = 0; i < crossover; i++)
    {
      child1->image[i] = parent1->image[i];
      child2->image[i] = parent2->image[i];
    }
	}
  #pragma acc loop independent worker
  for (i = crossover; i < imageSize; i++)
    {
      child1->image[i] = parent2->image[i];
      child2->image[i] = parent1->image[i];
    }

}
