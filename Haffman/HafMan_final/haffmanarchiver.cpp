#include "haffmanarchiver.h"

//=======Public=======================================

/*!
 * \brief Пустой объект
 * \details Путь к файлам не указан
 */

HaffmanArchiver::HaffmanArchiver(){
    _inputFilePath = "";
    _outputFilePath = "";
}

/*!
 * \brief Объект с указанными путями к файлам
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 */

HaffmanArchiver::HaffmanArchiver(std::string inputFilePath, std::string outputFilePath){
    _inputFilePath = inputFilePath;
    _outputFilePath = outputFilePath;
}

/*!
 * \brief Указание путей к файлам
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 */

void HaffmanArchiver::SetFilesPath(std::string inputFilePath, std::string outputFilePath){
    _inputFilePath = inputFilePath;
    _outputFilePath = outputFilePath;
}

/*!
 * \brief Выполнить архивацию с заданными файлами
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 * \return 0 в случае успеха, иначе код ошибки
 */

int HaffmanArchiver::ProssedArchiving(std::string inputFilePath, std::string outputFilePath){
    SetFilesPath(inputFilePath, outputFilePath);
    return ProssedArchiving();
}

/*!
 * \brief Выполнить деархивацию с заданными файлами
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 * \return 0 в случае успеха, иначе код ошибки
 */

int HaffmanArchiver::ProssedDearchiving(std::string inputFilePath, std::string outputFilePath){
    SetFilesPath(inputFilePath, outputFilePath);
    return ProssedDearchiving();
}

/*!
 * \brief Выполнить архивацию
 * \details Выполняется архивация с текущими сохраненными путями к файлам
 * \return 0 в случае успеха, иначе код ошибки
 */

int HaffmanArchiver::ProssedArchiving(){
    _inputFile.open(_inputFilePath, std::ios::in | std::ios::binary);
    if(!_inputFile){
        std::cerr << "Can't open file 1\n";
        return 1;
    }
    GetFrequency();
    _inputFile.close();

    GetHafmanTree();
    _prefixes = &(_prefixesTree.GetPrefixes());

    _outputFile.open(_outputFilePath, std::ios::binary | std::ios::out);
    if (!_outputFile) {
        std::cout << "File error - can't open to write data!\n";
        return 2;
    }
    MakeArchive();
    _outputFile.close();
    return 0;
}

/*!
 * \brief Выполнить деархивацию
 * \details Выполняется деархивация с текущими сохраненными путями к файлам
 * \return 0 в случае успеха, иначе код ошибки
 */

int HaffmanArchiver::ProssedDearchiving(){
    char charactersNumber; char lastBitOffset;
    _inputFile.open(_inputFilePath, std::ios::in | std::ios::binary);
    if(!_inputFile){
        std::cerr << "Can't open file 2\n";
        return 1;
    }
    _inputFile >> charactersNumber >> lastBitOffset;

    GetFrequency(charactersNumber);
    GetHafmanTree();

    _outputFile.open(_outputFilePath, std::ios::binary | std::ios::out);
    if (!_outputFile) {
        std::cout << "File error - can't open to write data!\n";
        return 2;
    }
    MakeDearchive(lastBitOffset);

    _inputFile.close();
    _outputFile.close();
    return 0;
}

//=======Private=======================================================

void HaffmanArchiver::GetFrequency(){
    _buffer = ""; _frequency.clear();
    std::vector<int> v(256, 0);

    char c;
    while (_inputFile.read(&c, 1)) {
        size_t t = (c < 0 ? 256 + ((int)c) : c);
        v[t]++;
        _buffer += c;
    }

    for(size_t i = 0; i < v.size(); i++)
        if(v[i]) _frequency.insert({ (float)v[i] / _buffer.size(), (char)i});
}

void HaffmanArchiver::GetFrequency(int charactersNumber){
    if(!charactersNumber) charactersNumber = 256;
    _frequency.clear();
    char *t = new char[5]; float f;
    for(int i = 0; i < charactersNumber; i++){
        _inputFile.read(t, 5);
        memcpy(&f, t + 1, sizeof (float));
        _frequency.insert({f, *t});
    }
    delete [] t;
}

void HaffmanArchiver::GetHafmanTree(){
    _prefixesTree.Clear();
    std::list<HaffmanTreeNode*> HafmanTreeNodes;
    for(auto i = _frequency.begin(); i != _frequency.end(); i++)
        HafmanTreeNodes.push_back(new HaffmanTreeNode(i->first, i->second));

    while(1){
start1:
        if(HafmanTreeNodes.size() <= 1) break;
        auto i = HafmanTreeNodes.begin(), j = (++i)--;
        HaffmanTreeNode* t = new HaffmanTreeNode((*i)->currentFrequency + (*j)->currentFrequency);
        t->first = *i; t->second = *j;
        HafmanTreeNodes.erase(i); HafmanTreeNodes.erase(j);

        for(auto ii = HafmanTreeNodes.end(); ii != HafmanTreeNodes.begin();)
            if((*(--ii))->currentFrequency <= t->currentFrequency){ HafmanTreeNodes.insert(++ii, t); goto start1; }

        HafmanTreeNodes.push_front(t);
    }

    _prefixesTree.start = *HafmanTreeNodes.begin();
}

void HaffmanArchiver::MakeArchive(){
    _outputFile.put(_frequency.size());
    _outputFile.put('\0');

    for(auto i = _frequency.begin(); i != _frequency.end(); i++){
        _outputFile.put(i->second);
        float f = (i->first);
        char *t = reinterpret_cast<char *>(&f);
        for(int j = 0; j < 4; j++) _outputFile.put(t[j]);
    }

    int offset = 0; char currentByte = 0;
    for (size_t i = 0; i < _buffer.size(); i++) {
        size_t bt = (_buffer[i] < 0 ? 256 + ((int)_buffer[i]) : _buffer[i]);
        for(size_t j = 0; j < (*_prefixes)[bt].size(); j++){
            if((*_prefixes)[bt][j] == '0') currentByte <<= 1;
            else currentByte = (currentByte << 1) | 1;

            if((++offset) >= 8){
                _outputFile.put(currentByte);
                offset = 0;
            }
        }
    }

    if(offset){
        currentByte <<= 8 - offset;
        _outputFile.put(currentByte);
    }
    currentByte = !offset ? 8 : offset;

    _outputFile.seekp(1);
    _outputFile.put(currentByte);
}

void HaffmanArchiver::MakeDearchive(int lastBitOffset){
    char c0, c1, t;
    bool oneByte = true;
    int mask = 0b10000000;
    _inputFile.get(c0);
    while (1) {
        if(_inputFile.get(c1)){
            for(int i = 0; i < 8; i++){
                if(_prefixesTree.TryGetChar(c0 & mask, t)) _outputFile.put(t);
                c0 <<= 1;
            }
            c0 = c1;
            oneByte = false;
        }
        else{
            if(oneByte) c1 = c0;
            for(int i = 0; i < lastBitOffset; i++){
                if(_prefixesTree.TryGetChar(c1 & mask, t)) _outputFile.put(t);
                c1 <<= 1;
            }
            break;
        }
    }
}
