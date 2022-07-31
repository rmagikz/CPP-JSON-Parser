#pragma once

#include "Token.h""

#include <string>
#include <iostream>
#include <vector>

namespace JSONparser {
	class Tokenizer {
	private:

	public:
		std::vector<Token> Tokenize(const std::string& inputJson);
	};
}