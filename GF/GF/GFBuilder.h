#ifndef GFBUILDER_H
#define GFBUILDER_H

// В векторе в начале стоит старшая степень
// Работает только если старший k исходного m0 = 1

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <string>

class GFs{
public:
    GFs(int mode, int p);
    void buildGF(const std::list<int>& m);
    void getRevElems();
    void getZetch();
    void printGF();
    void printRevs();
    void printZetch();

private:
    int _mode;
    size_t _p;

    std::vector<std::list<int>> _gf;
    std::vector<size_t> _revs;
    std::vector<int> _zetch;
    std::list<int> _m;
    size_t _fieldSize;
};

GFs::GFs(int mode, int p){
    _p = p;
    _mode = mode;
}

void GFs::buildGF(const std::list<int>& m0){
    _fieldSize = pow(_mode, _p);
    _gf.resize(_fieldSize);

    for(auto i = (++m0.begin()); i != m0.end(); i++) {
        int t = (-(*i)) % _mode;
        if(t < 0) t += _mode;
        _m.push_back(t);
    }

    std::list<int> t0; t0.push_back(0);
    _gf[0] = t0;
    t0.erase(t0.begin()); t0.push_back(1); _gf[1] = t0;
    t0.push_back(0); _gf[2] = t0;

    for(size_t i = 3; i < _fieldSize; i++){
        _gf[i] = _gf[i - 1];
        _gf[i].push_back(0);

        if(_gf[i].size() > _p){
            std::list<int> t(_m);
            int k1 = *_gf[i].begin();
            _gf[i].pop_front();
            for(auto ii = t.begin(), iii = _gf[i].begin(); ii != t.end(); ii++, iii++){
                *ii = (*ii * k1) % _mode;
                *iii = (*iii + *ii) % _mode;
            }
            while(!(*_gf[i].begin())) _gf[i].pop_front();
        }
    }
}

void GFs::getRevElems(){
    _revs.resize(_fieldSize); _revs[0] = 0;
    for(size_t i = 1; i < _revs.size(); i++){
        for(size_t ii = 1; ii < _gf.size(); ii++){
            if(i == ii || _gf[i].size() != _gf[ii].size()) continue;
            for(auto iii = _gf[ii].begin(), iiii = _gf[i].begin(); iii != _gf[ii].end(); iii++, iiii++)
                if((*iii + *iiii) % _mode) goto rskip;
            _revs[i] = ii;
rskip:      continue;
        }
    }
}

void GFs::getZetch(){
    _zetch.resize(_fieldSize); _zetch[0] = -1;

    for(size_t i = 1; i < _zetch.size(); i++){
        std::list<int> t(_gf[i]);
        t.back() = (t.back() + 1) % _mode;
        for(size_t ii = 0; ii < _gf.size(); ii++){
            if(i == ii || t.size() != _gf[ii].size()) continue;
            for(auto iii = _gf[ii].begin(), iiii = t.begin(); iii != _gf[ii].end(); iii++, iiii++)
                if(*iii != *iiii) goto zskip;
            _zetch[i] = ii;
zskip:      continue;
        }
    }
}

void GFs::printGF(){
    std::cout << "0) 0\n1) 1\na) a\n";
    for(size_t i = 3, ip; i < _gf.size(); i++){
        std::cout << "a^" << i - 1 << ") ";
        ip = _gf[i].size() - 1;
        std::string t = ""; bool bt = false;
        for(auto ii = _gf[i].begin(); ii != _gf[i].end(); ii++, ip--)
            if(*ii){
                if((*ii > 1) || (ip < 1)) t += std::to_string(*ii);
                if(ip > 0){
                    t += "a";
                    if(ip > 1) t += '^' + std::to_string(ip);
                }
                t += " + ";
                bt = true;
            }
        t[t.size() - 2] = '\0';
        std::cout << t << '\n';
    }
}

void GFs::printRevs(){
    std::cout << "0) 0\n";
    for(size_t i = 1; i < _revs.size(); i++)
        std::cout << "a^" << i - 1 << ") a^" << _revs[i] - 1 << '\n';
}

void GFs::printZetch(){
    std::cout << "0) 1\n";
    for(size_t i = 1; i < _zetch.size(); i++)
        std::cout << "a^" << i - 1 << ") a^" << _zetch[i] - 1  << '\n';
}

/*void GFs::buildGF(const std::list<int>& m0){
    _fieldSize = pow(_mode, _p);
    _gf.resize(_fieldSize + 1);

    for(auto i = (++m0.begin()); i != m0.end(); i++) {
        //_m[i] = (-_m[i]) % _mode;
        //if(_m[i] < 0) _m[i] += _mode;

        int t = (-(*i)) % _mode;
        if(t < 0) t += _mode;
        _m.push_back(t);
    }
    _baseSize = _m.size();

    std::list<int> t0; t0.push_back(0);
    _gf[0] = t0;
    t0.erase(t0.begin()); t0.push_back(1); _gf[1] = t0;
    t0.push_back(0); _gf[2] = t0;

    for(size_t i = 3; i <= _fieldSize; i++){
        _gf[i] = _gf[i - 1];
        _gf[i].push_back(0);

        if(_gf[i].size() > _baseSize){
            std::list<int> t(_m);
            int k1 = *_gf[i].begin();
            _gf[i].pop_front();
            for(auto ii = t.begin(), iii = _gf[i].begin(); ii != t.end(); ii++, iii++){
                *ii = (*ii * k1) % _mode;
                *iii = (*iii + *ii) % _mode;
            }
            while(!(*_gf[i].begin())) _gf[i].pop_front();
        }
    }

    std::cout << "HOU";
}*/

#endif // GFBUILDER_H
