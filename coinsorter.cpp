#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#pragma warning (disable: 4996)



using namespace std;

void countCoins(int &nickelCount, int &dimeCount,
	int &quarterCount, int &loonieCount, int &toonieCount);

int main()
{
	string sensorReading;
	string reading[4];
	string inRoutepath = "../input_files/";
	string fullInpath = "";
	string outRoutePath = "../output_files/";
	string fullOutpath = "";
	string line;
	//string shape;
	//string match;
	int weightNumeric = 0;
	int diameterNumeric = 0;
	int maxTries = 2;
	int tries = 0;
	int maxReading = 5000;
	int minReading = 0;
	int count = 0;
	int numLine = 0;
	int i = 0;
	int readLen = 4;
	//char ch;
	char outputName[1024] = { '\0' };
	char inputName[1024] = { '\0' };
	ifstream input_files;
	ifstream output_files;

	const double wmaxNickel = 4.3;
	const double wminNickel = 3.6;
	const double wmaxDime = 2.2;
	const double wminDime = 1.3;
	const double wmaxQuarter = 4.8;
	const double wminQuarter = 4.0;
	const double wmaxLoonie = 7.5;
	const double wminLoonie = 6.5;
	const double wmaxToonie = 7.85;
	const double wminToonie = 6.75;

	const double dmaxNickel = 21.8;
	const double dminNickel = 20.2;
	const double dmaxDime = 18.7;
	const double dminDime = 17.3;
	const double dmaxQuarter = 24.6;
	const double dminQuarter = 22.8;
	const double dmaxLoonie = 27.0;
	const double dminLoonie = 25.0;
	const double dmaxToonie = 29.1;
	const double dminToonie = 26.9;

	const int wrapNickel = 40;
	const int wrapDime = 50;
	const int wrapQuarter = 40;
	const int wrapLoonie = 25;
	const int wrapToonie = 25;

	int nickelRolls = 0;
	int dimeRolls = 0;
	int quarterRolls = 0;
	int loonieRolls = 0;
	int toonieRolls = 0;

	int nickelinRoll = 0;
	int dimeinRoll = 0;
	int quarterinRoll = 0;
	int loonieinRoll = 0;
	int toonieinRoll = 0;

	int bentCoins = 0;
	int otherCoins = 0;


	double otherCoinW = 0.0;
	double bentCoinW = 0.0;


	//step 1 to 6
	//prompt to enter filename with sensor readings
	cout << "Type the name of the input file containing sensor readings:" << endl;
	cin >> inputName;
	cout << endl;


	fullInpath = inRoutepath + inputName;
	//open the file
	input_files.open(fullInpath, ios::in);

	//if file could not be opened
	while (input_files.fail())
	{
		if (tries < maxTries)
		{
			cerr << "ERROR: File " << inputName << " could not be opened for input" << endl;
			cout << "Type the name of the input file containing sensor readings:" << endl;
			cin >> inputName;
		}

		//if user tries 3 times to input filename
		else if (tries == maxTries)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed" << endl;
			return 1;
		}
		else if (input_files.fail())
		{
			fstream input_files;
			input_files.open(inputName, ios::out);
		}
		else
		{
			tries = maxTries;
		}
		tries++;


	}


	// prompt to enter filename for output
	cout << "Type the name of the output file which will hold the simulation results:" << endl;
	cin >> outputName;
	cout << endl;

	fullOutpath = outRoutePath + outputName;
	//open the file
	output_files.open(fullOutpath, ios::in);


	//if file could not be opened
	while (output_files.fail())
	{
		if (tries < maxTries)
		{
			cerr << "ERROR: File " << outputName << " could not be opened for input" << endl;
			cout << "Type the name of the output file which will hold the simulation results:" << endl;
			cin >> outputName;
		}

		//if user tries 3 times to input filename
		else if (tries == maxTries)
		{
			cerr << "ERROR: You exceeded maximum number of tries allowed" << endl;
			return 2;
		}
		else
		{
			tries = maxTries;
		}
		tries++;


	}

	//read the number of lines of data
	getline(input_files, sensorReading);

	//if file does not read any data, print error message
	//then create an output file
	if (!(input_files >> sensorReading))
	{
		if (sensorReading.empty())
		{
			cerr << "ERROR: Input file is empty." << endl;
			input_files.close();
			ofstream input_files(inputName, ios::out);
		}
	}

	//step7 to 9
	//casting string into an integer to compare 
	//max and min - the range
	//if string contains alphabets, print error message
	//if not, if string is out of range, print error message
	//if file does not show more data(EOF), print error message

	input_files >> ws;

	getline(input_files, sensorReading);

	bool isNumber = isdigit(sensorReading[0]);
	if (isNumber)
	{
		numLine = stoi(sensorReading);
	}



	if ((!isNumber))
	{

		cout << sensorReading << endl;

		cerr << "ERROR: First piece of data in the file is not an integer" << endl;
		input_files.close();
		ofstream input_files(inputName, ios::out);
	}

	else if (numLine <= 0 || numLine > 5000)
	{
		if (numLine <= 0)
		{
			cout << "Number of sensor readings " << numLine << " is too small" << endl;
		}
		else
		{
			cout << "Number of sensor readings " << numLine << " too large" << endl;
		}
	}

	else if (input_files.eof())
	{
		cout << sensorReading << endl;
		cerr << "ERROR:  No data on first line that should contain sensor readings";
		cerr << "and image processing result." << endl;
	}

	//step 11
	//condition c check if both sensor data are present

	string badShape = "bent";
	string goodShape = "usable";
	string match1 = "OneMatch";
	string match2 = "BothMatch";
	string match3 = "NoMatch";
	string extraLine;

	for (int count = 0; count <= numLine; count++)
	{

		string data;
		string token;
		string diameter;
		string shape;
		string match;
		string extraStuff;
		int col = 0;
		int countSpace = 0;
		// added bool to skip lines of defective coins
		bool ignoreLine = false;


		char look = input_files.peek();
		if (look == '\n')
		{
			//getline(input_files, data);
			//cerr << "ERROR: Weight sensor value read on line " << count + 1 << " is not an integer" << endl;
			//cerr << "Simulation terminated early: Please correct your data file" << endl;
			input_files.ignore();
			// decrease the line count if the line is blank (the fle line count is only for data lines not all lines)
			count--;
		}
		else
		{
			getline(input_files, data);
			countSpace = 0;
			for (int j = 0; j <= data.size(); j++)
			{
				if (isspace(data[j]))
				{
					countSpace++;
				}
			}

			switch (countSpace)
			{
			case 0: //if only weightSensor is read

				cerr << "ERROR: Weight sensor measurements only" << endl;
				cerr << "Ignoring line" << count + 1 << " of the input file" << endl;
				input_files.ignore();

				break;
			case 1: //if only diameter is read

				cerr << "ERROR: Weight and diameter sensor measurements only" << endl;
				cerr << "Ignoring line" << count + 1 << " of the input file" << endl;
				input_files.ignore();
				break;

			case 2:

				cerr << "ERROR: Weight and diameter sensor measurements and bent string only" << endl; //change things here
				cerr << "Ignoring line " << count + 1 << " of the input file" << endl;
				input_files.ignore();
				break;

			default:


				istringstream lineStream(data);
				col = 0;
				ignoreLine = false;

				while (getline(lineStream, token, ' '))
				{
					col++;
					cout << token << endl << endl;
					// skip these tokens for ignored lines
					if (!ignoreLine && isalpha(token[0]))
					{
						switch (col)
						{
						case 3:
							// changed == to !=
							if (token.find("bent") != string::npos)
							{
								bentCoins++;

								// get weight of bent coin and add to the sum
								bentCoinW += 2 * ((5.0 / 255.0) * weightNumeric);

								// set bool to true to skip coin type checks
								ignoreLine = true;

							}
							// changed == to !=
							else if (token.find("usable") != string::npos)
							{
								//cerr << "ERROR: Weight and diameter sensor measurements and bent string only" << endl; //change things here
								//cerr << "Ignoring line " << count + 1 << " of the input file" << endl;
							}
							else
							{
								//cerr << "ERROR: Result of test to determine if coin is bent at line " << count + 1 << " is invalid" << endl;
								//cerr << "Ignoring this line of data" << endl;

								// set bool to true to skip coin type checks
								ignoreLine = true;
							}
							break;
						case 4:
							
							// changed match.find to token.find
							if ((token.find("OneMatch") != string:: npos) || ( token.find("NoMatch") != string::npos))
							{
								otherCoins++;

								// get weight of other coin and add to the sum
								otherCoinW += 2 * ((5.0 / 255.0) * weightNumeric);
							}
							// skip for defective coins (bent and other)
							else if (!ignoreLine && token.find("BothMatch") != string::npos)
							{

								//cout << weightNumeric << " " << diameterNumeric << endl;

								double weightCoin = 0;
								weightCoin = 2 * ((5.0 / 255.0) * weightNumeric);

								
								double diameterCoin= 0;
								diameterCoin = 10.0 + (diameterNumeric/8.5);

								cout << "sensor weight->" << weightNumeric << ": weight->" << weightCoin << " sensor diameter->" << diameterNumeric << ": diameter->" << diameterCoin << endl;

								if ((weightCoin <= wmaxNickel && weightCoin >= wminNickel) && (diameterCoin <= dmaxNickel && diameterCoin >= dminNickel))
								{
									nickelinRoll ++;
									if (nickelinRoll == wrapNickel)
									{
										cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
										cout << "The nickel wrapper is now full" << endl;
										cout << "The nickel wrapper has now been replaced" << endl;
										nickelRolls++;
										nickelinRoll = 0;
									}
									else
									{
										cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
										cout << "There are now " << nickelinRoll << " coins in the nickels wrapper" << endl;
									}
								}
								
								else if ((weightCoin <= wmaxDime && weightCoin >= wminDime) && (diameterCoin <= dmaxDime && diameterCoin >= dminDime))
								{
									dimeinRoll++;
									if (dimeinRoll == wrapDime)
									{
										cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
										cout << "The dime wrapper is now full" << endl;
										cout << "The dime wrapper has now been replaced" << endl;
										dimeRolls++;
										dimeinRoll = 0;
									}
									else
									{
										cout << "The Coin Sorter has sent one coin to the dime wrapper" << endl;
										cout << "There are now " << dimeinRoll << " coins in the dimes wrapper" << endl;
									}
								}
								else if ((weightCoin <= wmaxQuarter && weightCoin >= wminQuarter) && (diameterCoin <= dmaxQuarter && diameterCoin >= dminQuarter))
								{
									quarterinRoll++;
									if (quarterinRoll == wrapQuarter)
									{
										cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
										cout << "The quarter wrapper is now full" << endl;
										cout << "The quarter wrapper has now been replaced" << endl;
										quarterRolls++;
										quarterinRoll = 0;
									}
									else
									{
										cout << "The Coin Sorter has sent one coin to the quarter wrapper" << endl;
										cout << "There are now " << quarterinRoll << " coins in the quarter wrapper" << endl;
									}
								}
								else if ((weightCoin <= wmaxLoonie && weightCoin >= wminLoonie) && (diameterCoin <= dmaxLoonie && diameterCoin >= dminLoonie))
								{
									loonieinRoll++;
									if (loonieinRoll == wrapLoonie)
									{
										cout << "The Coin Sorter has sent one coin to the loonie wrapper" << endl;
										cout << "The loonie wrapper is now full" << endl;
										cout << "The loonie wrapper has now been replaced" << endl;
										loonieRolls++;
										loonieinRoll = 0;
									}
									else
									{
										cout << "The Coin Sorter has sent one coin to the loonie wrapper" << endl;
										cout << "There are now " << loonieinRoll << " coins in the loonie wrapper" << endl;
									}
								}
								else if ((weightCoin <= wmaxToonie && weightCoin >= wminToonie) && (diameterCoin <= dmaxToonie && diameterCoin >= dminToonie))
								{
									toonieinRoll++;
									if (toonieinRoll == wrapToonie)
									{
										cout << "The Coin Sorter has sent one coin to the toonie wrapper" << endl;
										cout << "The toonie wrapper is now full" << endl;
										cout << "The toonie wrapper has now been replaced" << endl;
										toonieRolls++;
										toonieinRoll = 0;
									}
									else
									{
										cout << "The Coin Sorter has sent one coin to the toonie wrapper" << endl;
										cout << "There are now " << toonieinRoll << " coins in the toonie wrapper" << endl;
									}
								}

								else
								{
									otherCoins++;
								}
		
							}
							else
							{
								cerr << "ERROR: image processing result at line " << count + 1 << " is invalid" << endl;
								cerr << "Ignoring this line of data" << endl;
							}
							break;
						case 5:
						{
							cerr << "ERROR: Extra data at line " << count + 1 << endl;
							cerr << "Ignoring extra data" << endl;
						}

						break;

						}
					}
					else
					{
						switch (col)
						{
						case 1:
							if (isalpha(token[0]))
							{
								cerr << "ERROR: Weight sensor value read on line " << count + 1 << " is not an integer" << endl;
								cerr << "Simulation terminated early: Please correct your data file" << endl;
							}

							else
							{
								
								// need to covert token to weight before the test
								weightNumeric = stoi(token);
								if (weightNumeric <= 0 || weightNumeric >= 255)
								{
									
									cerr << "ERROR: Sensor reading out of range, ignoring line " << count + 1 << " in the input file" << endl;
									// set bool to true to skip out of bounds line
									ignoreLine = true;
								}
								else
								{
									//cerr << "ERROR: Weight sensor measurements only" << endl;
									//cerr << "Ignoring line" << count + 1 << " of the input file" << endl;
								}

							}

							break;
						case 2:
							if (isalpha(token[0]))
							{
								cerr << "ERROR: Diameter sensor value read on line " << count + 1 << "is not an integer" << endl;
								cerr << "Simulation terminated early : Please correct your data file" << endl;
							}
							else
							{
								
								diameterNumeric = stoi(token);
								// need to convet token to diameter before the test
								if (diameterNumeric <= 0 || diameterNumeric >= 255)
								{
									
									cerr << "ERROR: Sensor reading out of range, ignoring line " << count + 1 << " in the input file" << endl;
									// set bool to true to skip out of bounds line
									ignoreLine = true;
								}
								else
								{
									//cerr << "ERROR: Weight and diameter sensor measurements only" << endl;
									//cerr << "Ignoring line" << count + 1 << " of the input file" << endl;
								}
							}
							break;
						}
					}
				}

			}
		}
	}
	
	//system("cls");

	cout << endl << endl << endl;

	cout << "SUMMARY" << endl;

	cout << "The Coin Sorter made " << nickelRolls << " rolls of nickels." << endl;

	cout << "There are " << nickelinRoll << " nickels in the partially full roll." << endl;

	cout << "The Coin Sorter made " << dimeRolls << " rolls of dimes." << endl;

	cout << "There are " << dimeinRoll << " dimes in the partially full roll." << endl;

	cout << "The Coin Sorter made " << quarterRolls << " rolls of quarters." << endl;

	cout << "There are " << quarterinRoll << " quarters in the partially full roll." << endl;

	cout << "The Coin Sorter made " << loonieRolls << " rolls of loonies." << endl;

	cout << "There are " << loonieinRoll <<" loonies in the partially full roll." << endl;

	cout << "The Coin Sorter made " << toonieRolls << " rolls of toonies." << endl;

	cout << "There are " << toonieinRoll << " toonies in the partially full roll." << endl;

	cout << "The Coin Sorter processed " << otherCoins << " other coins." << endl;

	cout << "The other coins completely filled " << otherCoins << " containers" << endl;

	cout << "There were " << otherCoins << " other coins in the partially full container" << endl;

	cout << "The total weight of the other coins was " << otherCoinW << " grams" << endl;

	cout << "The Coin Sorter processed " << bentCoinW << " g of bent coins" << endl;

	input_files.close();

	return 0;


}


