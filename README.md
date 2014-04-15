# libmph

This is a simple wrapper around [CMPH](http://cmph.sourceforge.net/)
specifically for building minimal perfect hash functions for lists of integers.

This wrapper adds support for deduplicating the list of keys before generating
the hash function.

## Installation

Pretty straight forward

```bash
$ ./configure
...
$ make && sudo make install
```

## Example

Here's an example of how to use this bad boy!

```c
#include <mph.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Create and fill a vector of integers. */
  unsigned int i = 0;
  unsigned long vector[5000];
  unsigned int nkeys = 5000;

  for(i = 0; i < 5000; i++) {
    vector[i] = (unsigned long)(i % 2000);
  }

  /* Create a new hash, this actually generates the function too. */
  mph_t * mph = mph_new(vector, nkeys);

  if(!mph) {
    fprintf(stderr, "Failed to generate hash function.\n");
    return 1;
  }

  /* Given a key, look up the index */
  for(int i = 0; i < nkeys; i++) {
    mph_get_index(mph, vector[i]);
  }

  /* And of course don't forget to clean up. */
  mph_destroy(mph);

  return 0;
}
```

## Contributing

If you want to contribute...

1. Fork the repo
1. Create a branch
1. Issue a pull request
