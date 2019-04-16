//
// Created by Michal Korzeniewski on 2019-04-16.
//

#ifndef AISDI_LAB_FIND_STR_UTIL_H
#define AISDI_LAB_FIND_STR_UTIL_H

#include <cmath>

int hash(const std::string &str);


void next_window_hash(int &fingerprint, const std::string &text, int position, int pattern_size);

std::vector<int> find(const std::string &str, const std::string &text) {
    std::cout << "hash: \n" << hash(str) << " " << hash(text.substr(0, str.size())) << " " << text.substr(0, str.size())
              << std::endl;
    std::vector<int> result;

    int str_fingerprint = hash(str);
    int window_fingerprint = hash(text.substr(0, str.size()));

    for (int i = 0; i < text.size() - str.size(); ++i) {
        if (str_fingerprint == window_fingerprint) {
            result.push_back(i);
        } else {
            next_window_hash(window_fingerprint, text, i, str.size());
        }
    }


    return std::vector<int>(6);
}

void next_window_hash(int &fingerprint, const std::string &text, int position, int pattern_size) {

};


int hash(const std::string &str) {
    int first_prime = 13, second_prime = 1017064787;

    int fingerprint = 0, temp;
    for (int i = 0; i < str.size(); ++i) {
        temp = str.at(i);
        for (int j = 0; j < str.size() - i; ++j) {
            temp *= first_prime;
        }
        fingerprint += temp;
    }
    return fingerprint % second_prime;
}

#endif //AISDI_LAB_FIND_STR_UTIL_H
