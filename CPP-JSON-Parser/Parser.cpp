#include "Parser.h";

namespace JSONparser {
	JSONObject* Parser::Parse(std::vector<Token>& tokens) {
		mStart = tokens.begin();
		mCurrent = tokens.begin();
		mEnd = tokens.end();

		JSONObject* finalObject = new JSONObject;

		if (ExpectObject()) {
			JSONObject* object = ParseObject();
			JSONValue value;
			value.SetObject(object);
			finalObject->emplace(std::make_pair("root", value));
		}
		
		return finalObject;
	}

	bool Parser::ExpectOperator(const char* name) {
		if (mCurrent == mEnd) return false;
		if (mCurrent->mType != OPERATOR) return false;
		if (mCurrent->mText != name) return false;

		++mCurrent;
		return true;
	}

	bool Parser::ExpectString() {
		if (mCurrent == mEnd) return false;
		if (mCurrent->mType != STRING) return false;

		++mCurrent;
		return true;
	}

	bool Parser::ExpectNumber() {
		if (mCurrent == mEnd) return false;
		if (mCurrent->mType != INT && mCurrent->mType != FLOAT) return false;

		++mCurrent;
		return true;
	}

	bool Parser::ExpectKey() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectString() && ExpectOperator(":")) {
			return true;
		}
		mCurrent = start;
		return false;
	}

	bool Parser::ExpectAssignment() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && (ExpectNumber() || ExpectString())) {
			return true;
		}
		mCurrent = start;
		return false;
	}

	bool Parser::ExpectArray() {
		std::vector<Token>::iterator start = mCurrent;
		if ((ExpectKey() && ExpectOperator("[")) || ExpectOperator("[")) {
			return true;
		}
		mCurrent = start;
		return false;
	}

	bool Parser::ExpectObject() {
		std::vector<Token>::iterator start = mCurrent;
		if ((ExpectKey() && ExpectOperator("{")) || ExpectOperator("{")) {
			return true;
		}
		mCurrent = start;
		return false;
	}

	void Parser::ParseAssignment(JSONObject& currentObject) {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		JSONValue value;
		value.SetString(&(mCurrent->mText));
		mCurrent++;
		currentObject.emplace(std::make_pair(key, value));
	}

	JSONObject* Parser::ParseObject() {
		JSONObject* currentObject = new JSONObject;

		while (mCurrent < mEnd) {
			if (ExpectOperator("}")) {
				break;
			}
			else if (ExpectObject()) {
				mCurrent -= 3;
				std::string key = mCurrent->mText;
				mCurrent += 3;
				JSONObject* newObject = ParseObject();
				JSONValue value;
				value.SetObject(newObject);
				currentObject->emplace(std::make_pair(key, value));
				//delete(newObject);
			}
			else if (ExpectArray()) {
				mCurrent -= 3;
				std::string key = mCurrent->mText;
				mCurrent += 3;
				JSONList* newArray = ParseArray();
				JSONValue value;
				value.SetList(newArray);
				currentObject->emplace(std::make_pair(key, value));
				//delete(newArray);
			}
			else if (ExpectAssignment()) {
				ParseAssignment(*currentObject);
			}
			else {
				++mCurrent;
			}
		}
		return currentObject;
	}

	JSONList* Parser::ParseArray() {
		JSONList* currentArray = new JSONList;
		int bracketCount = 0;

		while (mCurrent < mEnd) {
			if (ExpectOperator("]")) {
				break;
			}
			else if (ExpectObject()) {
				JSONObject* newObject = ParseObject();
				JSONValue value;
				value.SetObject(newObject);
				currentArray->emplace_back(value);
				//delete(newObject);
			}
			else if (ExpectArray()) {
				JSONList* newArray = ParseArray();
				JSONValue value;
				value.SetList(newArray);
				currentArray->emplace_back(value);
				//delete(newArray);
			}
			else {
				++mCurrent;
			}
		}
		return currentArray;
	}
}