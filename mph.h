#ifndef _MPH_H
#define _MPH_H

#include <cmph.h>
#include <stdlib.h>
#include <string.h>

#define RADIX_BASE    10

typedef struct {
	/* count of all the keys in the list. */
	int n;

	/* calculated hash from cmph */
  cmph_t *hash;
} mph_t;

mph_t * mph_new(unsigned long *, int);
void mph_destroy(mph_t *);
unsigned int mph_get_index(mph_t *, unsigned long);

#endif
