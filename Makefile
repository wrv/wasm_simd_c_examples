wabt_bin_path := ../wabt_plsyssec/build
wasm2c_folder := ../wabt_plsyssec/wasm2c/
simde_folder := ../wabt_plsyssec/third_party/simde/
wasi_sdk_path := ../wasi-sdk-14.0

define generic_build
	$(wasi_sdk_path)/bin/clang $(1).c -o $(1).int.wasm --sysroot $(wasi_sdk_path)/share/wasi-sysroot -msimd128 -c -O3
	$(wasi_sdk_path)/bin/wasm-ld -m wasm32 --export-all --no-entry --growable-table --stack-first -z stack-size=1048576 $(1).int.wasm -o $(1).wasm
	$(wabt_bin_path)/wasm2wat $(1).wasm -o $(1).wat
	$(wabt_bin_path)/wasm2wat $(1).int.wasm -o $(1).int.wat
	$(wabt_bin_path)/wasm2c $(1).wasm -o $(1).wasm2c.c &> $(1).wasm2c.verbose_log.txt
	clang -DWASM_RT_ENABLE_SIMD -I$(wasm2c_folder) -I$(simde_folder) \
					-lm -o $(1).wasm2c.out  \
					-mavx  					\
					$(1).main.c          	\
					$(1).wasm2c.c        	\
					$(wasm2c_folder)/wasm-rt-impl.c
	./$(1).wasm2c.out 1337
endef


all: simd_intrinsics wasm_inline simd_inline simd_external

simd: simd_intrinsics simd_inline simd_external

simd_intrinsics: wasm_simd_intrinsics/wasm_simd_intrinsics.c
	$(call generic_build,wasm_simd_intrinsics/wasm_simd_intrinsics)

wasm_inline: wasm_inline/wasm_inline.c
	$(call generic_build,wasm_inline/wasm_inline)

simd_inline: wasm_simd_inline/wasm_simd_inline.c
	$(call generic_build,wasm_simd_inline/wasm_simd_inline)

simd_inline2: wasm_simd_inline2/wasm_simd_inline.c
	$(call generic_build,wasm_simd_inline2/wasm_simd_inline)

simd_external: wasm_simd_external/wasm_simd_external.c wasm_simd_external/wasm_simd_external.wat
	$(wasi_sdk_path)/bin/clang wasm_simd_external/wasm_simd_external.c -o wasm_simd_external/wasm_simd_external.int.wasm --sysroot $(wasi_sdk_path)/share/wasi-sysroot -msimd128 -c -O3
	$(wabt_bin_path)/wat2wasm wasm_simd_external/wasm_simd_external.wat -o wasm_simd_external/wasm_simd_external.fun.wasm -r
	$(wasi_sdk_path)/bin/wasm-ld -m wasm32 \
				--export-all \
				--no-entry \
				--growable-table \
				--stack-first \
				-z stack-size=1048576 \
				wasm_simd_external/wasm_simd_external.fun.wasm \
				wasm_simd_external/wasm_simd_external.int.wasm \
				-o wasm_simd_external/wasm_simd_external.wasm
	$(wabt_bin_path)/wasm2c wasm_simd_external/wasm_simd_external.wasm \
				-o wasm_simd_external/wasm_simd_external.wasm2c.c &> wasm_simd_external/wasm_simd_external.wasm2c.verbose_log.txt
	clang -DWASM_RT_ENABLE_SIMD -I$(wasm2c_folder) -I$(simde_folder) \
					-lm -o wasm_simd_external/wasm_simd_external.wasm2c.out \
					-mavx \
					wasm_simd_external/wasm_simd_external.main.c \
					wasm_simd_external/wasm_simd_external.wasm2c.c \
					$(wasm2c_folder)/wasm-rt-impl.c
	./wasm_simd_external/wasm_simd_external.wasm2c.out 1337


clean:
	rm *.wasm *.wat *.err *.wasm2c.c *.wasm2c.h *.ll *.out 