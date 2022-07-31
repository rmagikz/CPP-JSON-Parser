#include "Tokenizer.h"
#include <iostream>
#include <fstream>

int main() {

	JSONparser::Tokenizer tokenizer;
	
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
		token.Display();
	}

	system("pause");

	return 0;
}