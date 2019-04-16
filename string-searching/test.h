//
// Created by Michal Korzeniewski on 2019-04-16.
//

#ifndef AISDI_LAB_TEST_H
#define AISDI_LAB_TEST_H

#include <cstdlib>
#include <vector>
#include "find_str_util.h"


char randomChar() { return 'A' + rand() % 3; }

void board_case_test() {

    /**
     * begin
     */
    std::string text = "";
    std::string pattern = "";
    std::vector<int> result;


    /**
     * when
     */
    result = find(pattern, text);

    /**
     * then
     */
    assert(result.empty() == true);

    /**
     * given
     */
    int text_predefined_size = 100;
    for (int i = 0; i < text_predefined_size; ++i) {
        text += randomChar();
    }
    /**
     * when
     */
    result = find(pattern, text);
    /**
     * then
     */
    assert(result.empty() == false);
    assert(result.size() == text.size());
    for (int i = 0; i < text.size(); ++i) {
        assert(result.at(i) == i);
    }

    /**
     * given
     */
    pattern = text;
    /**
     * when
     */
    result = find(pattern, text);
    /**
     * then
     */
    assert(result.empty() == false);
    assert(result.size() == 1);
    assert(result.at(0) == 0);

}

void random_case_test() {
    std::string text, pattern;

    int text_predefined_size = 1000;
    for (int i = 0; i < text_predefined_size; ++i) {
        text += randomChar();
    }
    int pattern_predefined_size = 3;
    for (int i = 0; i < pattern_predefined_size; ++i) {
        pattern += randomChar();
    }
    std::vector<int> result = find(pattern, text);

    std::cout << "pattern:\n" << pattern << std::endl;

    std::cout << "Pattern was occured at: ";
    for (auto i = result.begin(); i < result.end(); ++i) {
        std::cout << *i << ", ";
    }

}


#endif //AISDI_LAB_TEST_H
