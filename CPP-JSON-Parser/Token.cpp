#include "Token.h"

namespace JSONparser {
	Token::Token() : mType(BLANK), mText("") {};

	void Token::display() {
		std::cout << "TYPE: " << mType << " | TEXT: " << mText << std::endl;
	}
}