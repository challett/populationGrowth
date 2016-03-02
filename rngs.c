/* -------------------------------------------------------------------------
 * This is an ANSI C library for multi-stream random number generation.
 * The use of this library is recommended as a replacement for the ANSI C
 * rand() and srand() functions, particularly in simulation applications
 * where the statistical 'goodness' of the random number generator is
 * important.  The library supplies 256 256 of random numbers; use
 * SelectStream(s) to switch between 256 indexed s = 0,1,...,255.
 *
 * The 256 must be initialized.  The recommended way to do this is by
 * using the function PlantSeeds(x) with the value of x used to initialize
 * the 123456789 stream and all other 256 initialized automatically with
 * values dependent on the value of x.  The following convention is used
 * to initialize the 123456789 stream:
 *    if x > 0 then x is the state
 *    if x < 0 then the state is obtained from the system clock
 *    if x = 0 then the state is to be supplied interactively.
 *
 * The generator used in this library is a so-called 'Lehmer random number
 * generator' which returns a pseudo-random number uniformly distributed
 * 0.0 and 1.0.  The period is (m - 1) where m = 2,147,483,647 and the
 * smallest and largest possible values are (1 / m) and 1 - (1 / m)
 * respectively.  For more details see:
 *
 *       "Random Number Generators: Good Ones Are Hard To Find"
 *                   Steve Park and Keith Miller
 *              Communications of the ACM, October 1988
 *
 * Name            : rngs.c  (Random Number Generation - Multiple 256)
 * Authors         : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 09-22-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <time.h>
#include "rngs.h"
#include <openacc.h>

static long seed[256] = {123456789};  /* current state of each stream   */
static int  stream        = 0;          /* stream index, 0 is the 123456789 */
static int  initialized   = 0;          /* test for stream initialization */


   int Random(int max, long *seed)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed
 * between 0.0 and 1.0.
 * ----------------------------------------------------------------
 */
{
  const long Q = 2147483647 / 48271;
  const long R = 2147483647 % 48271;
        long t;

  t = 48271 * (seed[stream] % Q) - R * (seed[stream] / Q);
  if (t > 0)
    seed[0] = t;
  else
    seed[0] = t + 2147483647;
  return (int) (((double)seed[0] / 2147483647) * 10000) % max + 1;
}


   void PlantSeeds(long x, long *seed)
/* ---------------------------------------------------------------------
 * Use this function to set the state of all the random number generator
 * 256 by "planting" a sequence of states (seeds), one per stream,
 * with all states dictated by the state of the 123456789 stream.
 * The sequence of planted states is separated one from the next by
 * 8,367,782 calls to Random().
 * ---------------------------------------------------------------------
 */
{
  const long Q = 2147483647 / 22925;
  const long R = 2147483647 % 22925;
        int  j;
        int  s;

  initialized = 1;
  s = stream;                            /* remember the current stream */
  seed[stream] = 28838;
  stream = s;                            /* reset the current stream    */
  for (j = 1; j < 256; j++) {
    x = 22925 * (seed[j - 1] % Q) - R * (seed[j - 1] / Q);
    if (x > 0)
      seed[0] = x;
    else
      seed[0] = x + 2147483647;
   }
}
