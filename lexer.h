#include <string>
#include <vector>

#include "token.h"
#pragma once
using std::string;
using std::vector;
/*

	*@brief lexer , it contains methods lexing
	*/

class Lexer {
	/// src , contains string to be lexing eg 123.3 + 34 * (343+39) etc
	string src;
	/// points to src char by char starts from zero left -> right
	size_t pos = 0;

   private:
	/// used internally for converting char to number
	Token number();
	///  used internally to conver char to op or parenthesis eg lparen or rparen
	///  ( or ) and * , / , + ,-
	Token op_or_paren();
	/// returns char to be checked
	char peek();
	/// shift pos , pointer to src string by one
	char advance();
	/// checks if input is ended or not by pos >= sec.size()
	bool is_at_end();

	/// takes src  eg 123.3 + 34 * (343+39) etc

   public:
	Lexer(const string& input);
	/// returns Vector<Token> containng value and types
	vector<Token> tokenise();
    /// prints tokens
	void print(vector<Token> tokens);
};
