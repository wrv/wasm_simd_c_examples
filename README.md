# Using WASM+SIMD in C

This is a collection of examples on how to use WASM SIMD in C. It requires the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk) as well 
as the SIMD enhanced wasm2c from [WABT](https://github.com/PLSysSec/wabt/tree/simd). The SIMD enhanced wasm2c relies on the 
[SIMD Everywhere (SIMDe)](https://github.com/simd-everywhere/simde) library for translating WASMSIMD to the target architecture.

## Examples

We use the inner product function as an example: 

```math
\sum_{i=1}^{4} \textbf{x}_i \cdot \textbf{y}_i = x_1y_1 + x_2y_2 + x_3y_3 + x_4y_4

```

There are six examples for incorporating WASM+SIMD with C code:
1. Inline WASM [`wasm_inline/`](wasm_inline/wasm_inline.c): This uses non-SIMD inline WASM, and is included as another example.
2. Inline WASMSIMD [`wasm_simd_inline/`](wasm_simd_inline/wasm_simd_inline.c): Uses SIMD inline WASM without `wasm_simd128.h`
3. Inline WASMSIMD with locals [`wasm_simd_inline2/`](wasm_simd_inline2/wasm_simd_inline.c): Uses SIMD inline WASM but creates a local v128 variable.
4. Intrinsics WASMSIMD [`wasm_simd_intrinsics/`](wasm_simd_intrinsics/wasm_simd_intrinsics.c): Using the built-in `wasm_simd128.h` for intrinsics
5. External WASMSIMD [`wasm_simd_external/`](wasm_simd_external/wasm_simd_external.c): Uses a separate .wat file that is linked to and externally called from C. 
6. SIMD Everywhere WASMSIMD [`wasm_simde/](wasm_simde/wasm_simde.c): Use SIMDe to translate AVX2 intrinsics to corresponding WASMSIMD intrinsics. Because 
wasm2c also uses SIMDe, the library is used twice.  

The examples are in the `<name>.c` file in each folder. The `<name>.main.c` is to call into these functions after 
they've been passed through `wasm2c`. 

## Building

Update the paths in `Makefile` to the location of WASI and WABT. You can then call either `make` or for a specific example:
1. `make wasm_inline`
2. `make simd_inline`
3. `make simd_inline2`
4. `make simd_intrinsics`
5. `make simd_external`
6. `make simd_simde`

### Process 

The `Makefile` first compiles the `.c` file to an intermediate WASM representation with `clang`. Then, it links the `.wasm` with `wasm-ld` 
to make it externally callable. For sanity checking purposes, we also have calls to `wasm2wat` to inspect what was compiled. 

Because we're using WASM to sandbox libraries as a part of [RLBox](https://github.com/PLSysSec/rlbox), we convert the `.wasm` back to C 
using `wasm2c`, then compile the `.main.c` file with the `wasm2c` output. 

## Notes

After creating these examples, likely the easiest way to work with WASMSIMD in C is with intrinsics, with the second easiest way 
being the external `.wat` file. Using inline WASM SIMD may be okay, but observations so far have shown that the compiler does 
a good job of optimizing the WASM. 

## Resources

- From `llvm/lib/Target/WebAssembly/README.txt`:
```
The object format emitted by the WebAssembly backed is documented in:
  * https://github.com/WebAssembly/tool-conventions/blob/main/Linking.md

The C ABI is described in:
  * https://github.com/WebAssembly/tool-conventions/blob/main/BasicCABI.md

For more information on WebAssembly itself, see the home page:
  * https://webassembly.github.io/
```
- The single LLVM test testing inline WASM: [inline-asm-roundtrip.ll](https://github.com/llvm/llvm-project/blob/main/llvm/test/CodeGen/WebAssembly/inline-asm-roundtrip.ll). 
- [V8 blog post](https://v8.dev/features/simd) on using WASMSIMD intrinsics
