#ifndef CS2_BIGINT_HPP
#define CS2_BIGINT_HPP
#include <iostream>
#include <fstream>

const int CAPACITY = 300;

class Bigint {
public:
    Bigint();                     // Iniializes array to 0
    Bigint(int);                  // initializes from int
    Bigint(const char[]);         // initializes from char

    void debugPrint(std::ostream&) const; // prints out elements of array
    bool operator==(const Bigint&) const; //compares two bigints
    friend std::ostream& operator<<(std::ostream&, const Bigint&);
    friend std::istream& operator>>(std::istream&, Bigint&);
    Bigint operator+(const Bigint&) const;
    int operator[](int) const;
    Bigint timesDigit(int) const;
    Bigint times10(int) const;
    Bigint operator*(const Bigint&) const;

private:
    int digits[CAPACITY];
};

bool operator==(const Bigint&, int);
bool operator==(int, const Bigint&);

bool operator==(const Bigint&, const char[]);
bool operator==(const char[], const Bigint&);


#endif