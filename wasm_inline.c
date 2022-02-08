// from llvm/test/CodeGen/WebAssembly/inline-asm-roundtrip.ll 
int main(int argc, const char *argv[]) {
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
