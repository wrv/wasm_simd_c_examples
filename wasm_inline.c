/*
// from llvm/test/CodeGen/WebAssembly/inline-asm-roundtrip.ll 
int total_sum(int* in_a, int* in_b) {
  int src = 1;
  int dst;
  asm ("i32.const\t2\n"
       "\tlocal.get\t%1\n"
       "\ti32.add\n"
       "\tlocal.set\t%0"
       : "=r" (dst)
       : "r" (src));
  return dst != 3;
}
*/

int total_sum(int* in_a, int* in_b) {
  int total;
  
  // STACK: [0, 1, ..., n]

  asm("local.get %1\n"    // in_a           STACK: [addr_a]
      "i32.load 0\n"      // Load in_a[0]   STACK: [in_a[0]]   
      "local.get %2\n"    // in_b           STACK: [in_a[0], addr_b]
      "i32.load 0\n"      // Load in_b[0]   STACK: [in_a[0], in_b[0]]
      "i32.mul\n"         //                STACK: [prod0]
      "local.get %1\n"    //                STACK: [prod0, addr_a]
      "i32.load 4\n"      //                STACK: [prod0, in_a[1]]
      "local.get %2\n"    //                STACK: [prod0, in_a[1], addr_b]
      "i32.load 4\n"      //                STACK: [prod0, in_a[1], in_b[1]]
      "i32.mul\n"         //                STACK: [prod0, prod1]
      "local.get %1\n"    //                STACK: [prod0, prod1, addr_a]
      "i32.load 8\n"      //                STACK: [prod0, prod1, in_a[2]]
      "local.get %2\n"    //                STACK: [prod0, prod1, in_a[2], addr_b]
      "i32.load 8\n"      //                STACK: [prod0, prod1, in_a[2], in_b[2]]
      "i32.mul\n"         //                STACK: [prod0, prod1, prod2]
      "local.get %1\n"    //                STACK: [prod0, prod1, prod2, addr_a]
      "i32.load 12\n"     //                STACK: [prod0, prod1, prod2, in_a[3]]
      "local.get %2\n"    //                STACK: [prod0, prod1, prod2, in_a[3], addr_b]
      "i32.load 12\n"     //                STACK: [prod0, prod1, prod2, in_a[3], in_b[3]]
      "i32.mul\n"         //                STACK: [prod0, prod1, prod2, prod3]
      "i32.add\n"         //                STACK: [prod0, prod1, p2+p3]
      "i32.add\n"         //                STACK: [prod0, p1+p2+p3]
      "i32.add\n"         //                STACK: [p0+p1+p2+p3]
      "local.set %0"      //                STACK: []
      : "=r" (total)
      : "r" (in_a),
        "r" (in_b));
    
    return total;
}