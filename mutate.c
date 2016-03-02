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

void mutate (Individual *curr, int width, int height, int max)
{
  // #pragma acc routine(rand) seq
  // Set how many pixels to mutate. The constant 500 is somewhat
  // random. You can experiment with different constants.
  int rate = width*height/500;


  int i,j;

  for(i=0; i < rate; i++)
    {
      // Pick a pixel at random.
      j = rand() % (width*height);
      // and modify it
      (curr->image)[j].r = RANDOM(max);
      (curr->image)[j].g = RANDOM(max);
      (curr->image)[j].b = RANDOM(max);

    }
}
