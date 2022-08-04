
# C++ JSON Parser

A simple JSON parser for C++    

I created this library as a tool for my inventory system project in order to retrieve JSON data  
from MongoDB and convert it back into the structure meant to hold said data in C++.

The library currently supports all JSON data types, however it expects valid JSON input. It does  
not care about new lines or blank spaces, however there cannot be any syntax errors.

I've made it as fast as possible in order to not hinder performance.  
# Usage

Given the following sample JSON input

```json
{
    "Inventory": [
        {
            "Name": "Pineapple",
            "ID": 10001,
            "Price": 1.99,
            "On Display": false,
            "Items": [
                {
                    "ID": 100001,
                    "Status": "Available",
                    "Created": "08/04/2022"
                }
            ]
        }
    ]
}
```

We can begin by parsing it into a format that C++ understands

```cpp
#include <JSONToken.h>
#include <JSONTokenizer.h>
#include <JSONValue.h>
#include <JSONParser.h>

#include <string>

using namespace JSONparser;

int main() {
    Parser jsonParser;

    std::string jsonData = "";

    JSONObject parsedData = jsonParser.Parse(jsonData);
}
```

The "Parse" function of the Parser class returns a JSONObject which can be indexed like a  
standard map using the [] operator. 

The member "Name" is inside an object which is in turn inside the "Inventory" list.  
To access "Name" we do the following:

```cpp
std::string name = parsedData["Inventory"][0]["Name"].asString();
```

Similar methods to "asString()" exist to retrieve other data types.

```cpp
int itemID = parsedData["Inventory"][0]["Items"][0]["ID"].asInt();
float price = parsedData["Inventory"][0]["Price"].asFloat();
bool onDisplay = parsedData["Inventory"][0]["On Display"].asBool();
```


## Documentation

Coming soon.

