#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Structs.h"
//#include "Header.h"
#include "Neural.h"

using namespace std;

const int teamNum = 20;



void clubMenu(Club club[teamNum]);
void readData();
void teamInit(Club club[teamNum]);
void readMatches();
void clubArray(string[], string);
int readMatchesSingle();
void readDataMatch(Match * matches);
void modifyNeeded(Match * matches, Club club[], int numMatch);
void matchesWithSameRecord(Match *, Club[], int, string);
void gradientDescent(Match * matches, Club club[], int numMatch);
void gradientDescent1();
double equation(double var, double A, double B, double C);
double equation(double var, double A, double B, double C, double D);
double sumA(double*, double*, int m, double A, double B, double C, double D);
double sumB(double*, double*, int m, double A, double B, double C, double D);
double sumC(double*, double*, int m, double A, double B, double C, double D);
double sumD(double*, double*, int m, double A, double B, double C, double D);
double sumA(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C);
double sumB(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C);
double sumC(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C);
void createTrainingFile(Match * matches, Club club[], int numMatch, string folder);
double findK2(Match * matches, Club club[], int numMatch, double A, double B, double C);
double calculateRecord(Club club);
void test(Club club[]);
void graph(Match * matches, Club club[], int indexMatches[], int num, string folder);
void eliminated(Match * matches);
void testTeams(Match * matches, Club club[], string folder);
void testAll(Match * matches, Club club[]);
void adjust();
Program folders();
void file(Match * matches, Club club[], int numMatch, string folder);

int main()
{
	neural2();

	//createPlayerFiles(folder);
	//adjust(folder);
	//playersTrait(folder);
	//Program pro;
	//pro = folders();
	//createFixtureFiles(pro);
	//initPro(pro);
	//string folder = "";
	/*
	for (int x = 0; x < pro.lea[0].numSeason; x++)
	{
	for (int i = 0; i < pro.lea[0].sea[x].numClubs; i++)
	{
	int space = 50 - pro.lea[0].sea[x].clu[i].name.length();
	cout << pro.lea[0].sea[x].clu[i].name << setprecision(3) << fixed << setw(space) << pro.lea[0].sea[x].clu[i].avgTrait <<  endl;
	}
	cout << endl << endl;
	}
	*/
	/*
	string folder;
	for (int x = 0; x < pro.lea[0].numSeason; x++)
	{

		folder = pro.lea[0].name + pro.lea[0].sea[x].yearStart;
		cout << "Directory: " << folder << endl << endl;
		//file(pro.lea[0].sea[x].mat, pro.lea[0].sea[x].clu, pro.lea[0].sea[x].numMatches, folder);
		createTrainingFile(pro.lea[0].sea[x].mat, pro.lea[0].sea[x].clu, pro.lea[0].sea[x].numMatches, folder);
		//testTeams(pro.lea[0].sea[x].mat, pro.lea[0].sea[x].clu, folder);

		cout << endl << endl;
	}
	*/
	//eliminated(matches);
	//testTeams(matches,  club);
	//testAll(matches, club);
	//gradientDescent1();
	//gradientDescent(matches, club, numMatch);
	//gradientDescent(pro.lea[0].sea[0].mat, pro.lea[0].sea[0].clu, pro.lea[0].sea[0].numMatches);
	//cout << findK2(matches, club, numMatch, A, B, C);
	//test(club);
	//clubMenu(club);
	system("pause");
	return 0;
}

void test(Club club[])
{
	double A = -0.116564, B = 0.340718, C = 9.49892;
	double k = -1.3352;
	int ans = 0;
	int ans1, ans2;
	while (ans != -1)
	{
		if (ans != -1)
		{
			for (int i = 0; i < 20; i++)
			{
				cout << i << "." << club[i].name << endl;
			}
			cout << "Home: " << endl;
			cin >> ans1;
			cout << "Away: " << endl;
			cin >> ans2;
			cout << "Home: " << club[ans1].name << "	Away: " << club[ans2].name << endl;
			cout << club[ans1].avgTrait << "	" << club[ans2].avgTrait << endl;
			cout << equation(club[ans1].avgTrait - club[ans2].avgTrait, A, B, C) << endl;
			cout << (club[ans2].beta - club[ans1].beta) << endl;
			cout << equation(club[ans1].avgTrait - club[ans2].avgTrait, A, B, C) + (club[ans2].beta - club[ans1].beta)*k << endl;
			cout << "cont?	";
			cin >> ans;
		}
	}
}

//test the hypothesis for home effect
void eliminated(Match * matches)
{
	double A, B, C, tempA, tempB, tempC;
	double threshold = 0.001;
	A = 5, B = 5, C = 10;
	tempA = 0, tempB = 0, tempC = 0;
	double learning = 0.0001;
	ifstream inFile;
	inFile.open("matchesWithSameRecord.txt");
	int num = 0;
	int * indexMatches = NULL;
	int m = -1;
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		string line;
		getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			num++;
		}
		m = num;
		indexMatches = new int[num];
		inFile.clear();
		inFile.seekg(0, ios::beg);
		getline(inFile, line);
		//cout << num << endl;
		num = 0;
		while (!inFile.eof())
		{
			inFile >> line;
			//cout << line << "	";
			inFile >> line;
			//cout << line << endl;
			indexMatches[num] = stoi(line);
			getline(inFile, line);
			num++;
		}
		ofstream outFile;
		outFile.open("test.txt");
		int number = 0;
		for (int i = 0; i < num; i++)
		{
			if (abs(matches[indexMatches[i]].home - matches[indexMatches[i]].away) < 2)
			{
				outFile << endl;
				number++;
				outFile << number << "	" << matches[i].index << "	" << matches[i].away << "	" << matches[i].result << "	" << matches[i].home << "	" << matches[i].attendance;
			}
		}

	}
}
void testAll(Match * matches, Club club[])
{
	int indexMatches[380];
	for (int i = 0; i < 380; i++)
	{
		indexMatches[i] = i;
	}
	int num = 380;
	//graph(matches, club, indexMatches, num);
}
void testTeams(Match * matches, Club club[], string folder)
{
	ifstream inFile;
	//inFile.open(folder + "/fixtures.txt");
	inFile.open(folder + "/matchesWithSameRecord1.txt");
	string line;
	int * indexMatches = NULL;
	getline(inFile, line);
	int num = 0;
	while (!inFile.eof())
	{
		getline(inFile, line);
		num++;
	}

	indexMatches = new int[num];
	inFile.clear();
	inFile.seekg(0, ios::beg);
	num = 0;
	getline(inFile, line);
	while (!inFile.eof())
	{
		inFile >> line;
		if (isdigit(line.at(0)))
		{
			inFile >> line;
			//cout << line << endl;
			indexMatches[num] = stoi(line);
			num++;
		}

		getline(inFile, line);
	}
	cout << "matches: " << num << endl;
	cout << "Directory: " << folder << endl << endl;
	graph(matches, club, indexMatches, num, folder);
	inFile.close();
}

//findK2, calculateRecord, gradientDescent, sumA, equation come together
double findK2(Match * matches, Club club[], int numMatch, double A, double B, double C)
{
	ofstream outFile;
	outFile.open("kvalue.txt");
	double k2, k = 0;
	int num = numMatch;
	double highest = 0, lowest = 0;
	for (int i = 0; i < numMatch; i++)
	{
		k2 = 0;
		double betaA = calculateRecord(club[matches[i].home]);
		double betaB = calculateRecord(club[matches[i].away]);
		double var = club[matches[i].home].avgTrait - club[matches[i].away].avgTrait;
		cout << matches[i].index << "	" << betaA << "	" << betaB << endl;
		cout << (A*var*var + B*var + C) << endl;
		cout << matches[i].winType() << endl;
		if (betaA - betaB != 0)
		{
			k2 = (matches[i].winType() - (A*var*var + B*var + C)) / (betaA - betaB);
			k += k2;
			num--;
			if (highest < k2)
			{
				highest = k2;
			}
			if (lowest > k2)
			{
				lowest = k2;
			}
		}
		int winType = matches[i].winType();
		club[matches[i].home].newMatch(winType);
		club[matches[i].away].newMatch(-winType);
		outFile << endl << matches[i].index << "	" << k2;
		cout << "Lowest	" << lowest << endl;
		cout << "Highest	" << highest << endl;
	}
	return k / num;
}
double calculateRecord(Club club)
{

	return club.beta;
}

void graph(Match * matches, Club club[], int indexMatches[], int num, string folder)
{
	ofstream outFile;
	outFile.open(folder + "/graph4.txt");
	double *var;
	int *result;
	int graph[53][5];
	for (int x = 0; x < 27; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			graph[x][y] = 0;
		}
	}
	var = new double[num];
	result = new int[num];
	for (int i = 0; i < num; i++)
	{
		var[i] = club[matches[indexMatches[i]].home].avgTrait - club[matches[indexMatches[i]].away].avgTrait;
		result[i] = matches[indexMatches[i]].winType();
		//cout << matches[indexMatches[i]].index << "	" << var[i] << setw(10)<< fixed << right << result[i] << endl;
		int num = (var[i] / 1) + 13;

		graph[num][result[i] + 2]++;

	}

	for (int x = 4; x >= 0; x--)
	{
		cout << endl;
		for (int y = 0; y < 27; y++)
		{
			if (graph[y][x] != 0 || (x == 2 && y == 13))
			{
				if (graph[y][x] <= 9)
				{
					cout << " " << graph[y][x] << " ";
					outFile << " " << graph[y][x] << " ";
				}
				else
				{
					cout << graph[y][x] << "/";
					outFile << graph[y][x] << "/";
				}

			}
			else
			{
				cout << "-=-";
				outFile << "-=-";
			}

		}
		cout << endl;
		outFile << endl;
	}
	for (int i = 0; i < 27; i++)
	{
		if ((i - 13) >= -9 && (i - 13) < 0)
		{
			cout << i - 13 << " ";
			outFile << i - 13 << " ";
		}
		else if (i - 13 < -9)
		{
			cout << i - 13;
			outFile << i - 13;
		}
		else if ((i - 13) >= 0 && (i - 13) < 10)
		{
			cout << " " << i - 13 << " ";
			outFile << " " << i - 13 << " ";
		}
		else
		{
			cout << i - 13 << " ";
			outFile << i - 13 << " ";
		}
	}
	cout << endl;

	outFile.close();
	delete[] var;
	delete[] result;
}

void gradientDescent1()
{
	double A, B, C, D, tempA, tempB, tempC, tempD;
	double threshold = 0.00000001;
	A = 100, B = -100, C = 80, D = 0;
	tempA = 0, tempB = 0, tempC = 0;
	double learning = 0.0001;
	ifstream inFile;
	inFile.open("test1.txt");
	int num = 0;
	double * x = NULL;
	double * y = NULL;
	int m = -1;
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		string line;
		while (!inFile.eof())
		{
			getline(inFile, line);
			num++;
		}
		m = num;
		//cout << "num" << m << endl;
		x = new double[num];
		y = new double[num];
		inFile.clear();
		inFile.seekg(0, ios::beg);
		//getline(inFile, line);
		//cout << num << endl;
		num = 0;
		while (!inFile.eof())
		{
			inFile >> line;
			x[num] = stoi(line);
			cout << "x" << num << "	" << x[num];
			inFile >> line;
			y[num] = stoi(line);
			cout << "		y" << num << "	" << y[num] << endl;
			num++;
		}
	}
	//graph(matches, club, indexMatches,num);

	bool trueFalse = true;
	int iter = 0;
	while (trueFalse)
	{
		iter++;
		tempA = A - learning*sumA(x, y, m, A, B, C, D);
		tempB = B - learning*sumB(x, y, m, A, B, C, D);
		tempC = C - learning*sumC(x, y, m, A, B, C, D);
		tempD = D - learning*sumD(x, y, m, A, B, C, D);
		//cout << learning << endl;
		//cout << "m"<< m << endl;
		//cout << learning*(1 / m)*sumA(matches, club, indexMatches, m, A, B, C) << endl;
		//cout <<"a"<< tempA << endl;
		//cout << "b"<< abs(A - tempA) << endl;
		//cout << 0.0001 - abs(B - tempB) << endl;
		//cout << 0.0001 - abs(C - tempC) << endl;
		if (threshold > abs(A - tempA) && abs(B - tempB) < threshold && abs(C - tempC) < threshold)
		{
			trueFalse = false;
			cout << A << "	" << B << "	" << C << endl;
			cout << "Temp:	" << tempA << "	" << tempB << "	" << tempC << "	" << tempD << endl;
		}
		A = tempA;
		B = tempB;
		C = tempC;
		D = tempD;
	}

	inFile.close();
}

void gradientDescent(Match * matches, Club club[], int numMatch)
{
	double A, B, C, tempA, tempB, tempC;
	double threshold = 0.00000001;
	A = 5, B = 5, C = 10;
	tempA = 0, tempB = 0, tempC = 0;
	double learning = 0.0001;
	ifstream inFile;
	inFile.open("matchesWithSameRecord.txt");
	int num = 0;
	int * indexMatches = NULL;
	int m = -1;
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		string line;
		getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			num++;
		}
		m = num;
		indexMatches = new int[num];
		inFile.clear();
		inFile.seekg(0, ios::beg);
		getline(inFile, line);
		//cout << num << endl;
		num = 0;
		while (!inFile.eof())
		{
			inFile >> line;
			//cout << line << "	";
			inFile >> line;
			//cout << line << endl;
			indexMatches[num] = stoi(line);
			getline(inFile, line);
			num++;
		}
	}
	//graph(matches, club, indexMatches,num);

	bool trueFalse = true;
	int iter = 0;
	while (trueFalse)
	{
		iter++;
		tempA = A - learning*sumA(matches, club, indexMatches, m, A, B, C);
		tempB = B - learning*sumB(matches, club, indexMatches, m, A, B, C);
		tempC = C - learning*sumC(matches, club, indexMatches, m, A, B, C);
		//cout << learning << endl;
		//cout << 1 / m << endl;
		//cout << learning*(1 / m)*sumA(matches, club, indexMatches, m, A, B, C) << endl;
		//cout << 0.0001 - abs(A - tempA) << endl;
		//cout << 0.0001 - abs(B - tempB) << endl;
		//cout << 0.0001 - abs(C - tempC) << endl;
		if (threshold > abs(A - tempA) && abs(B - tempB) < threshold && abs(C - tempC) < threshold)
		{
			trueFalse = false;
			cout << A << "	" << B << "	" << C << endl;
			cout << "Temp:	" << tempA << "	" << tempB << "	" << tempC << endl;
		}
		A = tempA;
		B = tempB;
		C = tempC;
	}

	inFile.close();
}

double sumA(double* x, double* y, int m, double A, double B, double C, double D)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = x[i];
		sum += (equation(var, A, B, C, D) - y[i])*var*var*var;
		//cout << "Var	" << var << endl;
		//cout << "Equation	" << (equation(var, A, B, C) - y[i]) << endl;
	}

	//cout << "SumA	" << (1 / (double)m)*sum << endl;
	return (1 / (double)m)*sum;
}

double sumB(double* x, double* y, int m, double A, double B, double C, double D)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = x[i];
		sum += (equation(var, A, B, C, D) - y[i])*var*var;
	}
	//cout << "SumA	" << (1 / (double)m)*sum << endl;
	return (1 / (double)m)*sum;
}

double sumC(double* x, double* y, int m, double A, double B, double C, double D)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = x[i];
		sum += (equation(var, A, B, C, D) - y[i])*var;
	}
	//cout << "SumA	" << (1 / (double)m)*sum << endl;
	return (1 / (double)m)*sum;
}

double sumD(double* x, double* y, int m, double A, double B, double C, double D)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = x[i];
		sum += (equation(var, A, B, C, D) - y[i]);
		//cout << "Var	" << var << endl;
		//cout << "Equation	" << (equation(var, A, B, C) - y[i]) << endl;
	}

	//cout << "SumA	" << (1 / (double)m)*sum << endl;
	return (1 / (double)m)*sum;
}

double sumA(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = club[matches[indexMatches[i]].home].avgTrait - club[matches[indexMatches[i]].away].avgTrait;
		sum += (equation(var, A, B, C) - matches[indexMatches[i]].winType())*var*var;
	}
	//cout << "SumA	" << (1 / (double)m)*sum << endl;
	return (1 / (double)m)*sum;
}

double sumB(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = club[matches[indexMatches[i]].home].avgTrait - club[matches[indexMatches[i]].away].avgTrait;
		sum += (equation(var, A, B, C) - matches[indexMatches[i]].winType())*var;
	}
	return (1 / (double)m)*sum;
}

double sumC(Match * matches, Club club[], int * indexMatches, int m, double A, double B, double C)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		double var = club[matches[indexMatches[i]].home].avgTrait - club[matches[indexMatches[i]].away].avgTrait;
		sum += (equation(var, A, B, C) - matches[indexMatches[i]].winType());
	}
	return (1 / (double)m)*sum;
}

double equation(double var, double A, double B, double C)
{
	return (A * var * var + B * var + C);
}

double equation(double var, double A, double B, double C, double D)
{
	return (A * var * var * var + B * var* var + C* var + D);
}


//Find matches that records are the same
void matchesWithSameRecord(Match * matches, Club club[], int numMatch, string folder)
{
	ofstream outFile;
	outFile.open(folder + "/matchesWithSameRecord1.txt");
	int num = 1;
	for (int i = 0; i < numMatch; i++)
	{
		bool trueFalse = true;

		//Choose either one


		double betaA = calculateRecord(club[matches[i].home]);
		double betaB = calculateRecord(club[matches[i].away]);
		/*
		if (betaA != betaB)
		{
		trueFalse = false;
		}
		*/

		for (int x = 0; x < 5; x++)
		{

			//cout << club[matches[i].away].record[i] << "	" << club[matches[i].home].record[i] << endl;
			if (club[matches[i].away].record[x] != club[matches[i].home].record[x])
			{
				trueFalse = false;
			}
		}

		if (trueFalse)
		{
			cout << matches[i].index << "	" << betaA << "		" << betaB << "	";
			for (int x = 0; x < 5; x++)
			{
				cout << club[matches[i].away].record[x] << "/";
			}
			cout << "	";
			for (int x = 0; x < 5; x++)
			{
				cout << club[matches[i].home].record[x] << "/";
			}
			cout << endl;
			outFile << endl;
			outFile << num << "	" << matches[i].index << "	" << matches[i].away << "	" << matches[i].result << "	" << matches[i].home << "	" << matches[i].attendance;
			num++;
		}

		int winType = matches[i].winType();
		club[matches[i].home].newMatch(winType);
		club[matches[i].away].newMatch(-winType);
		//cout << endl;
	}
	outFile.close();
}

//
void createTrainingFile(Match * matches, Club club[], int numMatch, string folder)
{
	ofstream outFile;
	outFile.open(folder + "/training.txt");
	int num = 1;
	for (int i = 0; i < numMatch; i++)
	{
		bool trueFalse = true;

		//Choose either one


		double betaA = calculateRecord(club[matches[i].home]);
		double betaB = calculateRecord(club[matches[i].away]);
		/*
		if (betaA != betaB)
		{
		trueFalse = false;
		}
		*/


		//cout << matches[i].index << "	" << betaA << "		" << betaB << "	";
		//cout << endl;
		outFile << endl;
		//outFile << num << "	" << matches[i].index << "	" << matches[i].away << "	" << matches[i].result << "	" << matches[i].home << "	" << matches[i].attendance;
		outFile << num << "	" << club[matches[i].home].avgTrait - club[matches[i].away].avgTrait << "	" << betaA - betaB << "	"<<matches[i].winType();
		num++;


		int winType = matches[i].winType();
		club[matches[i].home].newMatch(winType);
		club[matches[i].away].newMatch(-winType);
		//cout << endl;
	}
	outFile.close();
}

//dsfds
void modifyNeeded(Match * matches, Club club[], int numMatch)
{
	for (int i = 0; i < numMatch; i++)
	{
		//matchesWithSameRecord(matches, club, numMatch);
		int winType = matches[i].winType();
		club[matches[i].home].newMatch(winType);
		club[matches[i].away].newMatch(-winType);
		for (int i = 0; i < 5; i++)
		{
			cout << club[matches[i].away].record[i] << "	";
		}
		cout << endl;
	}

}



//read match info
//note: first line in the txt file should be a day
//note: check reresult.txt, last line
void readMatches(string folder)
{
	Match** day;
	int* matchesDay;
	int days = 0, matches = 0;
	ifstream inFile;
	inFile.open(folder + "/fixtures.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		string line;
		getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			if (isdigit(line.at(0)))
			{

			}
			else
			{
				days++;
			}
		}
		matchesDay = new int[days];
		for (int i = 0; i < days; i++)
		{
			matchesDay[i] = 0;
		}
		inFile.clear();
		inFile.seekg(0, ios::beg);
		days = 0;
		getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			if (isdigit(line.at(0)))
			{
				matchesDay[days - 1]++;
			}
			else
			{
				days++;
			}
		}

		day = new Match*[days];

		for (int i = 0; i < days; i++)
		{
			day[i] = new Match[matchesDay[i]];
		}
		/*
		int numMat = 0;
		for (int i = 0; i < days; i++)
		{
		numMat += matchesDay[i];
		}
		for (int i = 0; i < days; i++)
		{
		cout << "day " << i << " has " << matchesDay[i] << endl;
		}
		cout << numMat << endl;
		cout << days << endl;
		*/
		inFile.clear();
		inFile.seekg(0, ios::beg);
		days = -1;
		int match = 0;
		string clubName[teamNum];
		clubArray(clubName, folder);
		string test, test1;
		int num = -1;
		getline(inFile, line);
		while (!inFile.eof())
		{
			num++;
			//cout << line << endl;
			inFile >> line;
			if (isdigit(line.at(0)))
			{
				day[days][match].index = stoi(line);
				//cout << line << endl;
				//cout << days << "	" << match << endl;
				//getline(inFile, line);
				//cout << "There	"<< line << endl;
				inFile >> line;
				day[days][match].away = stoi(line);
				//cout << line << endl;
				inFile >> line;
				//cout << line << endl;
				day[days][match].result = line;
				inFile >> line;
				//cout << line << endl;
				day[days][match].home = stoi(line);
				inFile >> line;
				inFile >> line;
				day[days][match].attendance = stoi(line);
				//cout << "Attendance	"<<line << endl;
				day[days][match].homeName = clubName[day[days][match].home];
				day[days][match].awayName = clubName[day[days][match].away];

				match++;
			}
			else
			{
				getline(inFile, line);
				//cout << line;
				days++;
				match = 0;
				//cout << days << endl;
			}
		}
		int ans = 0;
		int i = 0;
		while (ans != -1)
		{
			cout << "What days do you want(0-" << days << "): ";
			cin >> ans;
			for (int i = 0; i < matchesDay[ans]; i++)
			{
				int space = 30 - day[ans][i].awayName.length();
				int space1 = 30 - day[ans][i].homeName.length();
				cout << day[ans][i].index << "	" << day[ans][i].awayName << setw(space) << day[ans][i].result << "	" << day[ans][i].homeName << setw(space1) << day[ans][i].attendance << endl;
			}
		}
		delete day;
	}


	//delete day;
	inFile.close();
}


///Menu for clubs
void clubMenu(Club club[teamNum])
{
	//cout << club[0].numPlayer << endl;

	int ans = 1, indexClub = 0;
	while (ans != -1)
	{
		for (int i = 0; i < teamNum; i++)
		{
			cout << i << "." << club[i].name << endl;
		}
		cout << "Choose a club: " << endl;
		cin >> indexClub;
		cout << endl;
		cout << club[indexClub].name << "	Pts:" << club[indexClub].score << "	record:";
		for (int i = 0; i < 5; i++)
		{
			cout << club[indexClub].record[i] << "/";
		}
		cout << endl;
		for (int i = 0; i < club[indexClub].numPlayer; i++)
		{
			int space;
			if (i < 10)
			{
				space = club[indexClub].player[i].length() + 1;
			}
			else
			{
				space = club[indexClub].player[i].length();
			}
			cout << club[indexClub].player[i] << right << setw(50 - space) << club[indexClub].trait[i] << "		";
			cout << endl;
		}
		cout << "Average: " << club[indexClub].avgTrait << endl;
		cout << "Cont: ";
		cin >> ans;
	}
}



//array of folder
Program folders()
{
	Program pro;
	string line, *lea = NULL, **sea = NULL;
	int leaNum = 0, *seaNum = NULL;
	ifstream inFile;
	inFile.open("folders.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			inFile >> line;
			if (!isdigit(line.at(0)))
			{
				leaNum++;
			}
		}
		seaNum = new int[leaNum];
		for (int i = 0; i < leaNum; i++)
		{
			seaNum[i] = 0;
		}
		//cout << leaNum << endl;
		inFile.clear();
		inFile.seekg(0, ios::beg);
		lea = new string[leaNum];
		leaNum = 0;
		while (!inFile.eof())
		{
			inFile >> line;
			if (!isdigit(line.at(0)))
			{
				//cout << leaNum  << "	" << line << endl;

				lea[leaNum] = line;
				leaNum++;
			}
			else
			{
				seaNum[leaNum - 1]++;
			}
		}

		inFile.clear();
		inFile.seekg(0, ios::beg);
		sea = new string*[leaNum];
		int num = 0;
		for (int i = 0; i < leaNum; i++)
		{
			sea[i] = new string[seaNum[i]];
		}
		leaNum = -1;
		//cout << seaNum[0] << endl;
		while (!inFile.eof())
		{
			inFile >> line;
			if (!isdigit(line.at(0)))
			{
				leaNum++;
				num = 0;
			}
			else
			{
				sea[leaNum][num] = line;
				num++;
			}
		}
	}
	leaNum = leaNum + 1;
	//cout << leaNum << endl;
	pro.lea = new League[leaNum];
	pro.numLeagues = leaNum;
	for (int i = 0; i < leaNum; i++)
	{
		pro.lea[i].numSeason = seaNum[i];
		pro.lea[i].sea = new Season[seaNum[i]];
		pro.lea[i].name = lea[i];
		//cout << pro.lea[i].name << endl;
		for (int x = 0; x < seaNum[i]; x++)
		{
			pro.lea[i].sea[x].yearStart = sea[i][x];
			//cout << pro.lea[i].sea[x].yearStart << endl;
		}
	}
	inFile.close();




	delete[] lea;
	delete[] seaNum;
	delete[] sea;
	return pro;
}


void clubArray(string club[], string folder)
{
	string line;
	ifstream inFile;
	int num = 0;
	inFile.open(folder + "/clubs.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			club[num] = line;
			num++;
		}
	}
}


void file(Match * matches, Club club[], int numMatch, string folder)
{
	ofstream outFile;
	outFile.open("matchList" + folder + ".txt");
	for (int i = 0; i < numMatch; i++)
	{
		double betaA = calculateRecord(club[matches[i].home]);
		double betaB = calculateRecord(club[matches[i].away]);

		outFile << endl;
		cout << setprecision(5) << matches[i].index << "	" << club[matches[i].away].avgTrait << "	" << club[matches[i].home].avgTrait << "	" << betaA << "	" << betaB << "	" << matches[i].winType() << endl;
		outFile << setprecision(5) << matches[i].index << "	" << club[matches[i].away].avgTrait << "	" << club[matches[i].home].avgTrait << "	" << betaA << "	" << betaB << "	" << matches[i].winType();

		int winType = matches[i].winType();
		club[matches[i].home].newMatch(winType);
		club[matches[i].away].newMatch(-winType);
	}
	outFile.close();
}