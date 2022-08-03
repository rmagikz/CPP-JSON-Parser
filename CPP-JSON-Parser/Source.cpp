#include "Tokenizer.h"
#include "Parser.h"
#include "Token.h"
#include "JSONValue.h"
#include <iostream>
#include <fstream>

using namespace JSONparser;

struct Item {
	std::string id;
	std::string status;
	std::string lastcounted;

	Item(std::string& _id, std::string& _status, std::string& _lastcounted) : id(_id), status(_status), lastcounted(_lastcounted) {}
};

struct Category {
	std::string name;
	std::string id;
	std::string cost;
	std::vector<Item> items;

	Category(std::string& _name, std::string& _id, std::string& _cost) : name(_name), id(_id), cost(_cost) {}

	void AddItem(Item& item) {
		items.emplace_back(item);
	}

	void display() {
		std::cout << "NAME: " << name << " | ID: " << id << " | Cost: " << cost << std::endl;
		for (int i = 0; i < items.size(); i++) {
			std::cout << "\t ID: " << items[i].id << " | Status: " << items[i].status << " | Last Counted: " << items[i].lastcounted << std::endl;
		}
		std::cout << std::endl;
	}
};

std::vector<Category> CreateCategories(JSONValue& root) {
	std::vector<Category> Categories;

	JSONValue cats = root["Inventory"];

	for (int i = 0; i < cats.mCount; i++) {
		std::string name = root["Inventory"][i]["Name"].asString();
		std::string id = root["Inventory"][i]["ID"].asString();
		std::string cost = root["Inventory"][i]["Cost"].asString();

		Category cat1{ name,id,cost };

		JSONValue items = root["Inventory"][i]["Items"];

		for (int j = 0; j < items.mCount; j++) {
			std::string iid = root["Inventory"][i]["Items"][j]["ID"].asString();
			std::string istatus = root["Inventory"][i]["Items"][j]["Status"].asString();
			std::string ilastcounted = root["Inventory"][i]["Items"][j]["Last Counted"].asString();

			Item item{ iid,istatus,ilastcounted };
			cat1.AddItem(item);
		}

		Categories.emplace_back(cat1);
	}

	return Categories;
}

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

	std::vector<Category> inventoryList = CreateCategories(data["root"]);

	for (int i = 0; i < inventoryList.size(); i++) {
		inventoryList[i].display();
	}

	system("pause");

	return 0;
}