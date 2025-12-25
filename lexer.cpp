#include "lexer.h"

#include <iostream>
#include <stdexcept>
using namespace std;
Lexer::Lexer(const string& input) : src(input) {}
vector<Token> Lexer::tokenise() {
	vector<Token> tokens;
	while (!is_at_end()) {
		char c = peek();
		if (isspace(c)) {
			advance();
		} else if (isdigit(c) || c == '.') {
			tokens.push_back(number());
		} else {
			tokens.push_back(op_or_paren());
		}
	}
	tokens.push_back({TokenType::EOF_TOKEN, ""});
	return tokens;
}

Token Lexer::number() {
	string buf;
	bool has_dot = false;

	while (!is_at_end()) {
		char c = peek();
		if (isdigit(c)) {
			buf += c;
		} else if (c == '.') {
			if (has_dot) break;
			buf += c;
			has_dot = true;
		} else {
			break;
		}
		advance();
	}
	return {TokenType::NUMBER, buf};
}

Token Lexer::op_or_paren() {
	char c = advance();
	switch (c) {
		case '+':
			return {TokenType::PLUS, ""};
		case '-':
			return {TokenType::MINUS, ""};
		case '*':
			return {TokenType::STAR, ""};
		case '/':
			return {TokenType::SLASH, ""};
		case '%':
			return {TokenType::PERCENT, ""};
		case '(':
			return {TokenType::LPAREN, ""};
		case ')':
			return {TokenType::RPAREN, ""};
		default:
			throw runtime_error("illegal character");
	}
}

char Lexer::peek() { return src[pos]; }
char Lexer::advance() { return src[pos++]; }
bool Lexer::is_at_end() { return pos >= src.size(); }
void Lexer::print(vector<Token> tokens) {
	for (auto token : tokens) {
		switch (token.type) {
			case TokenType::NUMBER:
				cout << "[TokenType: NUMBER ," << "value: " << token.value
					 << "]" << endl;
				break;
			case TokenType::MINUS:
				cout << "[TokenType: MINUS ,"
					 << "value: " << token.value << " ]" << endl;
				break;
			case TokenType::PERCENT:
				cout << "PERCENT" << endl;
				break;
			case TokenType::PLUS:
				cout << "PLUS" << endl;
				break;
			case TokenType::LPAREN:
				cout << "LPAREN" << endl;
				break;
			case TokenType::RPAREN:
				cout << "RPAREN" << endl;
				break;
			case TokenType::SLASH:
				cout << "SLASH" << endl;
				break;
			case TokenType::STAR:
				cout << "STAR" << endl;
				break;
			case TokenType::EOF_TOKEN:
				cout << "EOF" << endl;
				break;
			default:
				cout << "nothing matched" << endl;
				break;
		}
	}
}
