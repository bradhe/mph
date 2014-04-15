#include "mph.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PRIME   199

int run() {
  // Creating a filled vector
  unsigned int i = 0;
  unsigned long vector[5000];
  unsigned int nkeys = 5000;

  for(i = 0; i < 5000; i++) {
    vector[i] = (unsigned long)(i % 2000);
  }

	mph_t * mph = mph_new(vector, nkeys);

	if(!mph) {
		fprintf(stderr, "Failed to generate hash function.\n");
		return 1;
	}

	for(int j = 0; j < 5000; j++) {
		for(int i = 0; i < nkeys; i++) {
			mph_get_index(mph, vector[i]);
		}
	}

	mph_destroy(mph);

  return 0;
}

int main(void) {
  run();
}
