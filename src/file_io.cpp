
#ifndef F_file_io
#define F_file_io

#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

namespace utils::file_io {
	using std::string;
	using Path = std::filesystem::path;
	namespace fs = std::filesystem;

	bool can_read_file(const Path target) {
		return fs::exists(target) && fs::is_regular_file(target);
	}
	bool can_write_file(const Path target) {
		return !fs::exists(target) || fs::is_regular_file(target);
	}
	bool can_delete_file(const Path target) {
		return fs::exists(target) && fs::is_regular_file(target);
	}

	void make_dir(const Path target, int& status) {
		std::error_code ec;
		fs::create_directories(target, ec);
		if(ec) {
			fprintf(stderr, "failed to make directory: %s (error: %s)\n", target.c_str(), ec.message().c_str());
			status = -1;
		} else {
			status = 0;
		}
	}

	string read_file(const Path target, int& status) {
		std::ifstream file(target, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			fprintf(stderr, "failed to open file for reading: %s\n", target.c_str());
			fprintf(stderr, "errno: %s\n", strerror(errno));
			status = -1;
			return "";
		} else {
			const size_t filesize = file.tellg();
			string buffer(filesize, '\0');
			file.seekg(0);
			file.read(buffer.data(), filesize);
			status = 0;
			return buffer;
		}
	}

	void write_file(const Path target, int& status, const void* data, const size_t size) {
		make_dir(target.parent_path(), status);
		if(status != 0) return;

		std::ofstream file(target, std::ios::binary);
		if (!file.is_open()) {
			fprintf(stderr, "failed to open file for writing: %s\n", target.c_str());
			fprintf(stderr, "errno: %s\n", strerror(errno));
			status = -1;
		} else {
			file.write((const char*)data, size);
			status = 0;
			errno = 0;
		}
	}

	void delete_file(const Path target, int& status) {
		std::error_code ec;
		bool success = fs::remove(target, ec);
		if(!success) {
			fprintf(stderr, "failed to delete file: %s (error: %s)\n", target.c_str(), ec.message().c_str());
			fprintf(stderr, "errno: %s\n", strerror(errno));
			status = -1;
		} else {
			status = 0;
		}
	}

	bool is_target_file_within_directory(Path dir, Path file, bool print_warning) {
		std::error_code ec;
		Path abs_p = fs::canonical(dir, ec);
		Path abs_t = fs::canonical(file.parent_path(), ec);
		bool is_safe = false;
		if(ec) {
			fprintf(stderr, "ERROR [is_target_file_within_directory]: %s\n", ec.message().c_str());
			errno = 0;// TODO: print error string as well before clearing.
		} else {
			is_safe = abs_t.string().append("/").contains(abs_p.string());
		}
		if(!is_safe && print_warning) {
			printf("SECURITY WARNING: target file outside of prefix directory:\n");
			printf("\ttarget: %s\n", file.c_str());
			printf("\tabs_pdir: %s\n", abs_p.c_str());
			printf("\tabs_file: %s\n", abs_t.c_str());
		}
		return is_safe;
	}

	string remove_trailing_slashes(string path) {
		while(path.length() > 1 && path.ends_with('/')) path.pop_back();
		return path;
	}
}

#endif
