
#ifndef F_vector_util
#define F_vector_util

#include <cassert>
#include <cstring>
#include <functional>
#include <thread>
#include <vector>
#include <numeric>

namespace utils::vector_util {
	using std::vector;
	//namespace stdx = std::experimental;

	template<class T> void vec_fill(vector<T>& vec, const T value) {
		// TODO - assertions.
		const auto length = vec.size();
		for(int x=0;x<length;x++) vec[x] = value;
	}

	template<class T> void vec_copy(vector<T>& dst, const vector<T>& src, const int beg, const int end) {
		// TODO - assertions.
		memcpy(dst.data() + beg, src.data() + beg, (end - beg) * sizeof(T));
	}

	template<class T> void vec_copy(vector<T>& dst, const vector<T>& src) {
		// TODO - more assertions.
		assert(dst.size() >= src.size());
		memcpy(dst.data(), src.data(), src.size() * sizeof(T));
	}


	template<class T> void vec_mult_fn(vector<T>& vec, const T value, const int beg, const int end) {
		// TODO - assertions.
		for(int x=beg;x<end;x++) vec[x] *= value;
	}
	template<class T> void vec_mult_mt(vector<T>& vec, const T value, const int beg, const int end, const int n_threads) {
		vector<std::thread> threads;
		const int len = end - beg;
		for(int x=0;x<n_threads;x++) {
			const int x0 = ((x+0) * len) / n_threads + beg;
			const int x1 = ((x+1) * len) / n_threads + beg;
			threads.push_back(std::thread(vec_mult_fn<T>, std::ref(vec), value, x0, x1));
		}
		for(int x=0;x<n_threads;x++) threads[x].join();
	}


	template<class T> void vec_sum_abs_fn(const vector<float>& vec, const int beg, const int end, float& result) {
		float sums[4] {0,0,0,0};
		int x = beg;
		for(;x+4<=end;x+=4) {
			sums[0] += std::abs(vec[x+0]);
			sums[1] += std::abs(vec[x+1]);
			sums[2] += std::abs(vec[x+2]);
			sums[3] += std::abs(vec[x+3]);
		}
		for(;x<end;x++) sums[0] += std::abs(vec[x]);
		result = sums[0] + sums[1] + sums[2] + sums[3];
	}
	template<class T> T    vec_sum_abs_mt(const vector<T>& vec, const int beg, const int end, const int n_threads) {
		vector<std::thread> threads;
		const int len = end - beg;
		float sums[n_threads];
		for(int x=0;x<n_threads;x++) {
			const int x0 = ((x+0) * len) / n_threads + beg;
			const int x1 = ((x+1) * len) / n_threads + beg;
			threads.push_back(std::thread(vec_sum_abs_fn<T>, std::ref(vec), x0, x1, std::ref(sums[x])));
		}
		for(int x=0;x<n_threads;x++) threads[x].join();
		float sum = 0;
		for(int x=0;x<n_threads;x++) sum += sums[x];
		return sum;
	}


	template<class T> T vec_reduce(const vector<T>& vec, const int beg, const int end) {
		// TODO - assertions.
		return std::reduce(vec.data() + beg, vec.data() + end);
	}

};

#endif
