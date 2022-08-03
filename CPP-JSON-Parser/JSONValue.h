#pragma once

#include <unordered_map>
#include <iostream>

namespace JSONparser {

	struct JSONValue {

		using JSONList = std::vector<JSONValue>;
		using JSONObject = std::unordered_map<std::string, JSONValue>;

		static enum DATA_TYPES {
			OBJECT, LIST, STRING, FLOAT, INT
		} data_types;

		union DATA {
			JSONObject* JSONObject;
			JSONList* JSONList;
			std::string* JSONString;
			float JSONFloat;
			int JSONInt;
		} mData;

		DATA_TYPES mDataType;
		size_t mCount;

		void SetObject(JSONObject* data);
		void SetList(JSONList* data);
		void SetString(std::string* data);
		void SetFloat(float& data);
		void SetInt(int& data);

		std::string asString();
		float asFloat();
		int asInt();

		JSONValue operator[](std::string key);
		JSONValue operator[](int index);

		void Display();
	};

	using JSONList = std::vector<JSONValue>;
	using JSONObject = std::unordered_map<std::string, JSONValue>;
}