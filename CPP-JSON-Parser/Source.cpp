#include "Tokenizer.h"
#include "Parser.h"
#include "Token.h"
#include "JSONValue.h"
#include <iostream>
#include <fstream>

using namespace JSONparser;

int main() {

	Tokenizer tokenizer;
	Parser parser;
	
	std::fstream inputFile;
	std::string inputStream;
	inputFile.open("SampleJSON.json", std::ios::in);
	while (!inputFile.eof()) {
		char c;
		inputFile.get(c);
		inputStream.append(1, c);
	}

	std::vector<Token> tokens = tokenizer.Tokenize(inputStream);
	JSONObject data = *parser.Parse(tokens);

	std::string inv = data["root"].GetObject()["Inventory"].GetList()[0].GetObject()["Name"].GetString();

	std::string inv1 = data["root"]["Inventory"][0]["Name"].GetString();

	std::cout << inv << std::endl;
	std::cout << inv1 << std::endl;

	system("pause");

	return 0;
}