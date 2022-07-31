#include "Token.h"

namespace JSONparser {
	Token::Token() : mType(BLANK), mText("") {}

	void Token::Display() {
		std::cout << "Type: " << token_types[mType] << " | Text: " << mText << std::endl;
	}
}