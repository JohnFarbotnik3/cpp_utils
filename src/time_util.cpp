
#ifndef F_time_util
#define F_time_util

#include <cstdint>
#include <ctime>

namespace utils::time_util {
	struct timepoint_64_ns {
		int64_t value = 0;

		timepoint_64_ns() = default;
		timepoint_64_ns(int64_t value) { this->value = value; }

		static timepoint_64_ns now() {
			std::timespec ts;
			std::timespec_get(&ts, TIME_UTC);
			timepoint_64_ns tp;
			tp.value = (int64_t)(ts.tv_sec)*(int64_t)(1000000000) + (int64_t)(ts.tv_nsec);
			return tp;
		}

		int64_t value_ns() { return value; }
		int64_t value_us() { return value / 1000; }
		int64_t value_ms() { return value / 1000000; }

		timepoint_64_ns delta(timepoint_64_ns t0) { return timepoint_64_ns(value - t0.value); }
		int64_t delta_ns(timepoint_64_ns t0) { return value - t0.value; }
		int64_t delta_us(timepoint_64_ns t0) { return delta_ns(t0) / 1000; }
		int64_t delta_ms(timepoint_64_ns t0) { return delta_ns(t0) / 1000000; }
	};
};

#endif
