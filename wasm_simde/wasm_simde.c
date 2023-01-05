// To use SIMD Everywhere, we replace the x86 intrinsics header with the SIMD Everywhere header
//#include <xmmintrin.h>
#include <simde/x86/avx2.h> 


int total_sum(int* in_a, int* in_b) {
  int out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i prod = _mm_mullo_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, prod);

  int total = out[0] + out[1] + out[2] + out[3];

  return total;
}
