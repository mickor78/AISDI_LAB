//
// Created by Michal Korzeniewski on 2019-04-13.
//

#ifndef DICTIONARIES_FILEUTILITY_H
#define DICTIONARIES_FILEUTILITY_H


#include "fstream"


class FileTest {
public:

    FileTest() {
        testFileInput.open("../pan-tadeusz.txt");
        if (!testFileInput.good())
            throw std::runtime_error("File ./pan-tadeusz.txt doesn't exist.");
    }

    FileTest(std::string fileName) {
        testFileInput.open(fileName);
        if (!testFileInput.good())
            throw std::runtime_error("File " + fileName + " doesn't exist.");
    };

    virtual ~FileTest() {
        testFileInput.close();
    };


    std::string readWord() {
        std::string letter, word;
        while (!testFileInput.eof()) {
            letter = std::to_string(testFileInput.get());
            if (letter != " " || letter != "\n")
                word += letter;
            else {
                if (!word.empty()) return word;
            }
        }

        //TODO
        //what if I you would like to read the file once again???
        //here the destructor should be called maybe

        return "";
    }

    void readWordsToTable(std::string *stringTable) {
        std::string *tablePointer = stringTable;
        while (!testFileInput.eof() && tablePointer != nullptr) {
            *tablePointer = readWord();
            tablePointer++;
        }
        //TODO
        //what if I you would like to read the file once again???
        //here the destructor should be called maybe
    }

private:
    std::fstream testFileInput;
};

#endif //DICTIONARIES_FILEUTILITY_H
