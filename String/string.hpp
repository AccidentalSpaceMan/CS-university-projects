#ifndef CS23001_STRING_INTERFACE_HPP
#define CS23001_STRING_INTERFACE_HPP

#include <iostream>
#include <cassert>
#include <vector>


// CLASS INV: str[length()] == 0             &&
//            length()      == capacity()    &&
//            capacity()    == stringSize - 1
class String {
public:
            String        ();                                  //Empty string
            String        (char);                              //String('x')
            String        (const char[]);                      //String("abc")
            String        (const String&);                     //Copy Constructor
            ~String       ();                                  //Destructor
    void    swap          (String&);                           //Constant time swap
    String& operator=     (String);                            //Assignment Copy

    int     capacity      ()                           const;  //Max chars that can be stored
    int     length        ()                           const;  //Actual number of chars in string
    char&   operator[]    (int);                               //Accessor/Modifier
    char    operator[]    (int)                        const;  //Accessor

    String& operator+=    (const String&);
    bool    operator==    (const String&)              const;
    bool    operator<     (const String&)              const;
    String  substr        (int start, int end)         const;  //sub string from start to end index
    int     findch        (int start, char ch)         const;  //Find ch starting at index start
    int     findstr       (int start, const String& s) const;  //Find s starting at index start

    std::vector<String> split(char) const;

    friend  std::ostream& operator<<(std::ostream&, const String&);
    friend  std::istream& operator>>(std::istream&, String&);

private:
    char    *str;                                              //Pointer to char[]
    int     stringSize;                                        //Size includes NULL terminator
};

String  operator+       (String,        const String&);
bool    operator==      (const char[],  const String&);
bool    operator==      (char,          const String&);
bool    operator<       (const char[],  const String&);
bool    operator<       (char,          const String&);
bool    operator<=      (const String&, const String&);
bool    operator!=      (const String&, const String&);
bool    operator>=      (const String&, const String&);
bool    operator>       (const String&, const String&);

#endif