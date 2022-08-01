#include "Tokenizer.h"
#include "Parser.h"
#include "Token.h"
#include <iostream>
#include <fstream>

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

	for (JSONparser::Token token : tokens) {
		//token.Display();
	}

	parser.Parse(tokens);
	std::cout << parser.data.size() << std::endl;

	for (auto const& pair : parser.data) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}

	system("pause");

	return 0;
}