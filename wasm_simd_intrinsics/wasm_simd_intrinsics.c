#include <wasm_simd128.h>

int total_sum(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_mul(a, b);
  wasm_v128_store(out, prod);

  int total = out[0] + out[1] + out[2] + out[3];

  return total;
}