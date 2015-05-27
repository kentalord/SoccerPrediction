#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <fstream>
using namespace std;



struct Club
{
	string name;
	double avgTrait;
	int record[5];
	string* player;
	int* trait;
	int numPlayer;
	int score = 0;
	int beta = 0;
	void newMatch(int newRecord)
	{
		beta = 0;
		for (int i = 0; i < 4; i++)
		{
			record[i] = record[i + 1];
		}
		record[4] = newRecord;
		if (newRecord > 0)
		{
			score += 3;
		}
		else if (newRecord == 0)
		{
			score++;
		}
		for (int i = 0; i < 5; i++)
		{
			beta += record[i];
		}
	}
	~Club()
	{
		//delete player;
		//delete trait;
	}
};

struct Match
{
	int index;
	int home;
	int away;
	string homeName;
	string awayName;
	string result;
	int attendance;
	int threshold = 2;
	int winType()
	{
		int awayScore = (int)result[0];
		int homeScore = (int)result[2];
		//cout << result[0] << "2" << result[2] << "3" << result[3] << endl;
		//cout << awayScore << "	" << homeScore << "	" << result << endl;
		/*
		if ((homeScore - awayScore) > threshold)
		{
			return 2;
		}
		else if ((homeScore - awayScore) <= threshold && (homeScore - awayScore) > 0)
		{
			return 1;
		}
		else if ((homeScore - awayScore) == 0)
		{
			return 0;
		}
		else if ((homeScore - awayScore) < -threshold)
		{
			return -2;
		}
		else
		{
			return -1;
		}
		*/
		if ((homeScore - awayScore) > 0)
		{
			return 1;
		}
		else if ((homeScore - awayScore) == 0)
		{
			return 0;
		}
		else if ((homeScore - awayScore) < 0)
		{
			return -1;
		}
	}
};


struct Season
{
	string yearStart;
	Club* clu;
	Match* mat;
	int numClubs;
	int numMatches;
	string nameSeason;
};

struct League
{
	string name;
	Season* sea;
	int numSeason;
};

struct Program
{
	League* lea;
	int numLeagues;
};

string getRidString(string baseString, string subString, string repString)
{

	size_t index = 0;
	size_t preIndex = -1;
	while (preIndex != index)
	{
		preIndex = index;
		index = baseString.find(subString, index);

		if (index <= baseString.length())
		{
			baseString.replace(index, subString.length(), repString);
			//cout << index << endl;
		}
		if (index == 0)
		{
			preIndex = index;
		}
	}


	//cout << "yeah:	"<< baseString << endl;
	return baseString;
}


//Create players traits file
void createPlayerFiles(string folder)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(folder+"/clubs.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
		exit(1);
	}
	while (!inFile.eof())
	{
		string clubName;
		getline(inFile, clubName);
		cout << clubName << endl;
		outFile.open(folder+"/Players/" + clubName + ".txt");
		outFile << " ";
		cout << clubName << " created" << endl;
		outFile.close();
	}
	inFile.close();
}

//Adjust playerstrait files
void adjust(string folder)
{
	ifstream inFile, inFile1;
	ofstream outFile;
	inFile.open(folder + "/clubs.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
		exit(1);
	}
	while (!inFile.eof())
	{
		string clubName, line, position, overall, bigline;
		getline(inFile, clubName);
		inFile1.open(folder+ "/Players/" + clubName + ".txt");
		while (!inFile1.eof())
		{
			inFile1 >> line;
			
			bigline += "\n" + line + "	";
			getline(inFile1, line);
			//cout << line << endl;
			bigline += line;
		}
		inFile1.close();
		bigline = getRidString(bigline, "Yes", "");
		bigline = getRidString(bigline, "No", "");
		//cout << bigline;
		//outFile.close();
		outFile.open(folder+"/Players/" + clubName + ".txt");
		if (!outFile)
		{
			cout << endl << endl << endl;
		}
		outFile << bigline;
		outFile.close();
	}
	inFile.close();
}

//Input players traits
void playersTrait(string folder)
{
	ifstream inFile, inFile1;
	ofstream outFile;
	inFile.open(folder+"/clubs.txt");
	if (!inFile)
	{
		cout << "Error" << endl;
		exit(1);
	}
	while (!inFile.eof())
	{
		string clubName, line, position, overall;
		getline(inFile, clubName);
		inFile1.open(folder+"/Players/" + clubName + ".txt");
		outFile.open(folder+"/PlayersTraits/" + clubName + "PlayersTraits.txt");
		while (!inFile1.eof())
		{

			getline(inFile1, line);
			cout << line << endl;
			cout << "Position (G or R): ";
			cin >> position;
			cout << "Overall: ";
			cin >> overall;
			outFile << line << "	" << position << "	" << overall << endl;
		}
		outFile.close();
		inFile1.close();
	}
	inFile.close();

}

//Create fixture and result file (fixtures.txt)
void fixture(string folder)
{
	cout << folder << "		There" << endl;
	string line, bigline = "";
	string *club = NULL;
	ifstream inFile;
	int teamNum = 0;
	inFile.open(folder + "/clubs.txt");
	string str;
	if (!inFile)
	{
		cout << "Error12" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			getline(inFile, str);
			teamNum++;
		}

		club = new string[teamNum];
		inFile.clear();
		inFile.seekg(0, ios::beg);
		teamNum = 0;
		while (!inFile.eof())
		{
			getline(inFile, str);
			club[teamNum] = str;
			teamNum++;
		}
	}
	inFile.close();
	inFile.open(folder + "/raw.txt");
	ofstream outFile;
	outFile.open(folder + "/fixtures.txt");
	int num = 1, num1 = 1;
	if (!inFile)
	{
		cout << "Error13" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			if (line.at(2) == ':')
			{
				bigline += "\n" + to_string(num1) + "	";
				getline(inFile, line);
				bigline = bigline + line + "	";
				getline(inFile, line);
				bigline = bigline + line + "	";
				getline(inFile, line);
				bigline = bigline + line + "	";
				getline(inFile, line);
				bigline = bigline + line;
				num1++;
			}
			else
			{
				bigline = bigline + "\n" + line;
			}
			num++;
		}

		//clubArray(club, folder);

		for (int i = 0; i < teamNum; i++)
		{
			bigline = getRidString(bigline, club[i], to_string(i));
			cout << club[i] << endl;
		}

		bigline = getRidString(bigline, "Report", "");
		bigline = getRidString(bigline, "		", "	");
		bigline = getRidString(bigline, ",", "");
		outFile << bigline;
	}
	inFile.close();
	outFile.close();
	delete[] club;
}
void createFixtureFiles(Program pro)
{
	for (int x = 0; x < pro.numLeagues; x++)
	{
		for (int y = 0; y < pro.lea[x].numSeason; y++)
		{
			string folder = pro.lea[x].name + pro.lea[x].sea[y].yearStart;
			cout << folder << endl;
			fixture(folder);
		}
	}
}


//Read in club data to club array
void teamInit(Club club[], string folder, int teamNum)
{
	ifstream inFile;
	inFile.open(folder + "/clubs.txt");
	string line;
	int num;
	if (!inFile)
	{
		cout << "Error" << endl;
	}
	else
	{
		num = 0;
		while (!inFile.eof())
		{
			getline(inFile, line);
			club[num].name = line;
			//cout << club[num].name << endl;
			num++;
		}
	}
	inFile.close();

	num = 0;
	int indexPlayer;
	while (num < teamNum)
	{
		indexPlayer = 0;
		int numPlayer = 0;
		inFile.open(folder + "/Players/" + club[num].name + ".txt");
		//cout << club[num].name << endl;
		if (!inFile)
		{
			cout << "Error2" << endl;
		}
		else
		{
			getline(inFile, line);
			while (!inFile.eof())
			{
				getline(inFile, line);
				numPlayer++;

			}
			numPlayer = numPlayer;
			inFile.clear();
			inFile.seekg(0, ios::beg);
			club[num].numPlayer = numPlayer;
			club[num].player = new string[numPlayer];
			club[num].trait = new int[numPlayer];
			for (int i = 0; i < 5; i++)
			{
				club[num].record[i] = 0;
			}
			getline(inFile, line);
			while (!inFile.eof())
			{
				getline(inFile, line);
				//cout << line << endl;
				club[num].player[indexPlayer] = line;
				indexPlayer++;
			}
		}
		inFile.close();
		num++;
	}
	num = 0;
	while (num < teamNum)
	{
		indexPlayer = 0;
		inFile.open(folder + "/PlayersTraits/" + club[num].name + "PlayersTraits.txt");
		if (!inFile)
		{
			cout << "Error1" << endl;
		}
		else
		{
			indexPlayer = 0;
			while (!inFile.eof())
			{
				inFile >> line;
				inFile >> line;
				inFile >> line;
				char ch[2];

				if (isdigit(line.at(0)))
				{
					ch[0] = line.at(0);
					ch[1] = line.at(1);
					club[num].trait[indexPlayer] = atoi(ch);
				}
				else
				{
					club[num].trait[indexPlayer] = -1;
				}
				indexPlayer++;
			}
		}
		num++;
		inFile.close();
	}

	for (int i = 0; i < teamNum; i++)
	{
		double avg = 0;
		int numPlayer = club[i].numPlayer;
		for (int x = 0; x < club[i].numPlayer; x++)
		{
			if (club[i].trait[x] != -1)
			{
				avg += club[i].trait[x];
			}
			else
			{
				numPlayer--;
			}
		}
		club[i].avgTrait = avg / numPlayer;
	}
}

//read match info with single array
//note: first line in the txt file should be a day
//note: check reresult.txt, last line
//readMatchesSingle return num of matches
int readMatchesSingle(string folder)
{
	ifstream inFile;
	inFile.open(folder + "/fixtures.txt");
	int numMatch = 0;
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
			inFile >> line;
			if (isdigit(line.at(0)))
			{
				inFile >> line;
				inFile >> line;
				inFile >> line;
				inFile >> line;
				inFile >> line;
				numMatch++;
			}
			else
			{
				getline(inFile, line);
			}
		}
	}
	return numMatch;
}

void readDataMatch(Match * matches, string folder, int numMatch)
{
	ifstream inFile;
	inFile.open(folder + "/clubs.txt");
	string line;
	int num = 0;
	string* clubName = NULL;
	int teamNum = 0;

	string str;
	if (!inFile)
	{
		cout << "Error12" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			getline(inFile, str);
			teamNum++;
		}

		clubName = new string[teamNum];
		inFile.clear();
		inFile.seekg(0, ios::beg);
		teamNum = 0;
		while (!inFile.eof())
		{
			getline(inFile, str);
			clubName[teamNum] = str;
			teamNum++;
		}
	}
	inFile.close();

	inFile.open(folder + "/fixtures.txt");
	
	while (!inFile.eof() && num < numMatch)
	{
		inFile >> line;
		//cout << line << endl;
		if (isdigit(line.at(0)))
		{
			matches[num].index = stoi(line);
			inFile >> line;
			matches[num].away = stoi(line);
			//cout << line << endl;
			inFile >> line;
			//cout << line << endl;
			matches[num].result = line;
			inFile >> line;
			//cout << line << endl;
			matches[num].home = stoi(line);
			inFile >> line;
			inFile >> line;
			matches[num].attendance = stoi(line);
			//cout << "Attendance	"<<line << endl;
			matches[num].homeName = clubName[matches[num].home];
			matches[num].awayName = clubName[matches[num].away];
			num++;
		}
		else
		{
			getline(inFile, line);
		}

	}
	delete[] clubName;
}

void initPro(Program pro)
{
	ifstream inFile;
	int teamNum;
	for (int x = 0; x < pro.numLeagues; x++)
	{
		for (int y = 0; y < pro.lea[x].numSeason; y++)
		{
			teamNum = 0;
			string folder = pro.lea[x].name + pro.lea[x].sea[y].yearStart;
			cout << folder << endl;
			pro.lea[x].sea[y].numMatches = readMatchesSingle(folder);
			pro.lea[x].sea[y].mat = new Match[pro.lea[x].sea[y].numMatches];
			readDataMatch(pro.lea[x].sea[y].mat, folder, pro.lea[x].sea[y].numMatches);
			inFile.open(folder + "/clubs.txt");
			string str;
			if (!inFile)
			{
				cout << "Error11" << endl;
			}
			else
			{
				while (!inFile.eof())
				{
					getline(inFile, str);
					teamNum++;
				}

			}
			inFile.close();
			pro.lea[x].sea[y].clu = new Club[teamNum];
			pro.lea[x].sea[y].numClubs = teamNum;
			teamInit(pro.lea[x].sea[y].clu, folder, teamNum);
			readDataMatch(pro.lea[x].sea[y].mat, folder, pro.lea[x].sea[y].numMatches);
		}
	}

}

#endif