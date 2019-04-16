//
// Created by Michal Korzeniewski on 2019-04-16.
//

#include <iostream>
#include <vector>
#include <string>

#ifndef AISDI_LAB_FIND_STR_UTIL_H
#define AISDI_LAB_FIND_STR_UTIL_H

#include <cmath>



int hash(const std::string &str);

void next_window_hash(int &fingerprint, const std::string &text, int position, int pattern_size);

bool check_if_pattern_maches_text_at_i(const std::string &str, const std::string &text, int i);

std::vector<int> find(const std::string &str, const std::string &text) {
    std::vector<int> result;
    std::string vizualization;

    if (str.empty()) {
        for (int i = 0; i < text.size(); ++i) {
            result.push_back(i);
        }
        return result;
    }

    int str_fingerprint = hash(str);
    int window_fingerprint = hash(text.substr(0, str.size()));

    for (int i = 0; i < text.size() - str.size() + 1; ++i) {

        if (str_fingerprint == window_fingerprint) {
            bool match = check_if_pattern_maches_text_at_i(str, text, i);

            if (match) {
                result.push_back(i);
                vizualization += "^";
            }
        } else {
            vizualization += " ";
        }

        if (i != text.size() - str.size())
            next_window_hash(window_fingerprint, text, i, str.size());
    }

    std::cout << text << std::endl;
    std::cout << vizualization << std::endl;

    return result;
}

bool check_if_pattern_maches_text_at_i(const std::string &str, const std::string &text, int i) {
    bool match = true;
    for (int j = 0; j < str.size(); ++j) {
        if (str.at(j) != text.at(i + j)) {
            match = false;
            break;
        }
    }
    return match;
}

void next_window_hash(int &fingerprint, const std::string &text, int position, int pattern_size) {
    int first_prime = 13, second_prime = 1017064787;

    int temp = text.at(position);
    for (int i = 0; i < pattern_size - 1; ++i) {
        temp *= first_prime;
    }
    fingerprint = (fingerprint - temp) % second_prime;
    fingerprint = (fingerprint * first_prime) % second_prime;
    fingerprint = (fingerprint + text.at(position + pattern_size)) % second_prime;
}


int hash(const std::string &str) {
    int first_prime = 13, second_prime = 1017064787;

    int fingerprint = 0, temp;
    for (int i = 0; i < str.size(); ++i) {
        temp = str.at(i);
        for (int j = 0; j < str.size() - i - 1; ++j) {
            temp *= first_prime;
        }
        fingerprint += temp;
    }
    return fingerprint % second_prime;
}

#endif //AISDI_LAB_FIND_STR_UTIL_H
