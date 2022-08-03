#pragma once

#include "Tokenizer.h"
#include "JSONValue.h"

namespace JSONparser {
	class Parser {
	private:
		Tokenizer mTokenizer;
		std::vector<JSONObject*> toDeleteObjects;
		std::vector<JSONList*> toDeleteLists;
	public:

		~Parser();

		JSONObject Parse(std::string inputString);

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
		void ParseObject(JSONObject& currentObject);
		void ParseArray(JSONList& currentArray);
	};
}