/* -----------------------------------------------------------------------
 * Name            : rngs.h  (header file for the library file rngs.c)
 * Author          : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 09-22-98
 * -----------------------------------------------------------------------
 */

#if !defined( _RNGS_ )
#define _RNGS_

#pragma acc routine seq
int Random(int max, long *seeds);
void   PlantSeeds(long x, long *seeds);
#endif
