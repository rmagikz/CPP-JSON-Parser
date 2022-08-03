#include "Parser.h"
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

	JSONObject data1 = parser.Parse(inputStream);

	JSONValue int1 = data1["Inventory"][0]["Items"][0]["Last Counted"];

	system("pause");

	return 0;
}