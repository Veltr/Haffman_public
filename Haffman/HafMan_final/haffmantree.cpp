#include "haffmantree.h"

//===========HafmanTree===============================================

/*!
 * \brief Найти префиксы
 * \details Запускает рекурсивную функцию поиска префиксев в дереве.
 *  В случае, если в дереве содержится один префикс, возвращает его.
 * \return Найденные префиксы
 */

std::vector<std::string>& HaffmanTree::GetPrefixes(){
    std::vector<std::string>& v = *(new std::vector<std::string>());
    v.assign(256, "");
    if(start->haveValue){
        size_t t = (start->value < 0 ? 256 + ((int)start->value) : start->value);
        v[t] = "0";
        return v;
    }
    GetPrefixesFunction(start, v);

    return v;
}

/*!
 * \brief Найти префиксы
 * \details Рекурсивная функция поиска префиксев в дереве
 * \param Node Текущая вершина
 * \param v Вектор, в который производиться запись
 * \param word Текущее найденное слово
 */

void HaffmanTree::GetPrefixesFunction(HaffmanTreeNode* Node, std::vector<std::string>& v, std::string word){
    if(Node->haveValue){
        size_t t = (Node->value < 0 ? 256 + ((int)Node->value) : Node->value);
        v[t] = word;
        return;
    }
    if(Node->first) GetPrefixesFunction(Node->first, v, word + "0");
    if(Node->second) GetPrefixesFunction(Node->second, v, word + "1");
}

/*!
 * \brief Достать префикс из дерева
 * \details Проход по дереву, в попытке найти следующий символ
 * \param currentBit Если равен нулю, перейти к первому узлу, иначе ко второму
 * \param out Ссылка, в которую записывается следующий символ, если он найден
 * \return true если символ найден, иначе false
 */

bool HaffmanTree::TryGetChar(int currentBit, char& out){
    if(!_currentNode) {
        _currentNode = start;
        if(_currentNode->haveValue) { out = _currentNode->value; return true; }
    }

    if(!currentBit) _currentNode = _currentNode->first;
    else _currentNode = _currentNode->second;

    if(_currentNode->haveValue) { out = _currentNode->value; _currentNode = start; return true; }
    return false;
}

/*!
 * \brief Очистка дерева
 *
 * Пока что ничерта не делает, так как автор не знает, что тут писать
 * \todo Видимо, что-то здесь надо сделать
 */

void HaffmanTree::Clear(){

}

//===========HafmanTreeNode===============================================

/*!
 * \brief Пустой узел
 * \details Все поля класса обнуляются
 */

HaffmanTreeNode::HaffmanTreeNode(){
    first = NULL;
    second = NULL;
    currentFrequency = .0;
    value = 0;
    haveValue = false;
}

/*!
 * \brief Узел без префикса
 * \details Используется во время построении дерева
 * \param frequency Текущая частота
 */

HaffmanTreeNode::HaffmanTreeNode(float frequency) : HaffmanTreeNode(){
    currentFrequency = frequency;
}

/*!
 * \brief Узел с префиксом
 * \param frequency Текущая частота
 * \param value_ Текущий префикс
 */

HaffmanTreeNode::HaffmanTreeNode(float frequency, char value_) : HaffmanTreeNode(){
    currentFrequency = frequency;
    value = value_;
    haveValue = true;
}

/*!
 * \brief Очистка значений
 *
 * \todo Придумать, что тут вообще очищать
 */

HaffmanTreeNode::~HaffmanTreeNode(){

}
