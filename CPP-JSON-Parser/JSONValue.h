#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>

namespace JSONparser {

	struct JSONValue {

		using JSONList = std::vector<JSONValue>;
		using JSONObject = std::unordered_map<std::string, JSONValue>;

		static enum DATA_TYPES {
			NOTHING, OBJECT, LIST, STRING, FLOAT, INT
		} data_types;

		union DATA {
			JSONObject* JSONObject;
			JSONList* JSONList;
			std::string* JSONString;
			float JSONFloat;
			int JSONInt;
		} mData;

		bool isSet;

		DATA_TYPES mDataType;

		void SetObject(JSONObject* data);
		void SetList(JSONList* data);
		void SetString(std::string* data);
		void SetFloat(float& data);
		void SetInt(int& data);

		JSONObject GetObject();
		JSONList GetList();
		std::string GetString();
		float GetFloat();
		int GetInt();

		void Display();
	};

	using JSONList = std::vector<JSONValue>;
	using JSONObject = std::unordered_map<std::string, JSONValue>;
}