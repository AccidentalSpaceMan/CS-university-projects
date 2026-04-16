#include <iostream>
#include "bigint.hpp"


Bigint::Bigint() {
    for (int i = 0; i < CAPACITY; ++i) {
        digits[i] = 0;
    }
}

Bigint::Bigint(int value) {
    for (int i = 0; i < CAPACITY; ++i) {
        digits[i] = 0;
    }

    int pos = 0;
    while (value > 0 && pos < CAPACITY) {
        digits[pos] = value % 10;
        value /= 10;
        ++pos;
    }
}

Bigint::Bigint(const char str[]) {
    for (int i = 0; i < CAPACITY; ++i) {
        digits[i] = 0;
    }

    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }

    for (int i = 0; i < len && i < CAPACITY; ++i) {
        digits[i] = str[len - 1 - i] - '0';
    }
}

void Bigint::debugPrint(std::ostream& out) const {
    for (int i = CAPACITY - 1; i >= 0; --i) {
        out << digits[i];
        if (i != 0) out << "|";
    }
}

bool Bigint::operator==(const Bigint& rhs) const {
    for (int i = 0; i < CAPACITY; ++i) {
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Bigint& b) {
    int start = CAPACITY - 1;

    while (start > 0 && b.digits[start] == 0) {
        --start;
    }

    int count = 0;
    for (int i = start; i >= 0; --i) {
        out << b.digits[i];
        ++count;

        if (count == 100 && i != 0) {
            out << '\n';
            count = 0;
        }
    }

    return out;
}

std::istream& operator>>(std::istream& in, Bigint& rhs){
    for(int i = 0; i < CAPACITY; ++i){
        rhs.digits[i] = 0;
    }

    char temp[CAPACITY];
    char ch;
    int count = 0;

    while(in.get(ch)){
        if (ch == ';'){
            break;
        }
        if (ch >= 0 && ch <= 9){
            if (count < CAPACITY){
                temp[count] = ch;
                ++count;
            }
        }
    }
    for(int i = 0; i < count; ++i){
        rhs.digits[i] = temp[count - 1 - i] - '0';
    }
    return in;
}

Bigint Bigint::operator+(const Bigint& rhs) const {
    Bigint result;
    int carry = 0;

    for(int i = 0; i < CAPACITY; ++i){
        int sum = digits[i] + rhs.digits[i] + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    return result;
}

bool operator==(const Bigint& lhs, int rhs){
    return lhs == Bigint(rhs);
}

bool operator==(int lhs, Bigint& rhs){
    return Bigint(lhs) == rhs;
}

bool operator==(const Bigint& lhs, const char rhs[]){
    return lhs == Bigint(rhs);
}

bool operator==(const char lhs[], const Bigint& rhs){
    return Bigint(lhs) == rhs;
}

int Bigint::operator[](int i) const {
    if (i < 0 || i >= CAPACITY){
        return 0;
    }
    return digits[i];
}

Bigint Bigint::timesDigit(int n) const {
    Bigint result;
    int carry = 0;

    for(int i = 0; i < CAPACITY; ++i){
        int product = digits[i] * n + carry;
        result.digits[i] = product % 10;
        carry = product / 10;
    }

    return result;
}

Bigint Bigint::times10(int n) const {
    Bigint result;

    for(int i = CAPACITY - 1; i >= n; --i){
        result.digits[i] = digits[i - n];
    }

    for(int i = 0; i < n; ++i){
        result.digits[i] = 0;
    }

    return result;
}

Bigint Bigint::operator*(const Bigint& rhs) const {
    Bigint product;

    for(int i = 0; i < CAPACITY; ++i){
        Bigint temp = this->timesDigit(rhs.digits[i]);
        Bigint shift = temp.times10(i);
        product = product + shift;
    }

    return product;
}