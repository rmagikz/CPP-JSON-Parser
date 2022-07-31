#pragma once

#include "Token.h"

#include <string>
#include <iostream>
#include <vector>

namespace JSONparser {
	class Tokenizer {
	private:
		std::vector<Token> mTokens;
	public:
		std::vector<Token> Tokenize(const std::string& inputJson);

		void CloseToken(Token& token);
	};
}