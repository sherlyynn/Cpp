#include <iostream>
#include "StringSet.h"
#include <string>
using std::cout;
using std::endl;

int main ()
{
	StringSet sset1;
	sset1.insert("cat");
	sset1.insert("bat");
	sset1.insert("rat");
	cout << "insert success: " << sset1.insert("badger") << endl;
	
	StringSet sset2;
	sset2.insert("elephant");
	sset2.insert("bat");
	sset2.insert("hamster");
	sset2.insert("weasel");
	//sset2.remove("weasel");
	cout << "index of weasel = " << sset2.find("hamster") << endl;

	cout <<  "ss1 size is " << sset1.size() << endl;
	cout << "ss2 size is " << sset2.size() << endl;
	StringSet sset3(sset1.unions(sset2));

	StringSet sset4;
	sset4 = sset2.intersection(sset1);

	StringSet sset5;
	sset5 = sset2.difference(sset1);

	sset1.print(); 
	cout << endl;
	sset2.print();
	cout << endl;
	sset3.print();
	cout << endl;
	sset4.print();
	cout << endl;
	sset5.print();

	std::cout << endl;
	return 0;
}