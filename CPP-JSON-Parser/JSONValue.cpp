#include "JSONValue.h"

namespace JSONparser {
	void JSONValue::SetObject(JSONObject* data) {
		mDataType = OBJECT;
		mData.JSONObject = data;
		mCount = data->size();
	}

	void JSONValue::SetList(JSONList* data) {
		mDataType = LIST;
		mData.JSONList = data;
		mCount = data->size();
	}

	void JSONValue::SetString(std::string* data) {
		mDataType = STRING;
		mData.JSONString = data;
	}

	void JSONValue::SetFloat(float& data) {
		mDataType = FLOAT;
		mData.JSONFloat = data;
	}

	void JSONValue::SetInt(int& data) {
		mDataType = INT;
		mData.JSONInt = data;
	}

	std::string JSONValue::asString() {
		if (mDataType == STRING) return *mData.JSONString;
		throw std::logic_error("Unexpected type.");
	}

	float JSONValue::asFloat() {
		if (mDataType == FLOAT) return mData.JSONFloat;
		throw std::logic_error("Unexpected type.");
	}

	int JSONValue::asInt() {
		if (mDataType == INT) return mData.JSONInt;
		throw std::logic_error("Unexpected type.");
	}

	JSONValue JSONValue::operator[](std::string key) {
		if (mDataType == OBJECT) return (*mData.JSONObject)[key];
		throw std::logic_error("Unexpected type.");
	}

	JSONValue JSONValue::operator[](int index) {
		if (mDataType == LIST) return (*mData.JSONList)[index];
		throw std::logic_error("Unexpected type.");
	}
}