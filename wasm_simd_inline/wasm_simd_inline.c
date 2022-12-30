//// This version works, but is a combination of in-line and intrinsics. 
// #include <wasm_simd128.h>
// 
// int total_sum(int* in_a, int* in_b) {
//   v128_t prod;
//   
//   asm("local.get %1\n"    // Get the first pointer onto the stack
//       "v128.load 0\n"     // Use the pointer to load a v128 onto the stack. The '0' is the offset from the loaded address
//       "local.get %2\n"    // Get the second pointer onto the stack
//       "v128.load 0\n"     // Use the pointer to load a v128 onto the stack
//       "i32x4.mul\n"       // Two v128s should be on the stack, ready to be multiplied. Product v128 is on the stack
//       "local.set %0"
//       : "=r" (prod)
//       : "r" (in_a),
//         "r" (in_b));
//   
//   int out[4];
//   wasm_v128_store(out, prod);
// 
//   int total = out[0] + out[1] + out[2] + out[3];
// 
//   return total;
// }
// 
// 

int total_sum(int* in_a, int* in_b) {
  int total;
  
  // STACK: [0, 1, ..., n]
  // NOTE: for some reason, we can't use local.get or local.set on v128 types, so 
  //       we resort to doing v128 loads and stores. It would be much more efficient
  //       if we could avoid the v128.loads. 
  // 
  //       Looking at the .wat output for an -O3 optimized intrinsics output, it seems
  //       like we'd need to create a local v128 variable in order to be able to do the
  //       local.get/.set but I'm not sure how to do that with in-line assembly atm. 
  asm("i32.const 0\n"             // The address we will store our multiplied v128  STACK: [addr0]
      "local.get %1\n"            // Get the first pointer onto the stack           STACK: [addr0, in_a]
      "v128.load 0\n"             // Use the pointer to load a v128 onto the stack. 
                                  // The '0' is the offset from the loaded address. STACK: [addr0, v128_a]
      "local.get %2\n"            // Get the second pointer onto the stack          STACK: [addr0, v128_a, in_b]
      "v128.load 0\n"             // Use the pointer to load a v128 onto the stack  STACK: [addr0, v128_a, v128_b]
      "i32x4.mul\n"               // Two v128s should be on the stack, ready to be 
                                  // multiplied. Product v128 is on the stack       STACK: [addr0, v128_prod]
      "v128.store 0\n"            // Store the v128 at i32.const 0                  STACK: []
      "i32.const 0\n"             // Get the address on the stack                   STACK: [addr0]
      "v128.load 0\n"             // Load the v128                                  STACK: [v128_prod]
      "i32x4.extract_lane 0\n"    // extract lane 0 to the stack                    STACK: [prod0]
      "i32.const 0\n"             // Address                                        STACK: [prod0, addr0]
      "v128.load 0\n"             //                                                STACK: [prod0, v128_prod]
      "i32x4.extract_lane 1\n"    // extract lane 1 to the stack                    STACK: [prod0, prod1]
      "i32.add\n"                 // Add the first two lanes                        STACK: [p0+p1]
      "i32.const 0\n"             // Address                                        STACK: [p0+p1, addr0]
      "v128.load 0\n"             //                                                STACK: [p0+p1, v128_prod]
      "i32x4.extract_lane 2\n"    // extract lane 2 to the stack                    STACK: [p0+p1, prod2]
      "i32.add\n"                 //                                                STACK: [p0+p1+p2]
      "i32.const 0\n"             //                                                STACK: [p0+p1+p2, addr0]
      "v128.load 0\n"             //                                                STACK: [p0+p1+p2, v128_prod]
      "i32x4.extract_lane 3\n"    //                                                STACK: [p0+p1+p2, prod3]
      "i32.add\n"                 //                                                STACK: [p0+p1+p2+p3]
      "local.set %0"              // Set the output to `total`                      STACK: []
      : "=r" (total)
      : "r" (in_a),
        "r" (in_b));
    
    return total;
}