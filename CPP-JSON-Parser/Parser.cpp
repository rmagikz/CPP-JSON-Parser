#include "Parser.h"

namespace JSONparser {
	JSONObject Parser::Parse(std::string inputString) {
		mTokenizer.Tokenize(inputString);

		mCurrent = mTokenizer.mTokens.begin();
		mEnd = mTokenizer.mTokens.end();

		if (ExpectObject()) {
			JSONObject* finalObject = new JSONObject;
			toDeleteObjects.emplace_back(finalObject);
			ParseObject(*finalObject);
			return *finalObject;
		}
		else {
			throw std::exception("INVALID FORMAT");
		}
	}

	void Parser::ParseObject(JSONObject& currentObject) {
		while (mCurrent < mEnd) {
			if (ExpectOperator("}")) {
				break;
			}
			else if (ExpectObject()) {
				mCurrent -= 3;
				std::string key = mCurrent->mText;
				mCurrent += 3;
				JSONObject* newObject = new JSONObject;
				toDeleteObjects.emplace_back(newObject);
				ParseObject(*newObject);
				JSONValue value{};
				value.SetObject(newObject);
				currentObject.emplace(std::make_pair(key, value));
			}
			else if (ExpectArray()) {
				mCurrent -= 3;
				std::string key = mCurrent->mText;
				mCurrent += 3;
				JSONList* newArray = new JSONList;
				toDeleteLists.emplace_back(newArray);
				ParseArray(*newArray);
				JSONValue value{};
				value.SetList(newArray);
				currentObject.emplace(std::make_pair(key, value));
			}
			else if (ExpectAssignment(STRING)) {
				ParseString(currentObject);
			}
			else if (ExpectAssignment(INT)) {
				ParseInt(currentObject);
			}
			else if (ExpectAssignment(FLOAT)) {
				ParseFloat(currentObject);
			}
			else if (ExpectAssignment(BOOL)) {
				ParseBool(currentObject);
			}
			else {
				++mCurrent;
			}
		}
	}

	void Parser::ParseArray(JSONList& currentArray) {
		while (mCurrent < mEnd) {
			if (ExpectOperator("]")) {
				break;
			}
			else if (ExpectObject()) {
				JSONObject* newObject = new JSONObject;
				toDeleteObjects.emplace_back(newObject);
				ParseObject(*newObject);
				JSONValue value{};
				value.SetObject(newObject);
				currentArray.emplace_back(value);
			}
			else if (ExpectArray()) {
				JSONList* newArray = new JSONList;
				toDeleteLists.emplace_back(newArray);
				ParseArray(*newArray);
				JSONValue value{};
				value.SetList(newArray);
				currentArray.emplace_back(value);
			}
			else {
				++mCurrent;
			}
		}
	}

	void Parser::ParseInt(JSONObject& currentObject) {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		JSONValue value{};
		value.SetInt(std::stoi(mCurrent->mText));
		mCurrent++;
		currentObject.emplace(std::make_pair(key, value));
	}

	void Parser::ParseFloat(JSONObject& currentObject) {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		JSONValue value{};
		value.SetFloat(std::stof(mCurrent->mText));
		mCurrent++;
		currentObject.emplace(std::make_pair(key, value));
	}

	void Parser::ParseBool(JSONObject& currentObject) {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		JSONValue value{};
		value.SetBool(mCurrent->mText != "0");
		mCurrent++;
		currentObject.emplace(std::make_pair(key, value));
	}

	void Parser::ParseString(JSONObject& currentObject) {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		JSONValue value{};
		value.SetString(&(mCurrent->mText));
		mCurrent++;
		currentObject.emplace(std::make_pair(key, value));
	}

	bool Parser::ExpectAssignment(const TOKEN_TYPES& type) {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && ExpectType(type)) {
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

	bool Parser::ExpectKey() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectType(STRING) && ExpectOperator(":")) {
			return true;
		}
		mCurrent = start;
		return false;
	}

	bool Parser::ExpectOperator(const char* name) {
		if (mCurrent == mEnd) return false;
		if (mCurrent->mType != OPERATOR) return false;
		if (mCurrent->mText != name) return false;

		++mCurrent;
		return true;
	}

	bool Parser::ExpectType(const TOKEN_TYPES& type) {
		if (mCurrent == mEnd) return false;
		if (mCurrent->mType != type) return false;

		++mCurrent;
		return true;
	}

	Parser::~Parser() {
		for (int i = 0; i < toDeleteObjects.size(); i++) {
			delete(toDeleteObjects[i]);
		}

		for (int i = 0; i < toDeleteLists.size(); i++) {
			delete(toDeleteLists[i]);
		}
	}
}