#include <iostream>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"

int main() {
	std::string input;
	while (true) {
		std::cout << ">>> ";
		std::getline(std::cin, input);

		if (input == "exit") break;
		if (input.empty()) continue;

		try {
			Lexer lexer(input);
			std::vector<Token> tokens = lexer.tokenise();

			Parser parser(std::move(tokens));
			// Parser parser(tokens);
			std::unique_ptr<Node> root = parser.parse_expression();

			if (root) {
				std::cout << root->evaluate() << std::endl;
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return 0;
}
