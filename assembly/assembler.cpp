#include "utilities.hpp"


int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Input file not found!" << std::endl;
    return 0;
  }

  std::ifstream infixFile(argv[1]);


	if (argc == 2){
    		String token;
    		String infix;

     while (!infixFile.eof()){
      	infixFile >> token;
      	if (token != ";") {
        	infix = infix + token + " ";
      }

      else {
		std::cout << "Infix: "    << infix << std::endl;
        		String postfix = infixToPostfix(infix);
		std::cout << "Postfix: "  << postfix << std::endl;
			postfixToAssembly(postfix);
        		infix = "";
      }

   	 }
}

	if(argc == 3){
    		std::ofstream postfixFile(argv[2]);
    		String token;
    		String infix;

    while(!infixFile.eof()){
      	infixFile >> token;

		if (token != ";") {
        	infix = infix + token + " ";
      }
      	else {
        		postfixFile << infix << std::endl;
        		String postfix = infixToPostfix(infix);
        		postfixFile << postfix << std::endl;
        		
			postfixToAssembly(postfix);
			infix = "";
     	 }

	postfixFile.close();
    }
    
	std::cout << "done" << std::endl;
    	infixFile.close();

    return 0;

  }
 

  

  return 0;
}