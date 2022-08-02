#pragma once

#include "Token.h"
#include "JSONValue.h"

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <optional>
#include <unordered_map>

namespace JSONparser {
	class Parser {
	private:
		int i = 0;
	public:

		JSONObject* Parse(std::vector<Token>& tokens);

		std::vector<Token>::iterator mStart;
		std::vector<Token>::iterator mCurrent;
		std::vector<Token>::iterator mEnd;

		bool ExpectOperator(const char* token);
		bool ExpectString();
		bool ExpectNumber();
		bool ExpectKey();
		bool ExpectArray();
		bool ExpectObject();
		bool ExpectAssignment();
		void ParseAssignment(JSONObject& currentObject);
		JSONObject* ParseObject();
		JSONList* ParseArray();
	};
}