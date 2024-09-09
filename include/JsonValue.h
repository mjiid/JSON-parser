#pragma once

#include <vector>
#include <map>
#include <variant>

using namespace std;

class JsonValue {
public:
    enum class Type {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };

    using Array = vector<JsonValue>;
    using Object = map<JsonValue, JsonValue>;

private:
variant<nullptr_t, bool, double, string, Array, Object> value;
Type type;

public:
    // Constructors for different kinds of objects
    JsonValue();
    JsonValue(nullptr_t);
    JsonValue(bool b);
    JsonValue(int i);
    JsonValue(double d);
    JsonValue(const& string s);
    JsonValue(const& char* s);
    JsonValue(const Array& a);
    JsonValue(const Object& o);

    // A copy constructor
    JsonValue(const JsonValue& jsonValue)

    // A move contructor
    JsonValue(const JsonValue& JsonValue) noexcept;

    // Copy assignment operator
    JsonValue& operator = (const JsonValue &other);

    // A move operator
    JsonValue& operator = (const JsonValue &&other) noexcept;

    // Type checking
    Type getType() const;
    bool isNull() const;
    bool isBoolean() const;
    bool isInt() const;
    bool isDouble() const;
    bool isString() const;
    bool isArray() const; 
    bool isObject() const;

    // Value getters
    bool getBool() const;
    double getNumber() const;
    const string& getString() const;
    const Array& getArray() const;
    const Object& getObject() const;

    Array& getArray();
    Object& getObject();

    // ... c
    void push_back(const JsonValue& val);
    void insert(const string& key, const JsonValue& val);

    // ... Operators
    JsonValue& operator[](size_t index);
    const JsonValue& operator[](size_t index) const; // Read-only
    JsonValue& operator[](const std::string& key);
    const JsonValue& operator[](const std::string& key) const;
}