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

#include <wasm_simd128.h>

int total_sum(int* in_a, int* in_b) {
  int total;
  v128_t local; 
  
  // STACK: [0, 1, ..., n]
  asm("local.get %2\n"            // Get the first pointer onto the stack           STACK: [in_a]
      "v128.load 0\n"             // Use the pointer to load a v128 onto the stack. 
                                  // The '0' is the offset from the loaded address. STACK: [v128_a]
      "local.get %3\n"            // Get the second pointer onto the stack          STACK: [v128_a, in_b]
      "v128.load 0\n"             // Use the pointer to load a v128 onto the stack  STACK: [v128_a, v128_b]
      "i32x4.mul\n"               // Two v128s should be on the stack, ready to be 
                                  // multiplied. Product v128 is on the stack       STACK: [v128_prod]
      "local.tee %1\n"            // Store the v128 at i32.const 0                  STACK: [v128_prod]
      "i32x4.extract_lane 0\n"    // extract lane 0 to the stack                    STACK: [prod0]
      "local.get %1\n"            // Address                                        STACK: [prod0, v128_prod]
      "i32x4.extract_lane 1\n"    // extract lane 1 to the stack                    STACK: [prod0, prod1]
      "i32.add\n"                 // Add the first two lanes                        STACK: [p0+p1]
      "local.get %1\n"            // Address                                        STACK: [p0+p1, v128_prod]
      "i32x4.extract_lane 2\n"    // extract lane 2 to the stack                    STACK: [p0+p1, prod2]
      "i32.add\n"                 //                                                STACK: [p0+p1+p2]
      "local.get %1\n\n"          //                                                STACK: [p0+p1+p2, v128_prod]
      "i32x4.extract_lane 3\n"    //                                                STACK: [p0+p1+p2, prod3]
      "i32.add\n"                 //                                                STACK: [p0+p1+p2+p3]
      "local.set %0"              // Set the output to `total`                      STACK: []
      : "=r" (total), "=r" (local)
      : "r" (in_a),
        "r" (in_b));
    
    return total;
}