#include <immintrin.h>

namespace utils::simd {
	/*
		multiply arrays of floats: C = A x B

		DATA FORMAT:
		alignas(16) float A[LEN]
		alignas(16) float B[LEN]
		alignas(16) float C[LEN]
	*/
	void multiply_16_aligned_4_float(const float* A, const float* B, float* C, const int LEN) {
		const int WID = 128 / 32;
		const int LIM = LEN - LEN % WID;
		int x = 0;
		for(;x<LIM;x+=WID) {
			__m128 a = _mm_load_ps(A+x);
			__m128 b = _mm_load_ps(B+x);
			__m128 c = _mm_mul_ps(a, b);
			_mm_store_ps(C+x, c);
		}
		for(;x<LEN;x++) C[x] = A[x] * B[x];
	}
}
