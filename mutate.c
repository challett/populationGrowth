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

void mutate (Individual *curr, int width, int height, int max, long *seed)
{
  // Set how many pixels to mutate. The constant 500 is somewhat
  // random. You can experiment with different constants.
  int rate = width*height/500;

  long s = *seed;
  int i,j;
  #pragma acc loop
  for(i=0; i < rate; i++)
    {
      s+=i;
      // Pick a pixel at random.
      int size = width*height;
      j = Random(size ,seed);
      // and modify it
      (curr->image)[j].r = Random(max, &(s));
      (curr->image)[j].g = Random(max, &(s));
      (curr->image)[j].b = Random(max, &(s));

    }
}
