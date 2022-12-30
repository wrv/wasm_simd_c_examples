#include <stdio.h>
#include <stdlib.h>

#include "wasm_simd_inline.wasm2c.h"


int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);

    return 1;
  }

  s32 x = atoi(argv[1]);

  s32 in_a[4] = {x, x, x, x}; 
  s32 in_b[4] = {2*x, 2*x, 2*x, 2*x}; 
  int size = 4;

  printf("\t in_a = %d %d %d %d\n", in_a[0], in_a[1], in_a[2], in_a[3]);
  printf("\t in_b = %d %d %d %d\n", in_b[0], in_b[1], in_b[2], in_b[3]);

  /* Initialize the Wasm runtime. */
  wasm_rt_init();

  /* One time initializations of minimum wasi runtime supported by wasm2c */
  Z_wasm_simd_inline_init_module();
  
  /* Declare an instance of the `wasm_simd_inline` module. */
  Z_wasm_simd_inline_instance_t wasm_simd_inline_instance;

  /* Construct the module instance */
  /* NOTE: the rot13 example passes in host_instance, where we store our values*/
  Z_wasm_simd_inline_instantiate(&wasm_simd_inline_instance);

  /* Sandbox memory addresses */
  u32 sbx_a = 0;  // for some reason there are weird memory offsets in the wasm output?
  u32 sbx_b = 16;

  // load 4 32-bit numbers
  for (int i = 0; i < size; i++) {
    int loc_a = 4*i+sbx_a;
    int loc_b = 4*i+sbx_b;
    // each entry is of type uint8 so we need to pass in all bits
    wasm_simd_inline_instance.w2c_memory.data[loc_a]   = in_a[i] & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_a+1] = (in_a[i] >> 8) & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_a+2] = (in_a[i] >> 16) & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_a+3] = (in_a[i] >> 24) & 0xff; 

    wasm_simd_inline_instance.w2c_memory.data[loc_b]   = in_b[i] & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_b+1] = (in_b[i] >> 8) & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_b+2] = (in_b[i] >> 16) & 0xff; 
    wasm_simd_inline_instance.w2c_memory.data[loc_b+3] = (in_b[i] >> 24) & 0xff; 
  }
  
  printf("- Add then sum result\n");

  int total = Z_wasm_simd_inlineZ_total_sum(&wasm_simd_inline_instance, sbx_a, sbx_b);
  printf("Total: %d \n", total);

  /* Free the wasm_simd_inline module. */
  Z_wasm_simd_inline_free(&wasm_simd_inline_instance);

  /* Free the Wasm runtime state. */
  wasm_rt_free();

  return 0;
}