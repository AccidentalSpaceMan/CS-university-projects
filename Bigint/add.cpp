#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bigint.hpp"

int main(){
    std::ifstream in;
    in.open("data1-1.txt");
    if (!in){
        std::cerr << "File not found: data1-1.txt" << std::endl;
        exit(1);
    }

    Bigint bi1(90000);
    Bigint bi2(300);
    Bigint bi3(300);
    Bigint bi4(300);

    while(!in.eof()){

        std::cout << bi1 << std::endl;
        std::cout << bi2 << std::endl;

        Bigint result = bi1 + bi2;

        std::cout << result << std::endl;

        std::cout << "\n";

        std::cout << bi3 << std::endl;
        std::cout << bi4 << std::endl;

        Bigint result2 = bi3 + bi4;

        std::cout << result2 << std::endl;

        break;

    }

    in.close();
    return 0;
}