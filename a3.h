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


#ifndef INCLUDED_A3_H
#define INCLUDED_A3_H

#include <stdlib.h>

typedef struct {
  unsigned char r,g,b;
} RGB;

typedef struct {
  RGB *image;
  double fitness;
//  double size;
} Individual;

RGB * readPPM(const char* file, int* width, int* height, int* max);
void  writePPM(const char* file, int width, int height, int max, const RGB *image);

RGB * randomImage(int width, int height, int max, long *seed);

#pragma acc routine seq
void  compFitness (const RGB *goal, Individual *I, RGB *curr, int width, int height);

void  mate (Individual *parent1, Individual *parent2, Individual *child1, Individual *child2, int width, int height, long *seed);
#pragma acc routine(mate) seq

#pragma acc routine seq
void  mutate (Individual *curr, int width, int height, int max, long *seed);

void compImage(const RGB *desired_image, int width, int height, int max,
	       int num_generations, int population_size,
	       RGB *found_image, const char *output_file, long *seed);

#endif
