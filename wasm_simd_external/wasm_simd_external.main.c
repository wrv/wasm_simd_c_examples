#include <stdio.h>
#include <stdlib.h>

#include "wasm_simd_external.wasm2c.h"


int main(int argc, char** argv) {
  /*
  if (argc < 9) {
    printf("Usage: %s <a0> <a1> <a2> <a3> <b0> <b1> <b2> <b3>\n", argv[0]);

    return 1;
  }

  s32 in_a[4] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])}; 
  s32 in_b[4] = {atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8])}; 

  */

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
  Z_wasm_simd_external_init_module();
  
  /* Declare an instance of the `wasm_simd_external` module. */
  Z_wasm_simd_external_instance_t wasm_simd_external_instance;

  /* Construct the module instance */
  Z_wasm_simd_external_instantiate(&wasm_simd_external_instance);

  /* Sandbox memory addresses */
  u32 sbx_a = 0;
  u32 sbx_b = 16;

  // load 4 32-bit numbers
  for (int i = 0; i < size; i++) {
    int loc_a = 4*i+sbx_a;
    int loc_b = 4*i+sbx_b;
    // each entry is of type uint8 so we need to pass in all bits
    wasm_simd_external_instance.w2c_memory.data[loc_a]   = in_a[i] & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_a+1] = (in_a[i] >> 8) & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_a+2] = (in_a[i] >> 16) & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_a+3] = (in_a[i] >> 24) & 0xff; 

    wasm_simd_external_instance.w2c_memory.data[loc_b]   = in_b[i] & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_b+1] = (in_b[i] >> 8) & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_b+2] = (in_b[i] >> 16) & 0xff; 
    wasm_simd_external_instance.w2c_memory.data[loc_b+3] = (in_b[i] >> 24) & 0xff; 
  }

  printf("- SIMD Add then sum result\n");

  int total = Z_wasm_simd_externalZ_total_sum_wrapper(&wasm_simd_external_instance, sbx_a, sbx_b);
  printf("Total: %d \n", total);

  /* Free the wasm_simd_external module. */
  Z_wasm_simd_external_free(&wasm_simd_external_instance);

  /* Free the Wasm runtime state. */
  wasm_rt_free();

  return 0;
}