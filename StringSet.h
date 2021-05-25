#pragma once 
#include <string>

class StringSet 
{
public:
	StringSet(); //default constructor
	StringSet(const StringSet & strset); //copy constructor
	StringSet & operator=(const StringSet & strset); //overloaded assignment operator
	~StringSet(); //destructor
	bool insert(std::string name); //returns false, string param
	void remove(std::string name); //returns nothing, string param
	int find (std::string name) const; //returns int i, string param
	int size (); //returns int, no param
	StringSet unions(StringSet strset);
	StringSet intersection(StringSet strset);
	StringSet difference(StringSet strset);
	// TESTING FUNCTION // 
	void print() ;



private:
	std::string* arr = new std::string();
	int maxSize;
	int currSize;
	void copyArr (const StringSet & strset);
	
};