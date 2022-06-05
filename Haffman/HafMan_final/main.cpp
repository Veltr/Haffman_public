//HafMan.exe 1 Test5.txt out.dat out.txt
//#include "HafManArc.h"
#include "haffmanarchiver.h"

int main(int argc, char* argv[]){
    /*HafManArc arc("in.txt", "out.dat");
    //arc.ProssedArc();
    arc.ProssedDeArc("out.dat", "out.txt");*/

    /*HafManArc arc("main.cpp", "out1.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out1.dat", "out1.txt");*/

    /*HafManArc arc("Test.bmp", "out2.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out2.dat", "out2.bmp");*/

    /*HafManArc arc("maxresdefault.bmp", "out3.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out3.dat", "out3.bmp");*/

    /*HafManArc arc("Tpdf.pdf", "out4.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out4.dat", "out4.pdf");*/

    /*HafManArc arc("Test5.txt", "out5.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out5.dat", "out5.txt");*/

    /*HafManArc arc("Test6.txt", "out6.dat");
    arc.ProssedArc();
    arc.ProssedDeArc("out6.dat", "out6.txt");*/

    HaffmanArchiver arc("maxresdefault.bmp", "out3.dat");
    arc.ProssedArchiving();
    arc.ProssedDearchiving("out3.dat", "out3.bmp");

    //for(int i = 0; i < argc; i++) std::cout << i << ") " << argv[i] << '\n';

    /*HafmanArchiver arc(argv[2], argv[3]);
    arc.ProssedArc();
    arc.ProssedDeArc(argv[3], argv[4]);*/

    std::cout << "Done\n";
}
