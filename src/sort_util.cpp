
#include <cstdint>
#include <cstring>
#include <vector>

namespace utils::sort_util {
	using std::vector;

	// https://en.wikipedia.org/wiki/Single-precision_floating-point_format
	// WARNING: this function does not check endianness - which will affect conversion between floats and uints.
	vector<float> radix_sort_f(const vector<float>& src) {
		const int LENGTH = src.size();
		vector<uint32_t> data(LENGTH);
		vector<uint32_t> temp(LENGTH);
		memcpy(data.data(), src.data(), LENGTH*sizeof(uint32_t));
		// sort by fraction.
		for(int RSH=0;RSH<24;RSH+=8) {
			const uint32_t BINS = 256;
			const uint32_t MASK = 0xff;
			const uint32_t FRACTION_MASK = 0x7fffff;
			int counts[BINS];
			for(int x=0;x<BINS;x++) counts[x] = 0;
			for(int x=0;x<LENGTH;x++) counts[(((data[x]&FRACTION_MASK)>>RSH)&MASK)]++;
			int s=0;
			for(int x=0;x<BINS;x++) { int c=counts[x]; counts[x]=s; s+=c; }
			for(int x=0;x<LENGTH;x++) temp[counts[(((data[x]&FRACTION_MASK)>>RSH)&MASK)]++] = data[x];
			memcpy(data.data(), temp.data(), LENGTH*sizeof(uint32_t));
		}
		// sort by exponent.
		{
			const int RSH = 23;
			const uint32_t BINS = 256;
			const uint32_t MASK = 0xff;
			int counts[BINS];
			for(int x=0;x<BINS;x++) counts[x] = 0;
			for(int x=0;x<LENGTH;x++) counts[((data[x]>>RSH)&MASK)]++;
			int s=0;
			for(int x=0;x<BINS;x++) { int c=counts[x]; counts[x]=s; s+=c; }
			for(int x=0;x<LENGTH;x++) temp[counts[((data[x]>>RSH)&MASK)]++] = data[x];
			memcpy(data.data(), temp.data(), LENGTH*sizeof(uint32_t));
		}
		// sort by sign.
		{
			const int RSH = 31;
			const uint32_t BINS = 2;
			const uint32_t MASK = 0x1;
			int counts[BINS];
			for(int x=0;x<BINS;x++) counts[x] = 0;
			for(int x=0;x<LENGTH;x++) counts[((data[x]>>RSH)&MASK)]++;
			counts[0] = counts[1];
			counts[1] = 0;
			for(int x=0;x<LENGTH;x++) temp[counts[((data[x]>>RSH)&MASK)]++] = data[x];
			// copy negative numbers in reverse.
			const int n_negatives = counts[1];
			for(int x=0;x<n_negatives;x++) data[x] = temp[n_negatives-1-x];
			// copy positive numbers normally.
			memcpy(data.data()+n_negatives, temp.data()+n_negatives, (LENGTH-n_negatives)*sizeof(uint32_t));
		}
		vector<float> dst(LENGTH);
		memcpy(dst.data(), data.data(), LENGTH*sizeof(uint32_t));
		return dst;
	}
};
