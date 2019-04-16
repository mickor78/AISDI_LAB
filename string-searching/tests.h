#include <cassert>
#include <string>

std::vector<int> find_N (const std::string& str, const std::string& text);

void boundary_test() {
	std::string pattern = "ABC";
	std::string text = "ABCABC";
	std::vector<int> result;


	// check for empty strings
	pattern = "";
	text = "ABCABC";
	assert(find_N(pattern, text).size() == 0);
	pattern = "ABCABC";
	text = "";
	assert(find_N(pattern, text).size() == 0);
	pattern = "";
	text = "";
	assert(find_N(pattern, text).size() == 0);
}
