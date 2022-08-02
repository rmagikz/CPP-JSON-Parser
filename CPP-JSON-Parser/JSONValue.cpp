#include "JSONValue.h"

namespace JSONparser {
	void JSONValue::SetObject(JSONObject* data) {
		mDataType = OBJECT;
		mData.JSONObject = data;
		isSet = true;
	}

	void JSONValue::SetList(JSONList* data) {
		mDataType = LIST;
		mData.JSONList = data;
		isSet = true;
	}

	void JSONValue::SetString(std::string* data) {
		mDataType = STRING;
		mData.JSONString = data;
		isSet = true;
	}

	void JSONValue::SetFloat(float& data) {
		mDataType = FLOAT;
		mData.JSONFloat = data;
		isSet = true;
	}

	void JSONValue::SetInt(int& data) {
		mDataType = INT;
		mData.JSONInt = data;
		isSet = true;
	}

	JSONObject JSONValue::GetObject() {
		if (mDataType == OBJECT) return *mData.JSONObject;
	}

	JSONList JSONValue::GetList() {
		if (mDataType == LIST) return *mData.JSONList;
	}

	std::string JSONValue::GetString() {
		if (mDataType == STRING) return *mData.JSONString;
		return 0;
	}

	float JSONValue::GetFloat() {
		if (mDataType == FLOAT) return mData.JSONFloat;
		return 0;
	}

	int JSONValue::GetInt() {
		if (mDataType == INT) return mData.JSONInt;
		return 0;
	}

	void JSONValue::Display() {
		std::cout << "MY TYPE IS: " << mDataType << std::endl;
	}
}