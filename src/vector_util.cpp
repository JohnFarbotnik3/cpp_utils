
#include <cassert>
#include <vector>

namespace utils::vector_util {
	using std::vector;

	template<class T>
	void vec_fill(vector<T>& vec, const T value) {
		// TODO - assertions.
		const auto length = vec.size();
		for(int x=0;x<length;x++) vec[x] = value;
	}

	template<class T>
	void vec_copy(vector<T>& dst, const vector<T>& src, const int beg, const int end) {
		// TODO - assertions.
		memcpy(dst.data() + beg, src.data() + beg, (end - beg) * sizeof(T));
	}

	template<class T>
	void vec_copy(vector<T>& dst, const vector<T>& src) {
		// TODO - more assertions.
		assert(dst.size() >= src.size());
		memcpy(dst.data(), src.data(), src.size() * sizeof(T));
	}

	template<class T>
	void vec_mult(vector<T>& vec, const T value) {
		// TODO - assertions.
		const auto length = vec.size();
		for(int x=0;x<length;x++) vec[x] *= value;
	}

};
