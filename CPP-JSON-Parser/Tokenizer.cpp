#include "Tokenizer.h"

namespace JSONparser {
	std::vector<Token> Tokenizer::Tokenize(const std::string& inputJson) {
		Token currentToken;
		for (char currChar : inputJson) {
			switch (currChar) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (currentToken.mType == STRING) {
					currentToken.mText.append(1, currChar);
				}
				else if (currentToken.mType == POTENTIAL_FLOAT) {
					currentToken.mType = FLOAT;
					currentToken.mText.append(1, currChar);
				}
				else {
					currentToken.mType = INT;
					currentToken.mText.append(1, currChar);
				}
				break;
			case '.':
				if (currentToken.mType == STRING) {
					currentToken.mText.append(1, currChar);
				}
				else {
					currentToken.mType = POTENTIAL_FLOAT;
					currentToken.mText.append(1, currChar);
				}
				break;
			case '\"':
				if (currentToken.mType == STRING) {
					CloseToken(currentToken);
				}
				else {
					currentToken.mType = STRING;
				}
				break;
			case ',':
				if (currentToken.mType == INT || currentToken.mType == FLOAT) {
					CloseToken(currentToken);
				}
				break;
			case ':':
			case '{':
			case '}':
			case '[':
			case ']':
				CloseToken(currentToken);
				currentToken.mType = OPERATOR;
				currentToken.mText.append(1, currChar);
				CloseToken(currentToken);
				break;
			default:
				if (currentToken.mType != STRING) break;
				if (currentToken.mType == STRING) {
					currentToken.mText.append(1, currChar);
				}
			}
		}

		return mTokens;
	}

	void Tokenizer::CloseToken(Token& token) {
		if (token.mType == BLANK) return;
		mTokens.push_back(token);

		token.mType = BLANK;
		token.mText.erase();
	}
}