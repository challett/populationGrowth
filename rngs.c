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


#include "rngs.h"
#include <openacc.h>


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

  t = 48271 * (seed[0] % Q) - R * (seed[0] / Q);
  if (t > 0)
    seed[0] = t;
  else
    seed[0] = t + 2147483647;
  return (int) (((double)seed[0] / 2147483647) * 10000) % max + 1;
}
