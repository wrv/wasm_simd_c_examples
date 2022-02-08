clang_bin := $(shell which clang)

all: simd_intrinsics wasm_inline wasm_simd_inline

simd_intrinsics: wasm_simd_intrinsics.c
	$(clang_bin) wasm_simd_intrinsics.c -o wasm_simd_intrinsics.wasm --target=wasm32-unknown-unknown-wasm -c -msimd128

wasm_inline: wasm_inline.c
	$(clang_bin) wasm_inline.c -o wasm_inline.wasm --target=wasm32-unknown-unknown-wasm -c

wasm_simd_inline: wasm_simd_inline.c
	$(clang_bin) wasm_simd_inline.c -o wasm_simd_inline.wasm --target=wasm32-unknown-unknown-wasm -c -msimd128