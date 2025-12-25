#pragma once
#include <memory>
#include <vector>

#include "ast.h"
#include "lexer.h"

class Parser {
	std::vector<Token> tokens;
	size_t pos = 0;

   private:
	Token advance() { return tokens[pos++]; }
	Token peek() { return tokens[pos]; }

	int get_precedence(TokenType type) {
		switch (type) {
			case TokenType::PLUS:
			case TokenType::MINUS:
				return 10;
			case TokenType::STAR:
			case TokenType::SLASH:
			case TokenType::PERCENT:
				return 20;
			default:
				return 0;
		}
	}

	char get_char_from_token(Token t) {
		if (t.type == TokenType::PLUS) return '+';
		if (t.type == TokenType::MINUS) return '-';
		if (t.type == TokenType::STAR) return '*';
		if (t.type == TokenType::SLASH) return '/';
		if (t.type == TokenType::PERCENT) return '%';
		return '?';
	}

   public:
	Parser(std::vector<Token> t) : tokens(std::move(t)) {};
	std::unique_ptr<Node> parse_expression(int precedence = 0) {
		Token token = advance();
		std::unique_ptr<Node> left;

		// handles number
		if (token.type == TokenType::NUMBER) {
			left = std::make_unique<NumberNode>(std::stod(token.value));

		} else if (token.type == TokenType::LPAREN) {
			// handles parenthesis
			left = parse_expression(0);	 // start fresh
			advance();					 // cosumes Rparen
		}
		while (get_precedence(peek().type) > precedence) {
			Token op_token = advance();
			int op_precendence = get_precedence(op_token.type);
			std::unique_ptr<Node> right = parse_expression(op_precendence);

			left = std::make_unique<BinaryOpNode>(get_char_from_token(op_token),
												  std::move(left),
												  std::move(right));
		}
		return left;
	}
};
