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


    void readWordsToTable(std::string *stringTable, int size) {
        for (int i = 0; testFileInput.eof() || i < size; ++i) {
            *stringTable = readWord();
            stringTable++;
        }

        //TODO
        //what if I you would like to read the file once again???
        //here the destructor should be called maybe
    }

private:

    std::fstream testFileInput;

    std::string readWord() {
        char letter;
        std::string word;
        while (!testFileInput.eof()) {
            letter = testFileInput.get();
            if (letter != ' ' && letter != '\r' && letter != '\n' && letter != ',')
                word += letter;
            else {
                if (!word.empty() && word != "—") return word;
                word = "";
            }
        }

        //TODO
        //what if I you would like to read the file once again???
        //here the destructor should be called maybe

        return "";
    }
};

#endif //DICTIONARIES_FILEUTILITY_H
