#include "JSONValue.h"

namespace JSONparser {
	void JSONValue::SetObject(std::unordered_map<std::string, JSONValue>& data) {
		mDataType = OBJECT;
		mData.JSONObject = &data;
	}

	void JSONValue::SetList(std::vector<JSONValue>& data) {
		mDataType = LIST;
		mData.JSONList = &data;
	}

	void JSONValue::SetString(std::string& data) {
		mDataType = STRING;
		mData.JSONString = &data;
	}

	void JSONValue::SetFloat(float& data) {
		mDataType = FLOAT;
		mData.JSONFloat = data;
	}

	void JSONValue::SetInt(int& data) {
		mDataType = INT;
		mData.JSONInt = data;
	}

	std::unordered_map<std::string, JSONValue> JSONValue::GetObject() {
		if (mDataType == OBJECT) return *mData.JSONObject;
	}

	std::vector<JSONValue> JSONValue::GetList() {
		if (mDataType == LIST) return *mData.JSONList;
	}

	std::string JSONValue::GetString() {
		if (mDataType == STRING) return *mData.JSONString;
	}

	float JSONValue::GetFloat() {
		if (mDataType == FLOAT) return mData.JSONFloat;
	}

	int JSONValue::GetInt() {
		if (mDataType == INT) return mData.JSONInt;
	}
}