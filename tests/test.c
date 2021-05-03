#include "../src/ibst.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void empty_in_order(int n) {
  ibst_t *t = ibst_interval(1, n);

  for (int i = 1; i <= n; i++) {
    assert(! ibst_empty(t));
    assert(ibst_size(t) == n - i + 1);
    assert(ibst_pop_nth(&t, 0) == i);
  }
  assert(ibst_empty(t));

  ibst_free(t);
}

static void empty_backward(int n) {
  ibst_t *t = ibst_interval(1, n);

  for (int i = n - 1; i >= 0; i--) {
    assert(! ibst_empty(t));
    assert(ibst_size(t) == i + 1);
    assert(ibst_pop_nth(&t, i) == i + 1);
  }
  assert(ibst_empty(t));

  ibst_free(t);
}

static void empty_random(int n) {
  ibst_t *t = ibst_interval(0, n - 1);
  int *check = calloc(n, sizeof(int));

  for (int i = 0; i < n; i++) check[i] = 0;

  for (int i = 0; i < n; i++) {
    assert(! ibst_empty(t));
    assert(ibst_size(t) == n - i);
    int r = ibst_pop_nth(&t, rand() % (n - i));
    assert(0 <= r && r < n);
    assert(!check[r]);
    check[r] = 1;
  }

  assert(ibst_empty(t));
  for (int i = 0; i < n; i++) assert(check[i]);

  ibst_free(t);
  free(check);
}

int main() {
  unsigned int seed = 0xcafeb0b0u;
  srand(seed);

  for (int n = 1; n < 20; n++) {
    empty_in_order(n);
    empty_backward(n);
    empty_random(n);
  }

  return 0;
}
