#ifndef DICTIONARIES_TEST_H
#define DICTIONARIES_TEST_H

#include <cassert>
#include <string>

#include <map>
#include <random>
#include <algorithm>
#include "fileUtility.h"
#include "timeUtility.h"

void unit_test() {
    TreeMap<int, int> dict;

    // slownik jest pusty
    assert(dict.isEmpty() == true);
    assert(dict.size() == 0);
    assert(dict.contains(0) == false);

    // dodanie elementu do slownika
    dict.insert(0, 1);
    assert(dict.isEmpty() == false);
    assert(dict.size() == 1);
    assert(dict.contains(0) == true);
    assert(dict.value(0) == 1);

    // dodanie elementu do slownika jako pary
    dict.insert(std::pair<int, int>(1, 2));
    assert(dict.size() == 2);
    assert(dict.contains(1) == true);
    assert(dict.value(0) == 1);
    assert(dict.value(1) == 2);

    // operator []
    assert(dict[0] == 1);
    assert(dict[1] == 2);

    // operator [] tworzy nowy element
    dict[2] = 3;
    assert(dict.value(2) == 3);
    assert(dict.size() == 3);


    // nadpisanie wartosci dla istniejacego elementu
    dict.insert(2, 4);
    assert(dict.size() == 3);
    assert(dict.value(2) == 4);
}

void insert_test() {
    TreeMap<int, int> dict;

    // slownik jest pusty
    assert(dict.isEmpty() == true);
    assert(dict.size() == 0);
    assert(dict.contains(0) == false);

    // dodanie elementow do slownika
    dict.insert(1, 11);
    dict.insert(2, 12);
    dict.insert(3, 13);
    dict.insert(4, 14);
    dict.insert(5, 15);
    assert(dict.size() == 5);
    assert(dict.contains(0) == false);
    assert(dict.contains(1) == true);
    assert(dict.contains(2) == true);
    assert(dict.contains(3) == true);
    assert(dict.contains(4) == true);
    assert(dict.contains(5) == true);

}

void insert_test2() {
	TreeMap<int, std::string> dict;

	// slownik jest pusty
	assert(dict.isEmpty() == true);
	assert(dict.size() == 0);
	assert(dict.contains(5) == false);

	// dodanie elementow do slownika
	dict.insert(1, "");
	dict.insert(2, "");
	dict.insert(3, "");
	dict.insert(4, "");
	dict.insert(5, "k");
	assert(dict.size() == 5);
	assert(dict.contains(0) == false);
	assert(dict.contains(1) == true);
	assert(dict.contains(5) == true);
}

void testRaportGenerator(
        int numOfAllElements,
        int testNumber,
        size_t measureCustomSplaySolution,
        size_t measureOneCustomSplaySolution,
        size_t measureStdSolution,
        size_t measureOneStdSolution,
        const std::string &testType);


void compare_test(const int WORDS_TEST_NUMBER) {
    if (WORDS_TEST_NUMBER == 0)
        throw std::runtime_error("Shouldn't be zero");

    FileTest panTadeuszFile;
    TreeMap<int, std::string> wordSplayTree;
    std::map<int, std::string> wordMapTree;
    Benchmark <std::chrono::nanoseconds> benchmarkNano;


    std::vector<int> v;
    for (int keyNumber = 0; keyNumber < WORDS_TEST_NUMBER - 1; ++keyNumber) {
        v.push_back(keyNumber);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);


    /**
     * Insert test
     */

    std::string wordTable[WORDS_TEST_NUMBER];
    panTadeuszFile.readWordsToTable(wordTable);

    // custom splay solution test

    size_t measureInsertsCustomSplaySolution = benchmarkNano.elapsed();
    for (auto keyNumber = v.begin(); keyNumber < v.end() - 1; ++keyNumber) {
        int key = *keyNumber;
        wordSplayTree.insert(key, wordTable[*keyNumber]);
    }
    measureInsertsCustomSplaySolution = benchmarkNano.elapsed() - measureInsertsCustomSplaySolution;

    size_t measureInsertOneCustomSplaySolution = benchmarkNano.elapsed();
    wordSplayTree.insert(*v.end(), wordTable[WORDS_TEST_NUMBER - 1]);
    measureInsertOneCustomSplaySolution = benchmarkNano.elapsed() - measureInsertOneCustomSplaySolution;


    // map test
    size_t measureInsertsStdSolution = benchmarkNano.elapsed();
    for (auto keyNumber = v.begin(); keyNumber < v.end() - 1; ++keyNumber) {
        std::pair<int, std::string> temp(*keyNumber, wordTable[*keyNumber]);
        wordMapTree.insert(temp);
    }
    measureInsertsStdSolution = benchmarkNano.elapsed() - measureInsertsStdSolution;

    std::pair<int, std::string> temp(*v.end(), wordTable[WORDS_TEST_NUMBER - 1]);

    size_t measureInsertOneStdSolution = benchmarkNano.elapsed();
    wordMapTree.insert(temp);
    measureInsertOneStdSolution = benchmarkNano.elapsed() - measureInsertOneStdSolution;

    testRaportGenerator(
            WORDS_TEST_NUMBER,
            WORDS_TEST_NUMBER,
            measureInsertsCustomSplaySolution,
            measureInsertOneCustomSplaySolution,
            measureInsertsStdSolution,
            measureInsertOneStdSolution,
            "insert");


    /**
     * Search test
     */
    int numToFind =
            WORDS_TEST_NUMBER > 10 ? (WORDS_TEST_NUMBER > 1000 ? WORDS_TEST_NUMBER / 100 : WORDS_TEST_NUMBER / 10)
                                   : WORDS_TEST_NUMBER;

    size_t measureSearchCustomSplaySolution = benchmarkNano.elapsed();
    for (int keyNumber = 0; keyNumber < numToFind; ++keyNumber) {
        wordSplayTree.contains(rand() % WORDS_TEST_NUMBER);
    }
    measureSearchCustomSplaySolution = benchmarkNano.elapsed() - measureSearchCustomSplaySolution;

    size_t measureSearchOneCustomSplaySolution = measureSearchCustomSplaySolution / numToFind;

    size_t measureSearchStdSolution = benchmarkNano.elapsed();
    for (int keyNumber = 0; keyNumber < numToFind; ++keyNumber) {
        wordMapTree.find(rand() % WORDS_TEST_NUMBER);
    }
    measureSearchStdSolution = benchmarkNano.elapsed() - measureSearchStdSolution;

    size_t measureOneSearchStdSolution = measureSearchStdSolution / numToFind;


    testRaportGenerator(
            WORDS_TEST_NUMBER,
            numToFind,
            measureSearchCustomSplaySolution,
            measureSearchOneCustomSplaySolution,
            measureSearchStdSolution,
            measureOneSearchStdSolution,
            "search");

}

std::string ms2stringConverter(size_t measureCustomSplaySolution) {
    int nano = 1000000000;
    size_t min = measureCustomSplaySolution / 60 / nano;
    size_t sec = (measureCustomSplaySolution - min * 60 * nano) / nano;
    size_t nsec = (measureCustomSplaySolution - sec * nano - min * 60 * nano);
    return std::to_string(min) + " min " + std::to_string(sec) + "." + std::to_string(nsec) + "sec";
}

void testRaportGenerator(
        const int numOfAllElements,
        const int testNumber,
        size_t measureCustomSplaySolution,
        size_t measureOneCustomSplaySolution,
        size_t measureStdSolution,
        size_t measureOneStdSolution,
        const std::string &testType) {
    std::string customSplayTime = ms2stringConverter(measureCustomSplaySolution);
    std::string stdTime = ms2stringConverter(measureStdSolution);

    std::cout << "Test " << testType << " of " << testNumber << " words \n";
    std::cout << "Splay " + testType + " time \t" << customSplayTime;
    std::cout << " One word was " + testType + "ed in " << measureOneCustomSplaySolution << " nanosec";
    std::cout << std::endl;
    std::cout << "Map " + testType + " time \t" << stdTime;
    std::cout << " One word was " + testType + "ed in " << measureOneStdSolution << " nanosec";
    std::cout << std::endl << "-----------------------" << std::endl;


    std::fstream resultFile;
    resultFile.open("../data.csv", std::ios::out | std::ios::app);
//    resultFile << "type,num of all,num,custom,onecustom,std,onestd";
//    resultFile << std::endl;
    resultFile << testType << ",";
    resultFile << numOfAllElements << ",";
    resultFile << testNumber << ",";
    resultFile << measureCustomSplaySolution << ",";
    resultFile << measureOneCustomSplaySolution << ",";
    resultFile << measureStdSolution << ",";
    resultFile << measureOneStdSolution << std::endl;

}

#endif //DICTIONARIES_TEST_H
