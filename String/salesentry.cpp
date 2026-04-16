#include "string.hpp"
#include "salesentry.hpp"
#include <iostream>
#include <vector>
#include <map>

SalesEntry::SalesEntry(const String& line) {
    std::vector<String> fields;

    if (line[0] == '"') {
        int quoteEnd = line.findch(1, '"');

        String firstField = line.substr(1, quoteEnd - 1);
        String remaining = line.substr(quoteEnd + 2, line.length() - 1);

        fields = remaining.split(',');
        fields.insert(fields.begin(), firstField);
    } else {
        fields = line.split(',');
    }

    name = fields[0];
    mainCategory = fields[1];
    subCategory = fields[2];
    image = fields[3];
    link = fields[4];
    ratings = convertDouble(fields[5]);
    noOfRatings = convertInt(fields[6]);
    discountPrice = fields[7];
    actualPrice = fields[8];
}


std::vector<SalesEntry> parse(std::istream& in) {
    std::vector<SalesEntry> entries;
    char buffer[500];

    // skip header
    in.getline(buffer, 500);

    while (in.getline(buffer, 500)) {
        String currentLine(buffer);

        if (currentLine.length() > 0) {
            entries.emplace_back(currentLine);
        }
    }

    return entries;
}


std::ostream& operator<<(std::ostream& out, const SalesEntry& s) {
    out << "Name: " << s.name << '\n';
    out << "Main Category: " << s.mainCategory << '\n';
    out << "Sub Category: " << s.subCategory << '\n';
    out << "Image: " << s.image << '\n';
    out << "Link: " << s.link << '\n';
    out << "Rating: " << s.ratings << '\n';
    out << "No. of ratings: " << s.noOfRatings << '\n';
    out << "Discount Price: " << s.discountPrice << '\n';
    out << "Actual Price: " << s.actualPrice << '\n';

    return out;
}


void outputAll(std::ostream& out, const std::vector<SalesEntry>& data) {
    for (const auto& entry : data) {
        out << entry << '\n';
    }
}


void outputTotal(std::ostream& out, const std::vector<SalesEntry>& data) {
    int sum = 0;

    for (const auto& entry : data) {
        sum += getRatings(entry);
    }

    out << "Total number of ratings: " << sum << '\n';
}


void outputLink(std::ostream& out, const std::vector<SalesEntry>& data) {
    for (const auto& entry : data) {
        out << getLink(entry) << '\n';
    }
}


int convertInt(const String& s) {
    int value = 0;
    int index = 0;
    bool isNegative = false;

    if (s[0] == '-') {
        isNegative = true;
        index = 1;
    }

    while (s[index] != '\0') {
        if (s[index] >= '0' && s[index] <= '9') {
            value = value * 10 + (s[index] - '0');
        } else if (s[index] != ',') {
            break;
        }
        ++index;
    }

    return isNegative ? -value : value;
}


double convertDouble(const String& s) {
    double value = 0.0;
    double factor = 0.1;
    bool decimalPart = false;
    bool isNegative = false;
    int index = 0;

    if (s[0] == '-') {
        isNegative = true;
        index = 1;
    }

    for (; s[index] != '\0'; ++index) {
        if (s[index] == '.') {
            decimalPart = true;
        } else if (!decimalPart) {
            value = value * 10 + (s[index] - '0');
        } else {
            value += (s[index] - '0') * factor;
            factor *= 0.1;
        }
    }

    return isNegative ? -value : value;
}


int getRatings(const SalesEntry& s) {
    return s.noOfRatings;
}


String getLink(const SalesEntry& s) {
    return s.link;
}


double getRatingValue(const SalesEntry& s) {
    return s.ratings;
}


void outputRatings(std::ostream& out, const std::vector<SalesEntry>& data) {
    std::map<double, int> counts;

    for (const auto& entry : data) {
        counts[getRatingValue(entry)]++;
    }

    for (auto it = counts.begin(); it != counts.end(); ++it) {
        out << it->first << ": " << it->second << '\n';
    }
}