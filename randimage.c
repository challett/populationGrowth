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


#include <assert.h>
#include "a3.h"

// This function generates a random width x height image. max is the
// largest RGB value in the original image.
RGB * randomImage(int width, int height, int max) 
{
  RGB *image = (RGB*)malloc(width*height*sizeof(RGB));
  assert(image);
  int i;
  for(i=0; i < width * height; i++) 
    {
      image[i].r = RANDOM(max);
      image[i].g = RANDOM(max);
      image[i].b = RANDOM(max);
    }
  return image;
}


