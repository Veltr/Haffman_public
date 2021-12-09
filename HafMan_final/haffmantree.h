#ifndef HAFMANTREE_H
#define HAFMANTREE_H

#include <iostream>
#include <vector>

/*!
 * \brief Узел дерева Хаффмана
 *
 * Данный класс содержит значения узлов дерева Хаффмана
 */

class HaffmanTreeNode{
public:
    HaffmanTreeNode();
    HaffmanTreeNode(float frequency);
    HaffmanTreeNode(float frequency, char value_);
    ~HaffmanTreeNode();

    HaffmanTreeNode * first, * second;
    float currentFrequency;
    char value;
    bool haveValue = false;
};

/*!
 * \brief Дерево Хаффмана
 *
 * Данный класс хранит в себе дерево, построенное по таблице Хаффмана
 */

class HaffmanTree{
public:
    HaffmanTreeNode* start;

    bool TryGetChar(int currentBit, char& out);
    std::vector<std::string>& GetPrefixes();
    void Clear();

private:
    HaffmanTreeNode* _currentNode = NULL;

    void GetPrefixesFunction(HaffmanTreeNode* Node, std::vector<std::string>& v, std::string word = "");
};

#endif // HAFMANTREE_H
