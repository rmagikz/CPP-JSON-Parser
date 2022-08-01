#pragma once

#include "Token.h"

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <optional>
#include <unordered_map>

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

		std::vector<Token>::iterator mStart;
		std::vector<Token>::iterator mCurrent;
		std::vector<Token>::iterator mEnd;

		std::unordered_map <std::string, std::string> data;

		Token* ExpectOperator(const char* token);
		Token* ExpectString();
		Token* ExpectNumber();
		Token* ExpectKey();
		Token* ExpectArray();
		Token* ExpectObject();
		Token* ExpectAssignment();
		void ParseAssignment();
		void ParseObject();
		void ParseArray();
	};

	class JSONKeyValuePair {
	public:
		std::string key;
		std::string value;
		
	};
}