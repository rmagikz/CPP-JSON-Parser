#include "Tokenizer.h"
#include "Parser.h"
#include "Token.h"
#include "JSONValue.h"
#include <iostream>
#include <fstream>

using namespace JSONparser;

int main() {

	JSONparser::Tokenizer tokenizer;
	JSONparser::Parser parser;
	
	std::fstream inputFile;
	std::string inputStream;
	inputFile.open("SampleJSON.json", std::ios::in);
	while (!inputFile.eof()) {
		char c;
		inputFile.get(c);
		inputStream.append(1, c);
	}

	std::vector<JSONparser::Token> tokens = tokenizer.Tokenize(inputStream);

	JSONObject data = *parser.Parse(tokens);

	system("pause");

	return 0;
}