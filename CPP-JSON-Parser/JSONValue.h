#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>

namespace JSONparser {
	struct JSONValue {
		static enum DATA_TYPE {
			OBJECT, LIST, STRING, FLOAT, INT
		};

		union DATA {
			std::unordered_map<std::string, JSONValue>* JSONObject;
			std::vector<JSONValue>* JSONList;
			std::string* JSONString;
			float JSONFloat;
			int JSONInt;
		} mData;

		DATA_TYPE mDataType;

		void SetObject(std::unordered_map<std::string, JSONValue>& data);
		void SetList(std::vector<JSONValue>& data);
		void SetString(std::string& data);
		void SetFloat(float& data);
		void SetInt(int& data);

		std::unordered_map<std::string, JSONValue> GetObject();
		std::vector<JSONValue> GetList();
		std::string GetString();
		float GetFloat();
		int GetInt();
	};
}