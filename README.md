# Using WASM+SIMD in C

This repo is a collection of basic examples on how to use SIMD WASM in C. 

Files:
- wasm_inline.c: Using inline WASM
- wasm_simd_inline.c: Using inline SIMD WASM
- wasm_simd_intrinsics.c: Using the built-in wasm_simd128.h 

In `Makefile`, change the location of `clang_bin` to your `clang` with wasm32 support if not the default.

`.wat` files are generated with [`wasm2wat`](https://github.com/WebAssembly/wabt). 

## Resources

From `llvm/lib/Target/WebAssembly/README.txt`:
```
The object format emitted by the WebAssembly backed is documented in:
  * https://github.com/WebAssembly/tool-conventions/blob/main/Linking.md

The C ABI is described in:
  * https://github.com/WebAssembly/tool-conventions/blob/main/BasicCABI.md

For more information on WebAssembly itself, see the home page:
  * https://webassembly.github.io/
```

