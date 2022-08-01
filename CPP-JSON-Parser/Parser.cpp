#include "Parser.h"

namespace JSONparser {
	void Parser::Parse(std::vector<Token>& tokens) {
		mCurrent = tokens.begin();
		mEnd = tokens.end();
		int a = 0;
		int b = 0;
		while (mCurrent != mEnd) {
			if (ExpectAssignment()) {
				a++;
			}
			else if (ExpectArray()) {
				b++;
			}
			else {
				++mCurrent;
			}
		}
		std::cout << a << std::endl;
		std::cout << b << std::endl;
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
			std::cout << "Found assignment" << std::endl;
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}

	Token* Parser::ExpectArray() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && ExpectOperator("[")) {
			std::cout << "Found array" << std::endl;
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}

	Token* Parser::ExpectObject() {
		std::vector<Token>::iterator start = mCurrent;
		if (ExpectKey() && ExpectOperator("{")) {
			std::cout << "Found object" << std::endl;
			Token returnToken = *mCurrent;
			return &returnToken;
		}
		mCurrent = start;
		return NULL;
	}
}