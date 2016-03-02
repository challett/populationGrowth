#include <stdlib.h>
#include <stdio.h>
#include "a3.h"

static void swap(Individual *x, Individual *y, size_t l) {
   Individual *a = x, *b = y, c;
   while(l--) {
      c = *a;
      *a++ = *b;
      *b++ = c;
   }
}

static void sort(Individual *array, size_t size,int begin, int end) {
   if (end > begin) {
      Individual *pivot = array + begin;
      int l = begin + size; 
      int r = end;
      while(l < r) {
		  int res1 = ((*(array+l)).fitness - (*pivot).fitness);
		  int res2 = ((*(array+r)).fitness - (*pivot).fitness);
         if (res1 >= 0) {
            l += size;
         } else if ( res2 > 0)  {
            r -= size;
         } else if ( l < r ) {
            swap(array+l, array+r, size);
         }
      }
      l -= size;
      swap(array+begin, array+l, size);
      sort(array, size, begin, l);
      sort(array, size, r, end);
   }
}

void quicksort(void *array, size_t nitems, size_t size) {
   sort(array, 1, 0, nitems);
}

