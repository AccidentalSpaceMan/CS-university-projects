#include "string.hpp"
#include <cassert>

String::String() {
    stringSize = 1;
    str = new char[1];
    str[0] = 0;
}

String::String(char ch) {
     if (ch == 0) {
        stringSize = 1;
        str = new char[1];
        str[0] = 0;
    } else {
        stringSize = 2;
        str = new char[2];
        str[0] = ch;
        str[1] = 0;
    }
}

String::String(const char s[]) {
    int len = 0;
    while (s[len] != 0) ++len;

    stringSize = len + 1;
    str = new char[stringSize];

    for (int i = 0; i < len; ++i)
        str[i] = s[i];

    str[len] = 0;
}

String::String(const String& other) {
    stringSize = other.stringSize;
    str = new char[stringSize];

    for (int i = 0; i < stringSize; ++i)
        str[i] = other.str[i];
}

String::~String() {
    delete[] str;
}

void String::swap(String& other) {
    char* tempStr = str;
    str = other.str;
    other.str = tempStr;

    int tempSize = stringSize;
    stringSize = other.stringSize;
    other.stringSize = tempSize;
}

String& String::operator=(String rhs) {
    swap(rhs);
    return *this;
}

int String::capacity() const {
    return stringSize - 1;
}

int String::length() const {
    return stringSize - 1;
}

char& String::operator[](int index) {
    assert(index >= 0 && index < stringSize);
    return str[index];
}

char String::operator[](int index) const {
    assert(index >= 0 && index < stringSize);
    return str[index];
}

String& String::operator+=(const String& rhs) {
    int newLen = length() + rhs.length();
    char* newStr = new char[newLen + 1];

    for (int i = 0; i < length(); ++i)
        newStr[i] = str[i];

    for (int i = 0; i < rhs.length(); ++i)
        newStr[length() + i] = rhs.str[i];

    newStr[newLen] = 0;

    delete[] str;
    str = newStr;
    stringSize = newLen + 1;

    return *this;
}

String operator+(String lhs, const String& rhs) {
    lhs += rhs;
    return lhs;
}

bool String::operator==(const String& rhs) const {
    if (length() != rhs.length()) return false;

    for (int i = 0; i < length(); ++i)
        if (str[i] != rhs.str[i])
            return false;

    return true;
}

bool operator==(const char lhs[], const String& rhs) {
    return String(lhs) == rhs;
}

bool operator==(char lhs, const String& rhs) {
    return String(lhs) == rhs;
}

bool String::operator<(const String& rhs) const {
    int i = 0;

    while (str[i] != 0 && rhs.str[i] != 0 && str[i] == rhs.str[i])
        ++i;

    if (str[i] == 0 && rhs.str[i] == 0) return false;
    if (str[i] == 0) return true;
    if (rhs.str[i] == 0) return false;

    return str[i] < rhs.str[i];
}

bool operator<(const char lhs[], const String& rhs) {
    return String(lhs) < rhs;
}

bool operator<(char lhs, const String& rhs) {
    return String(lhs) < rhs;
}

bool operator<=(const String& lhs, const String& rhs) {
    return !(rhs < lhs);
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}

bool operator>(const String& lhs, const String& rhs) {
    return rhs < lhs;
}

String String::substr(int start, int end) const {
    if (start < 0) start = 0;
    if (start >= length()) return String();

    if (end >= length()) end = length() - 1;
    if (end < start) return String();

    int newLen = end - start + 1;

    String result;
    delete[] result.str;

    result.stringSize = newLen + 1;
    result.str = new char[newLen + 1];

    for (int i = 0; i < newLen; ++i) {
        result.str[i] = str[start + i];
    }

    result.str[newLen] = 0;

    return result;
}

int String::findch(int start, char ch) const {
    for (int i = start; i < length(); ++i)
        if (str[i] == ch)
            return i;

    return -1;
}

int String::findstr(int start, const String& s) const {
    if (s.length() == 0) return start;

    for (int i = start; i <= length() - s.length(); ++i) {
        bool match = true;

        for (int j = 0; j < s.length(); ++j) {
            if (str[i + j] != s.str[j]) {
                match = false;
                break;
            }
        }

        if (match) return i;
    }

    return -1;
}

std::ostream& operator<<(std::ostream& out, const String& rhs) {
    out << rhs.str;
    return out;
}

std::istream& operator>>(std::istream& in, String& rhs) {
    char buffer[1024];
    in >> buffer;
    rhs = String(buffer);
    return in;
}

std::vector<String> String::split(char ch) const {
    std::vector<String> result;
    int start = 0;
    do{
        int end = findch(start, ch);
        if (end == -1) end = length();
        result.push_back(substr(start, end - 1));
        start = end + 1;
    }   while (start <= length());
    return result;
}