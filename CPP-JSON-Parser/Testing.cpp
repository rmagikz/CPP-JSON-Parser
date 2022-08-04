#include "JSONParser.h"
#include <fstream>

using namespace JSONparser;

int main() {
	Parser parser;

	std::fstream inputFile;
	std::string inputStream;
	inputFile.open("SampleJSON.json", std::ios::in);
	while (!inputFile.eof()) {
		char c;
		inputFile.get(c);
		inputStream.append(1, c);
	}
	inputFile.close();

	//JSONObject data1 = parser.Parse(inputStream);

	Tokenizer tokenizer;
	std::vector<Token> tokens = tokenizer.Tokenize(inputStream);

	for (int i = 0; i < tokens.size(); i++) {
		tokens[i].display();
	}

	system("pause");

	return 0;
}