#include "GFBuilder.h"

int main(){
    // GF(3^2) x^2 + x + 2
    /*std::list<int> a;
    a.push_back(1); a.push_back(1); a.push_back(2);
    GFs b(3, 2); b.buildGF(a); b.printGF();*/

    // GF(3^2) x^2 + 2x + 2
    std::list<int> a = {1, 2, 2};
    GFs b(3, 2);
    b.buildGF(a); b.printGF(); std::cout << '\n';
    b.getRevElems(); b.printRevs(); std::cout << '\n';
    b.getZetch(); b.printZetch();

    // GF(3^3) x^3 + 2x^2 + 1
    /*std::list<int> a = {1, 2, 0, 1};
    GFs b(3, 3); b.buildGF(a); b.printGF();*/

    // GF(5^4) x^4 + x^2 + 2x + 2
    /*std::list<int> a = {1, 0, 1, 2, 2};
    GFs b(5, 4);
    b.buildGF(a); b.printGF(); std::cout << '\n';
    b.getRevElems(); b.printRevs(); std::cout << '\n';
    b.getZetch(); b.printZetch();*/

    std::cout << "Done\n";
}
