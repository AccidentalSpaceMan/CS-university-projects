#ifndef CS_SALESENTRYH
#define CS_SALESENTRYH

#include "string.hpp"
#include <iostream>
#include <vector>




// A single sales entry
class SalesEntry {
public:
            SalesEntry() {};
            SalesEntry(const String&);
    friend  std::ostream& operator<<(std::ostream&, const SalesEntry&);
    friend int getRatings(const SalesEntry&);
    friend String getLink(const SalesEntry&);
    friend double getRatingValue(const SalesEntry&);


private:
    String  name;
    String  mainCategory;
    String  subCategory;
    String  image;
    String  link;
    double  ratings;
    int     noOfRatings;
    String  discountPrice;
    String  actualPrice;
};


//
// Free functions
//

std::vector<SalesEntry> parse      (std::istream&);
void                    outputAll  (std::ostream&, const std::vector<SalesEntry>&);
void                    outputTotal(std::ostream&, const std::vector<SalesEntry>&);
void                    outputLink (std::ostream&, const std::vector<SalesEntry>&);
void                    outputRatings(std::ostream&, const std::vector<SalesEntry>&);
int convertInt(const String&);
double convertDouble(const String&);

#endif