#include "utilities.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file> [output_file]" << std::endl;
        return 1;
    }

    char buff[500];
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Can't open input file" << std::endl;
        return 1;
    }

    std::ofstream outFile;
    if (argc == 3) {
        outFile.open(argv[2]);
        if (!outFile) {
            std::cout << "Can't open output file" << std::endl;
            return 1;
        }
    }
    std::ostream& out = (argc == 3) ? outFile : std::cout;

    while (input.getline(buff, 500)) {
        if (buff[0] == '\0') continue;
 
        int len = 0;
        while (buff[len] != '\0') ++len;
        if (len > 0 && buff[len - 1] == '\r') buff[len - 1] = '\0';

        String infix(buff);
        String result = infixToPostfix(infix);
        out << "Infix:  " << infix  << std::endl;
        out << "Postfix: " << result << std::endl;
        out << std::endl;
    }

    return 0;
}