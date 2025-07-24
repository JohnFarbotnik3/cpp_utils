
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
	std::uniform_int_distribution<T> rand_uniform_int(T min, T max) {
		return std::uniform_int_distribution<T>(min, max);
	}

	template<typename T>
	std::uniform_real_distribution<T> rand_uniform_real(T min, T max) {
		return std::uniform_real_distribution<T>(min, max);
	}

	template<typename T>
	std::normal_distribution<T> rand_normal(float mean, float stddev) {
		return std::normal_distribution<T>(mean, stddev);
	}

	std::vector<int> generate_shuffle_mapping(std::mt19937& gen32, const int length) {
		// generate pool of indices.
		std::vector<int> pool(length);
		for(int x=0;x<length;x++) pool[x] = x;
		// generate random order of indices.
		std::vector<int> order;
		for(int x=0;x<length;x++) {
			std::uniform_int_distribution<int> distr(0, pool.size()-1);
			const int ind = distr(gen32);
			order.push_back(pool[ind]);
			pool[ind] = pool.back();
			pool.pop_back();
		}
		return order;
	}
};

#endif
