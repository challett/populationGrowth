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

void mate (Individual *parent1, Individual *parent2, 
	   Individual *child1, Individual *child2, int width, int height) 
{
  int crossover = RANDOM(width*height-1);
  int i;
  
  for (i = 0; i < crossover; i++) 
    {
      child1->image[i] = parent1->image[i];
      child2->image[i] = parent2->image[i];
    }
  for (i = crossover; i < width*height; i++) 
    {
      child1->image[i] = parent2->image[i];
      child2->image[i] = parent1->image[i];
    }
}

