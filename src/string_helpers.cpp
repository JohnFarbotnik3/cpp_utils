#include <array>
#include <string>
#include <vector>

using string = std::string;

// TODO: check if these mutate original string, or if std::string is deep-copied.
// !!! WRITE TESTS !!!

// ============================================================
// case conversions
// ------------------------------------------------------------

// https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
/*
string to_lowercase(string str) {
	for(int x=0;x<str.length();x++) str[x] = std::tolower(x);
	return str;
}
string to_uppercase(string str) {
	for(int x=0;x<str.length();x++) str[x] = std::toupper(x);
	return str;
}
*/

string to_lowercase_ascii(string str) {
	for(int x=0;x<str.length();x++) {
		char c = str[x];
		str[x] = ('A' <= c && c <= 'Z') ? (c - 'A' + 'a') : c;
	}
	return str;
}
string to_uppercase_ascii(string str) {
	char diff = 'A' - 'a';
	for(int x=0;x<str.length();x++) {
		char c = str[x];
		str[x] = ('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c;
	}
	return str;
}

// ============================================================
// trim
// ------------------------------------------------------------

string trim(string str, string whitespace_chars=" \t") {
	int a = 0;
	while(a < str.length() && whitespace_chars.contains(str[a])) a++;
	int b = str.length();
	while(b > a && whitespace_chars.contains(str[b])) b--;
	return str.substr(a, b-a);
}

string trim_leading(string str, string whitespace_chars=" \t") {
	int a = 0;
	while(a < str.length() && whitespace_chars.contains(str[a])) a++;
	int b = str.length();
	return str.substr(a, b-a);
}

// ============================================================
// split
// ------------------------------------------------------------

std::vector<string> split(const string& str, const string& delim) {
	std::vector<string> list;
	int beg = 0;
	int end;
	while(beg < str.length()) {
		end = str.find(delim, beg);
		if(end == str.npos) {
			list.push_back(str.substr(beg));
			break;
		} else {
			list.push_back(str.substr(beg, end));
			beg = end + delim.length();
		}
	}
	return list;
}

std::array<string, 2> split_2(const string& str, const string& delim) {
	std::array<string, 2> list;
	int pos = str.find(delim);
	if(pos == str.npos) {
		list[0] = str;
		list[1] = "";
	} else {
		list[0] = str.substr(0, pos);
		list[1] = str.substr(pos + delim.length());
	}
	return list;
}







