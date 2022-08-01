#include "Token.h"

namespace JSONparser {
	Token::Token(TOKEN_TYPES& type, const std::string& text) : mType(type), mText(text) {}
	Token::Token() : mType(BLANK), mText("") {};

	void Token::Display() {
		std::cout << "Type: " << token_types[mType] << " | Text: " << mText << std::endl;
	}
}