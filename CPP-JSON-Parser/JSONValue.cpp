#include "JSONValue.h"

namespace JSONparser {
	void JSONValue::SetObject(JSONObject* data) {
		mDataType = OBJECT;
		mData.JSONObject = data;
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

	void JSONValue::SetFloat(const float& data) {
		mDataType = FLOAT;
		mData.JSONFloat = data;
	}

	void JSONValue::SetInt(const int& data) {
		mDataType = INT;
		mData.JSONInt = data;
	}

	void JSONValue::SetBool(const bool& data) {
		mDataType = BOOL;
		mData.JSONBool = data;
	}

	void JSONValue::SetNULL() {
		mDataType = NULL_VALUE;
		mData.JSONNULL = NULL;
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

	bool JSONValue::asBool() {
		if (mDataType == BOOL) return mData.JSONBool;
		throw std::logic_error("Unexpected type.");
	}

	short JSONValue::asNULL() {
		if (mDataType == NULL_VALUE) return mData.JSONNULL;
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

	void JSONValue::Display() {
		std::cout << "MY TYPE IS " << mDataType << std::endl;
	}
}