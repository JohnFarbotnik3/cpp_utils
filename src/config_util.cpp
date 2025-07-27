
#ifndef F_config_util
#define F_config_util

#include <string>
#include <map>
#include "./string_util.cpp"

namespace utils::config_util {
	using std::string;
	using std::string_view;

	std::map<string, string> parse(const string data) {
		std::map<string, string> pairs;
		int pos = 0;
		while(pos < data.length()) {
			int end = data.find("\n", pos);
			if(end == string::npos) end = data.length();
			string_view line(data.data()+pos, data.data()+end);
			// get part of line between start and first instance of "#".
			int esc = line.find("#");
			if(esc == string::npos) esc = line.length();
			string_view part(line.data(), line.data() + esc);
			// extract key-value pair from line.
			int br = part.find("=");
			if(br != string::npos) {
				string key = string(string_util::trim(string_view(part.data()+0, part.data()+br), " \t"));
				string val = string(string_util::trim(string_view(part.data()+br+1, part.data()+part.length()), " \t"));
				pairs[key] = val;
			}
			// advance to next line.
			pos = end+1;
		}
		return pairs;
	}
};

#endif
