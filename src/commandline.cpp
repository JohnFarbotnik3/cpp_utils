
#include <charconv>
#include <map>
#include <string>
#include <vector>

namespace utils::commandline {
	using std::map;
	using std::vector;
	using std::string;

	struct cmd_arguments {
		map<string, string> named_arguments;
		vector<string> positional_arguments;

		cmd_arguments(const int argc, const char** argv) {
			int x=0;
			while(x<argc) {
				string arg(argv[x++]);
				if(arg.length() >= 1 && arg[0] == '-' && x < argc) {
					string val(argv[x++]);
					named_arguments[arg] = val;
				} else {
					positional_arguments.push_back(arg);
				}
			}
		}

		void print() const {
			printf("=====\n");
			printf("named arguments:\n");
			for(const auto& [key,val] : this->named_arguments) printf("%s=%s\n", key.c_str(), val.c_str());
			printf("-----\n");
			printf("positional arguments\n");
			for(const std::string& arg : this->positional_arguments) printf("%s\n", arg.c_str());
			printf("-----\n");
		}

		template<class T>
		T get_named_value(string name, T default_value) const {
			if(named_arguments.contains(name)) {
				T value;
				string str = named_arguments.at(name);
				std::from_chars_result status = std::from_chars(str.data(), str.data() + str.size(), value);
				if(status.ec == std::errc::invalid_argument) {
					printf("[get_named_value()] invalid_argument: %s\n", str.c_str());
					return default_value;
				}
				return value;
			} else {
				return default_value;
			}
		}
	};

}
