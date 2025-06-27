
#ifndef F_random
#define F_random

#include <random>

namespace utils::random {
	// get psuedo-random generator (32-bit).
	std::mt19937 get_generator_32(int seed) {
		return std::mt19937(seed);
	}

	// get distribution function.
	// usage: distribution(generator)
	template<typename T>
	std::uniform_int_distribution<T> rand_uniform(T min, T max) {
		return std::uniform_int_distribution<T>(min, max);
	}

	template<typename T>
	std::uniform_real_distribution<T> rand_uniform(T min, T max) {
		return std::uniform_real_distribution<T>(min, max);
	}

	template<typename T>
	std::normal_distribution<T> rand_normal(float mean, float stddev) {
		return std::normal_distribution<T>(mean, stddev);
	}
};

#endif
