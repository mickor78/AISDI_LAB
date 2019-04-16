//
// Created by Kamil Zych on 17.04.2019.
//

#include <iostream>
#include <vector>
#include <string>

#ifndef AISDI_FIND_STR_UTIL2_H
#define AISDI_FIND_STR_UTIL2_H


std::vector<int> find_N(const std::string &pattern, const std::string &text) {

	std::vector<int> result;
	std::string window;
	const unsigned int window_size = pattern.length();
	bool isMatch(false), isEndOfString(false);
	unsigned int fingerPosition(0);

	if(pattern.length() != 0 or window_size > text.length()){

		while(not isEndOfString)
		{
			window = text.substr(fingerPosition, window_size);

			isMatch = true;
			for (int i=0; i<window_size; ++i)
			{
				if (window[i] != pattern[i])
				{
					isMatch = false;
					break;
				}
			}
			if (isMatch){
				result.push_back(fingerPosition);
			}

			if(++fingerPosition + window_size > text.length())
				isEndOfString = true;
		}
	}

	return result;
}

std::vector<int> prefixFun(const std::string &text) {

	std::vector<int> result(text.length(), 0);
	int fingerPosition(0);

	if (text.length() > 1) {

		for(int k=1; k<text.length(); k++)
		{
			while(fingerPosition>0 && text[k] != text[fingerPosition])
				fingerPosition=result[fingerPosition-1];

			if(text[k] == text[fingerPosition])
				result[k] = ++fingerPosition;
			else
				result[k] = 0;
		}

	} else if (text.length() == 2 and text[0] == text [1])
			result[1] = 1;

	return result;
}




#endif //AISDI_FIND_STR_UTIL2_H
