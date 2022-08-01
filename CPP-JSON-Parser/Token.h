#pragma once

#include <string>
#include <iostream>

namespace JSONparser {
	enum TOKEN_TYPES {
		BLANK,
		STRING,
		INT,
		POTENTIAL_FLOAT,
		FLOAT,
		OPERATOR,
		UNKNOWN
	};

	static const char* token_types[] = {
			"BLANK",
			"STRING",
			"INT",
			"POTENTIAL_FLOAT",
			"FLOAT",
			"OPERATOR",
			"UNKNOWN"
	};


	class Token {
	public:
		TOKEN_TYPES mType;
		std::string mText;

		Token();
		Token(TOKEN_TYPES& type, const std::string& text);

		void Display();
	};
}