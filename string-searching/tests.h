#include <cassert>
#include <string>
#include <vector>

std::vector<int> find_N (const std::string& pattern, const std::string& text);

void boundary_test() {

	std::string pattern;
	std::string text;


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

	// check if works properly
	pattern = "ABCABC";
	text = "ABCABC";
	assert(find_N(pattern, text).size() == 1);
	assert(find_N(pattern, text)[0] == 0);
	pattern = "ABCABC";
	text = "ABC";
	assert(find_N(pattern, text).size() == 0);
	pattern = "ABC";
	text = "ABCABC";
	assert(find_N(pattern, text).size() == 2);
	assert(find_N(pattern, text)[0] == 0);
	assert(find_N(pattern, text)[1] == 3);

	// check what if no pattern found
	pattern = "ZZ";
	text = "ABCABC";
	assert(find_N(pattern, text).size() == 0);
}
