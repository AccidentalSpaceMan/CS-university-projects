#include "string.hpp"
#include "salesentry.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>


int main(int argc, char *argv[]) {
    std::vector<String> option(4);
    option[0] = "all";
    option[1] = "total";
    option[2] = "link";
    option[3] = "ratings";
    if (argc != 3) {                                //3 things should be on the command line
        std::cerr << "Error" << std::endl;
        std::cerr << "Usage: " << argv[0] << " [ "
        << option[0] << " | "
        << option[1] << " | "
        << option[2] << " | "
        << option[3] << " ] sales_file" << std::endl;
        exit(1);                                     //Exit with error
    }

    std::ifstream in(argv[2]);                       //Open file
    if (!in) {                                       //Quit if open fails
        std::cerr << "Error: Can not open file: " << argv[2] << std::endl;
        exit(2);
    }
    std::vector<SalesEntry> sales = parse(in);   //Process the file
    in.close();

    if (option[0] == argv[1]) {                      //Handle the specified option
        outputAll(std::cout, sales);
    } else if (option[1] == argv[1]) {
        outputTotal(std::cout, sales);
    } else if (option[2] == argv[1]) {
        outputLink(std::cout, sales);
    } else if (option[3] == argv[1]) {
        outputRatings(std::cout, sales);
    } else {                                          //Error, bad option
        std::cerr << "Invalid option: " << argv[1] << std::endl;
        std::cerr << "Valid options: "
             << option[0] << " "
             << option[1] << " "
             << option[2] << " "
             << option[3] << std::endl;
        exit(3);
    }
    return 0;
}