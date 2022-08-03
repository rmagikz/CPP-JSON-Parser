#pragma once

#include <string>

namespace JSONparser {
	enum TOKEN_TYPES {
		BLANK,
		STRING,
		INT,
		POTENTIAL_FLOAT,
		FLOAT,
		OPERATOR,
	};

	class Token {
	public:
		TOKEN_TYPES mType;
		std::string mText;

		Token();
	};
}