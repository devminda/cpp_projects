#include <iostream>
#include "hanoi.h"

int main(int argc, const char* argv[]) {

    std::cout << "-----------------Tower of Three-------------------" << std::endl;
    Hanoi h(7, 3); // create a Hanoi tower
    h.print();
    h.move(7, 0, 2, 1);
    h.print();

    std::cout << "------------------Tower of four------------------" << std::endl;
    Hanoi4 h1(7, 4);
    h1.print();
    h1.move(7, 0, 3, 1, 2);
    h1.print();

    // Or, even cleaner...
//    Hanoi h2(3,3);
//    h2.print();
//    h2.move(3,0,2,1);
//    h2.print();
    return 0;


}
