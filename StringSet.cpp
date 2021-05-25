#include "StringSet.h"
#include <string>
#include <iostream>

//constructor
//creates empty array of max size 2
StringSet::StringSet()
{
	maxSize = 2;
	arr = new std::string[maxSize];
	//maxSize = 2;
	currSize = 0;
}

//destructor
//delete memory assigned to array
StringSet::~StringSet()
{
	delete[] arr;
}

//helper function
//implementation of copy array using overloaded assignment op
void StringSet::copyArr(const StringSet & strset)
{
	currSize = strset.currSize;
	maxSize = strset.maxSize; 

	arr = new std::string[maxSize];

	for (int i = 0; i < currSize ; i++)
	{
		arr[i] = strset.arr[i];
	}

}

//copy constructor
//creates deep copy of a new array if an array hasn't already exists
//"initializes the new object with an already existing object" - tutorialspoint
StringSet::StringSet(const StringSet & strset)
{
	copyArr(strset);
}


//overloaded assignment operator
//this is so we can create copies of array if an array already exists
//"assigns the value of one object to another object both of which already exists" - tutorialspoint
StringSet & StringSet::operator=(const StringSet & strset)
{
	if (this != &strset)
	{
		delete[] arr;
		copyArr(strset);
	}

	return *this;
}

//Mutator

// *1*  if value is a duplicate of an element in array, don't insert value
// *2*  if the elements to be insert excedes maxSize, make maxSize x 2; make a new array with that new maxSize; 
// ^... store all old array content into new array; free old array, assign new array to old array.
// *3* insert value at next available index if value is not duplicate of an element in array
// *4* increment currSize, returns true
bool StringSet::insert(std::string name)
{
	for (int i = 0; i < currSize; i++) //*1*//
	{
		if (arr[i].compare(name) == 0)
		{
			return false;
		}
	}
	
	if (currSize >= maxSize) //*2//
	{
		maxSize = maxSize*2;
		std::string* newArr = new std::string[maxSize];
		for (int i = 0; i < currSize; i++)
		{
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	}
	arr[currSize] = name; //*3*//
	currSize++; //*4*//
	return true;
}

//Mutator
//if value is a duplicate of an element in array, replaces it with last value, then decrement array size
//if string is a duplicate of an element in array, replace this duplicate with last string
void StringSet::remove(std::string name)
{
	for(int i = 0; i < currSize; i++)
	{
		if(arr[i].compare(name) == 0)
		{
			if(i != (currSize-1)) 
			{
				arr[i] = arr[currSize-1];
			}
			currSize--;
		}
	}
}

//Accessor
//if value is a duplicate of an element in array, returns that duplicate's index value
//if not, returns -1
int StringSet::find(std::string name) const
{
	for(int i = 0; i < currSize; i++)
	{
		if(arr[i].compare(name) == 0)
		{
			return i;
		}
	}
	return -1;

}

//Accessor
//returns the size of array
int StringSet::size() 
{
	
	return currSize;
	
}

//Class Accessor
//if array is an empty set, return current size (should be zero if empty)
//*1*  traverse the first array; in new array, insert the elements from first array into new array
//since insert method takes care of duplicates, we don't need to implement the removal of dupes here
StringSet StringSet::unions(StringSet strset)
{
		StringSet set(strset);

		for(int i = 0; i < currSize; i++) //*1*
		{
				set.insert(arr[i]);
		}
		return set;
}

//Class Accessor
//if array is an empty set, return current size (should be zero if empty)
//if not empty, find the duplicates in both arrays
//*1*  traverse the first array and compare with second array; if the string is a dupe, we insert them into new array
StringSet StringSet::intersection(StringSet strset)
{
		StringSet set;

		for(int i = 0; i < currSize; i++) //*1*//
		{
			if(strset.find(arr[i]) != -1)
			{
				set.insert(arr[i]);
			}
		}
		return set;
}

//Class Accessor
//if array is empty set, return current size (should be zero if empty)
//if not empty, find the difference of the arrays
StringSet StringSet::difference(StringSet strset)
{
		StringSet set(*this);
		for(int i = 0; i < currSize; i++)
		{
			set.remove(strset.arr[i]);
		}
	return set;
}


//!!!---------TESTING FUNCTION---------!!!!
void StringSet::print() 
{
	for (int i = 0; i < maxSize; i++)
	{
		std::cout << arr[i] << " ";
	}
}


