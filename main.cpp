#include <iostream>
#include <cassert>
#include "Parser.h"

// Unit tests for the json parser

void testSimpleValues() {
    Parser parser("null");
    assert(parser.parse().isNull());

    parser = Parser("true");
    assert(parser.parse().getBool() == true);

    parser = Parser("false");
    assert(parser.parse().getBool() == false);

    parser = Parser("42");
    assert(parser.parse().getNumber() == 42);

    parser = Parser("3.14");
    assert(parser.parse().getNumber() == 3.14);

    parser = Parser("\"Hello, World!\"");
    assert(parser.parse().getString() == "Hello, World!");

    cout << "Simple value tests passed.\n";
}

void testArray() {
    Parser parser("[1, 2, 3, 4, 5]");
    JsonValue arr = parser.parse();
    assert(arr.isArray());
    assert(arr.getArray().size() == 5);
    assert(arr[0].getNumber() == 1);
    assert(arr[4].getNumber() == 5);

    cout << "Array test passed.\n";
}

void testObject() {
    Parser parser("{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}");
    JsonValue obj = parser.parse();
    assert(obj.isObject());
    assert(obj["name"].getString() == "John");
    assert(obj["age"].getNumber() == 30);
    assert(obj["city"].getString() == "New York");

    cout << "Object test passed.\n";
}

void testNestedStructure() {
    Parser parser(R"({
        "name": "John",
        "age": 30,
        "address": {
            "street": "123 Main St",
            "city": "New York"
        },
        "hobbies": ["reading", "cycling"]
    })");

    JsonValue obj = parser.parse();
    assert(obj.isObject());
    assert(obj["name"].getString() == "John");
    assert(obj["age"].getNumber() == 30);
    assert(obj["address"].isObject());
    assert(obj["address"]["street"].getString() == "123 Main St");
    assert(obj["address"]["city"].getString() == "New York");
    assert(obj["hobbies"].isArray());
    assert(obj["hobbies"][0].getString() == "reading");
    assert(obj["hobbies"][1].getString() == "cycling");

    cout << "Nested structure test passed.\n";
}

int main() {
    try {
        testSimpleValues();
        testArray();
        testObject();
        testNestedStructure();
        cout << "All tests passed successfully!\n";
    } catch (const exception& e) {
        cerr << "Test failed: " << e.what() << endl;
        return 1;
    }
    return 0;
}
