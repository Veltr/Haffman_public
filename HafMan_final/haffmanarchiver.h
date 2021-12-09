#ifndef HAFMANARCHIVER_H
#define HAFMANARCHIVER_H

#include "haffmantree.h"

#include <stdio.h>
#include <fstream>
#include <vector>
#include <set>
#include <list>

/*!
 * \brief Архиватор Хаффмана
 *
 * Данный класс представляет из себя набор методов для работы по алгоритму Хаффмана
 */

class HaffmanArchiver{
public:
    HaffmanArchiver();
    HaffmanArchiver(std::string inputFilePath, std::string outputFilePath);

    void SetFilesPath(std::string inputFilePath, std::string outputFilePath);
    int ProssedArchiving();
    int ProssedDearchiving();
    int ProssedArchiving(std::string inputFilePath, std::string outputFilePath);
    int ProssedDearchiving(std::string inputFilePath, std::string outputFilePath);

private:
    std::string _inputFilePath;
    std::string _outputFilePath;

    std::ifstream _inputFile;
    std::ofstream _outputFile;
    std::string _buffer;

    std::set<std::pair<float, char>> _frequency;
    HaffmanTree _prefixesTree;
    std::vector<std::string>* _prefixes;

    void GetFrequency();
    void GetFrequency(int charactersNumber);
    void GetHafmanTree();
    void MakeArchive();
    void MakeDearchive(int lastBitOffset);
};

#endif // HAFMANARCHIVER_H
