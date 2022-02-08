// NOTE: the below compiles but wasm2wat errors out due to type errors with v128.load/v128.store
void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i+=4) {
    asm("\tlocal.get\t%1\n"
        "\tlocal.set\t0\n"
        "\tv128.load\t0\n"
        "\tlocal.get\t%2\n"
        "\tlocal.set\t1\n"
        "\tv128.load\t1\n"
        "\tlocal.get\t0\n"
        "\tlocal.get\t1\n"
        "\ti32x4.mul\n"
        "\tv128.store\t%0\n"
        : "=r" (out[i])
        : "r" (&in_a[i]), 
          "r" (&in_b[i])); 
  }
}
