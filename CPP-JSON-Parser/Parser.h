#pragma once

#include "Token.h"

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <optional>

namespace JSONparser {
	//static enum TYPES {
	//	STRING,
	//	ASSIGNMENT,
	//	ARRAY,
	//	OBJECT,
	//	KEY,
	//	INT,
	//	FLOAT
	//};

	class Parser {
	private:
		int i = 0;
	public:

		void Parse(std::vector<Token>& tokens);

		std::vector<Token>::iterator mCurrent;
		std::vector<Token>::iterator mEnd;

		Token* ExpectOperator(const char* token);
		Token* ExpectString();
		Token* ExpectNumber();
		Token* ExpectKey();
		Token* ExpectArray();
		Token* ExpectObject();
		Token* ExpectAssignment();
	};
}