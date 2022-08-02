#include "Parser.h"
#include "Tokenizer.h"

namespace JSONparser {
	void Parser::Parse(std::vector<Token>& tokens) {
		mStart = tokens.begin();
		mCurrent = tokens.begin();
		mEnd = tokens.end();

		while (mCurrent < mEnd) {
			if (ExpectObject()) {
				ParseObject();
			}
			else if (ExpectArray()) {
				ParseArray();
			}
			else if (ExpectAssignment()) {
				mCurrent -= 3;
				std::string key = mCurrent->mText;
				mCurrent += 2;
				std::string value = mCurrent->mText;
				mCurrent++;
				std::cout << key << ": " << value << std::endl;
			}
			else {
				++mCurrent;
			}
		}
	}

	Token* Parser::ExpectOperator(const char* name) {
		if (mCurrent == mEnd) return NULL;
		if (mCurrent->mType != OPERATOR) return NULL;
		if (mCurrent->mText != name) return NULL;

		Token returnToken = *mCurrent;
		++mCurrent;
		return &returnToken;
	}

	Token* Parser::ExpectString() {
		if (mCurrent == mEnd) return NULL;
		if (mCurrent->mType != STRING) return NULL;

		Token returnToken = *mCurrent;
		++mCurrent;
		return &returnToken;
	}

	Token* Parser::ExpectNumber() {
		if (mCurrent == mEnd) return NULL;
		if (mCurrent->mType != INT && mCurrent->mType != FLOAT) return NULL;

		Token returnToken = *mCurrent;
		++mCurrent;
		return &returnToken;
	}

	Token* Parser::ExpectKey() {
		if (ExpectString() && ExpectOperator(":")) {
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		return NULL;
	}

	Token* Parser::ExpectAssignment() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && (ExpectNumber() || ExpectString())) {
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}

	Token* Parser::ExpectArray() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && ExpectOperator("[")) {
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}

	Token* Parser::ExpectObject() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectOperator("{") || (ExpectKey() && ExpectOperator("{"))) {
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}

	void Parser::ParseAssignment() {
		mCurrent -= 3;
		std::string key = mCurrent->mText;
		mCurrent += 2;
		std::string value = mCurrent->mText;
		mCurrent++;
		std::cout << key << ": " << value << std::endl;
	}

	void Parser::ParseObject() {
		std::cout << "{" << std::endl;
		while (mCurrent < mEnd) {
			if (ExpectOperator("}")) {
				std::cout << "}" << std::endl;
				break;
			}
			else if (ExpectObject()) {
				ParseObject();
			}
			else if (ExpectArray()) {
				ParseArray();
			}
			else if (ExpectAssignment()) {
				ParseAssignment();
			}
			else {
				++mCurrent;
			}
		}
	}

	void Parser::ParseArray() {
		mCurrent -= 3;
		std::cout << mCurrent->mText << ": [" << std::endl;
		mCurrent += 3;

		while (mCurrent < mEnd) {
			if (ExpectOperator("]")) {
				std::cout << "]" << std::endl;
				break;
			}
			else if (ExpectObject()) {
				ParseObject();
			}
			else if (ExpectArray()) {
				ParseArray();
			}
			else if (ExpectAssignment()) {
				ParseAssignment();
			}
			else {
				++mCurrent;
			}
		}
	}
}