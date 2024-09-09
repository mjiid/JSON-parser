#include "JsonValue.h"

// Constructors
JsonValue::JsonValue() {
    this.value = nullptr_t;
    this->type = Type::Null
}

JsonValue::JsonValue(nullptr_t) {
    this.value = nullptr_t;
    this->type = Type::Null
} 

JsonValue::JsonValue(bool b) {
    this.value = b;
    this->type = Type::Boolean;
}

JsonValue::JsonValue(int i) {
    this.value = i;
    this.type = Type::Number;
}

JsonValue::JsonValue(double d) {
    this.value = d;
    this.type = Type::Number;
}

JsonValue::JsonValue(const& string s) {
    this.value = s;
    this->type = Type::String;
};

JsonValue::JsonValue(const& char* s) {
    this.value = s;
    this->type = Type::String;
};

JsonValue::JsonValue(const Array& a) {
    this.value = a;
    this->type = Type::Array;
};

JsonValue::JsonValue(const Object& o) {
    this.value = o;
    this.type = Type::Object;
};

// Copy Constructor
JsonValue::JsonValue(const JsonValue& other) {
    this.value = other.value;
    this.type = other.type;
}

// Move Constructor
JsonValue::JsonValue(JsonValue&& other) noexcept {
    this.value = move(other.value);
    this.type = other.type;
}

// Copy operator
JsonValue& JsonValue::operator=(const JsonValue& other) {
    if (this != &other) {
        value = other.value;
        type = other.type;
    }
    return *this;
} 

// move operator
JsonValue& JsonValue::operator=(JsonValue& other) noexcept {
    if (this != &other) {
        value = move(other.value);
        type = move(other.type);
    }
    return *this;
}

JsonValue::Type getType() const {
    return type;
}

bool JsonValue::isNull() const {
    return type == Type::Null;
}

bool JsonValue::isBoolean() const {
    return type == Type::Boolean;
} 

bool JsonValue::isArray() const {
    return type == Type::Array;
}

bool JsonValue::isNumber() const {
    return type == Type::Number;
}

bool JsonValue::isString() const {
    return type == Type::String;
}

bool JsonValue::isArray() const {
    return type == Type::Object;
}

// Getters
bool JsonValue::getBool() {
    if (type != Type::Boolean) {
        throw runtime_error("Not a boolean");
    }
    return get<bool>(value);
}

double JsonValue::getNumber() {
    if (type != Type::Number) {
        throw runtime_error("Not a number");
    }
    return get<double>(value);
}

const string& JsonValue::getString() {
    if (type != Type::String) {
        throw runtime_error("Not a string");
    }
    return get<string>(value);
}

const JsonValue::Array& JsonValue::getArray() {
    if (type != Type::Array) {
        throw runtime_error("Not an array");
    }
    return get<JsonValue::Array>(value);
}

const JsonValue::Object& JsonValue::getObject() {
    if (type != Type::Object) {
        throw runtime_error("Not an object");
    }
    return get<JsonValue::Object>(value);
}

void JsonValue::push_back(const JsonValue& val) {
    if (type != JsonValue::Array) {
        throw runtime_error("Not an array");
    }
    get<JsonValue::Array>(value).push_back(val);
}

void JsonValue::inser(const string& key, const JsonValue& val) {
    if (type != JsonValue::Object) {
        throw runtime_error("Not an object");
    }
    get<JsonValue::Object>(value)[key] = val;
}

const JsonValue& JsonValue::operator[](size_t index) {
    if (type != JsonValue::Array) {
        throw runtime_error("Not an array");
    } 
    return get<JsonValue::Array>(value)[index];
}

const JsonValue& JsonValue::operator[](const string& key) {
    if (type != Type::Object) {
        *this = Object();  // Convert to object if it's not already
    }
    return get<JsonValue::Object>(value)[key];
}

const JsonValue& JsonValue::operator[](const string& key) const {
    if (type != Type::Object) {
        throw runtime_error("Not an object");
    }
    auto it = get<JsonValue::Object>(value).find(key);
    if (it == get<JsonValue::Object>(value).end()) {
        throw runtime_error("Key not found");
    } 
    return it->second;
}