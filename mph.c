#include "mph.h"

/* internal functions. don't want to export these. */
int mph_radixsort(unsigned long*, int);

mph_t * mph_new(unsigned long *arr, int n) {
	mph_t * mph = malloc(sizeof(mph_t));
	memset(mph, '\0', sizeof(mph_t));

	/* don't fuck with someone else's data. */
	unsigned long *copy = malloc(sizeof(unsigned long) * n);
	memcpy(copy, arr, sizeof(unsigned long) * n);

	/* Get the actual number of keys... */
	mph->n = mph_radixsort(copy, n);

  cmph_io_adapter_t *source = cmph_io_struct_vector_adapter((void *)copy, sizeof(unsigned long), 0, sizeof(unsigned long), mph->n);

  if(!source) {
		/* cleanup! */
		free(mph);
		free(copy);
    return NULL;
  }

  cmph_config_t *config = cmph_config_new(source);

  if(!config) {
		/* cleanup! */
		free(mph);
		free(copy);

    cmph_io_vector_adapter_destroy(source);
    return NULL;
  }

  cmph_config_set_algo(config, CMPH_CHD);
  cmph_t *hash = cmph_new(config);

  if(!hash) {
		/* cleanup! */
		free(mph);
		free(copy);

    cmph_io_vector_adapter_destroy(source);
    cmph_config_destroy(config);
    return NULL;
  }

	mph->hash = hash;

	/* Otherwise, we got it! */
	cmph_io_vector_adapter_destroy(source);
	cmph_config_destroy(config);
	free(copy);

	return mph;
}

void mph_destroy(mph_t * mph) {
	/* Some people are dumb. */
	if(mph == NULL) {
		return;
	}

	if(mph->hash != NULL) {
		cmph_destroy(mph->hash);
	}

	free(mph);
}

unsigned int mph_get_index(mph_t * mph, unsigned long key) {
  return cmph_search(mph->hash, (char *)&key, sizeof(key));
}

/**
 * This is an implementation of radixsort basically ripped off of Google and
 * adapted to sort arrays of unsigned long specifically. My analysis shows that
 * it's supposedly O(n log n) in the worse case.
 *
 * It's also been adapted to remove duplicate values.
 */
int mph_radixsort(unsigned long *a, int n) {
  unsigned long *b = 0;
  unsigned long m = a[0];
  int i, exp = 1, count = 0;

  b = malloc(n * sizeof(unsigned long));

	/* Get the greatest value in the array a and assign it to m */
  for (i = 1; i < n; i++) {
    if (a[i] > m)
      m = a[i];
  }

  /* Loop until exp is bigger than the largest number */
  while (m / exp > 0) {
    int bucket[RADIX_BASE] = { 0 };

    /* Count the number of keys that will go into each bucket */
    for (i = 0; i < n; i++) {
      bucket[(a[i] / exp) % RADIX_BASE]++;
		}

		/* Add the count of the previous buckets to acquire the indexes after the
		 * end of each bucket location in the array */
    for (i = 1; i < RADIX_BASE; i++) {
      bucket[i] += bucket[i - 1];
		}

		/* Starting at the end of the list, get the index corresponding to the
		 * a[i]'s key, decrement it, and use it to place a[i] into array b. */
    for (i = n - 1; i >= 0; i--) {
      b[--bucket[(a[i] / exp) % RADIX_BASE]] = a[i];
		}

    /* Copy array b to array a */
    count = 0;
    for (i = 0; i < n; i++) {
			/* This removed duplicates */
      if(count < 1 || (a[count-1] != b[i])) {
        a[count] = b[i];
        count++;
      }
    }

    //Multiply exp by the RADIX_BASE to get the next group of keys
    exp *= RADIX_BASE;
  }

  free(b);
  return count;
}
