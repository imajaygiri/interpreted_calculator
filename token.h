#include <string>
#include "types.h"

/*
	*@brief defines Token types
	* Use this when returning tokens , it contains value and types
	* type is enum
	*
	NUMBER, PLUS, MINUS, SLASH, STAR, PERCENT, LPAREN, RPAREN,
	EOF_TOKEN */
struct Token {
	/// token types
	/// NUMBER, PLUS, MINUS, SLASH, STAR, PERCENT, LPAREN, RPAREN,EOF_TOKEN
	TokenType type;
	/// value of tokens eg 12 ,34.4
    /// use only if token type is number
	std::string value;
};
