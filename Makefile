clang_bin := ../wasi-sdk-14.0/bin/clang
ld_path := ../wasi-sdk-14.0/bin/wasm-ld
wasm2wat_bin := ../plsyssec_wabt/build/wasm2wat
wasm2c_bin := ../plsyssec_wabt/build/wasm2c
wasm2c_folder := ../plsyssec_wabt/wasm2c/
simde_folder := ../plsyssec_wabt/third_party/simde/
WASI_SDK_PATH=../wasi-sdk-14.0

define generic_build
	$(clang_bin) $(1).c -o $(1).int.wasm --sysroot $(WASI_SDK_PATH)/share/wasi-sysroot -msimd128 -c -O3
	$(ld_path) -m wasm32 --export-all --no-entry --growable-table --stack-first -z stack-size=1048576 $(1).int.wasm -o $(1).wasm
	$(wasm2wat_bin) $(1).wasm -o $(1).wat
	$(wasm2wat_bin) $(1).int.wasm -o $(1).int.wat
	$(wasm2c_bin) $(1).wasm -o $(1).wasm2c.c &> $(1).wasm2c.verbose_log.txt
	clang -DWASM_RT_ENABLE_SIMD -I$(wasm2c_folder) -I$(simde_folder) \
					-lm -o $(1).wasm2c.out  \
					-mavx  					\
                    $(1).main.c          	\
                    $(1).wasm2c.c        	\
                    $(wasm2c_folder)/wasm-rt-impl.c   
	./$(1).wasm2c.out 1337
endef


all: simd_intrinsics wasm_inline simd_inline

simd: simd_intrinsics simd_inline

simd_intrinsics: wasm_simd_intrinsics.c
	$(call generic_build,wasm_simd_intrinsics)

wasm_inline: wasm_inline.c
	$(call generic_build,wasm_inline)

simd_inline: wasm_simd_inline.c
	$(call generic_build,wasm_simd_inline)

clean:
	rm *.wasm *.wat *.err *.wasm2c.c *.wasm2c.h *.ll *.out 