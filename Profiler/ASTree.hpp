#ifndef INCLUDES_ASTree_H_
#define INCLUDES_ASTree_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <list>
#include <vector>
#include <string>
#include <algorithm>


bool                     isStopTag (std::string);
std::string              readUntil (std::istream&, char);
std::string              unEscape  (std::string);
std::vector<std::string> tokenize  (const std::string& s);


// AST nodes can be one of three things:
// category   - internal node of some syntactic category
// token      - a source code token
// whitespace - blanks, tabs, line returns, etc.
enum NodeType {category, token, whitespace};


class AST;


// srcML the data structure for a srcML input file
//
// CLASS INV: Assigned(tree)
//
class srcML {
public:
            srcML     () : tree(0) {};
            ~srcML    ();
            srcML     (const srcML&);
    void    swap      (srcML&);
    srcML&  operator= (srcML);

    void    insertMainHeader    (const std::vector<std::string>&, const std::vector<std::string>&);
    void    insertFileHeader    (const std::string&);
    void    insertMainReport    (const std::vector<std::string>&);
    void    insertFunctionCount (const std::string&);
    void    insertLineCount     (const std::string&);

    friend  std::istream& operator>>(std::istream&, srcML&);
    friend  std::ostream& operator<<(std::ostream&, const srcML&);

private:
    std::string header;
    AST*        tree;
};


// An AST node is either:
//     -A category node and has children
//     -A token or whitespace node and is leaf with text
//
// CLASS INV: if (type == category) than (child != 0) && (text == "")
//            if ((type == token) || (type == whitespace)) then (child == 0) && (text != "")
//
class AST {
public:
                  AST       () {};
                  AST       (NodeType t) : type(t) {};
                  AST       (NodeType t, const std::string&);
                  ~AST      ();
                  AST       (const AST&);
    void          swap      (AST&);
    AST&          operator= (AST);

    AST*          getChild            (std::string);
    std::string   getName             () const;
    void          insertMainHeader    (const std::vector<std::string>&, const std::vector<std::string>&);
    void          insertFileHeader    (const std::string&);
    void          insertMainReport    (const std::vector<std::string>&);
    void          insertFunctionCount (const std::string&);
    void          insertLineCount     (const std::string&);
    std::ostream& print               (std::ostream&) const;
    std::istream& read                (std::istream&);

private:
    NodeType        type;           //category || token || whitespace
    std::string     tag;            //category: the tag name and
    std::string     closeTag;       //          closing tag.
    std::list<AST*> child;          //category: A list of subtrees.
    std::string     text;           //token || whitespace: the text.
};

#endif