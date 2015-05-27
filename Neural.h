#ifndef NEURAL_H
#define NEURAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

const int numStatistic = 3;//number of data on one l
const int layer = 7;
int neuron[layer] = { 2,2, 2,2,2, 2, 1 };//
const int totalNeuron = 13;   //
const int numWeight = 22;  //
double weight[numWeight];
double preWeight[numWeight];
double delWeight[numWeight];
double threshold[totalNeuron];
double delThres[totalNeuron];
double errorGra[totalNeuron];
double wxValue[totalNeuron];
/*
double saveWeight[380][numWeight];
double saveThre[380][totalNeuron];
double saveErrors[380];
*/
double learning = 0.1;

double** readArray(int& num);
double** readArray1(int& num);
void layerOutput(double *, int layer);
void wx(int layer, int, int, double input[]);
int getWeightIndex(int layer, int node1, int node2);
void init();
int readArray1(double*& arr, double*& arr1, double*& arr2);
double update(int layer, double[]);
void fullUpdate();
void smallestVa(double& smallest);
void test();

int neural2()
{
	double** input = NULL;										//totalNeuron + 1 elements, each for each neuron and last for dOutput
	double error = 0, sumError = 1, preSumErr = 0;
	//double errorA[4];
	//int num;
	int number = 0;
	input = readArray1(number);
	int index = 0;
	int epoch = 0;
	double smallest = 0;
	//init();


	int no = 1;
	for (int x = 0; x < number; x++)
	{
		cout << no << " ";
		no++;
		//errorA[x] = 0;
		//input[x][0] = (input[x][0] + 12.5136) / (12.5136 + 11.7549);
		//input[x][totalNeuron] = (input[x][totalNeuron] + 2) / (4);
		//input[x][1] = (input[x][1] + 9) / (8+9);
		for (int y = 0; y < 2; y++)
		{
			cout << input[x][y] << " ";
		}
		cout << input[x][totalNeuron];
		cout << endl;
	}

	while (sumError > 0.00001)
	{
		init();
		while (learning > 0.00000001 && sumError > 0.00001 && learning < 100000  )
			//while (sumError > 0.00001 && learning > 0.00000001 )
		{

			epoch++;
			sumError = 0;
			error = 0;
			for (int index = 0; index < number; index++)
			{
				/*
				for (int i = 0; i < numWeight; i++)
				{
				cout << weight[i] << " ";
				}
				cout << endl;
				*/
				/*
				for (int n = 0; n < numWeight; n++)
				{
				saveWeight[index][n] = weight[n];
				}

				for (int n = 0; n < totalNeuron; n++)
				{
				saveThre[index][n] = threshold[n];
				}
				*/
				//cout << input[index][0] << " " << input[index][1] << endl;
				for (int i = 1; i < layer; i++)
				{
					layerOutput(input[index], i);
				}


				error = input[index][totalNeuron] - input[index][totalNeuron - 1];

				//saveErrors[index] = error;
				//errorA[index] = error*error;
				sumError += error*error;
				//sumError += abs(error);
				//cout << errorA[index] << endl;

				
				for (int i = layer - 1; i > 0; i--)
				{
					update(i, input[index]);
				}
			
				fullUpdate();

				//cout << error << endl;
			}

			if (epoch == 1)
			{
				preSumErr = sumError;
				smallest = sumError;
			}
			if (sumError > (preSumErr))
			{
				learning *= 0.85;
			}
			else
			{
				learning *= 1.005;
			}
			preSumErr = sumError;

			if (smallest > sumError)
			{
				smallest = sumError;
				smallestVa(sumError);
			}
			cout << sumError << " " << learning << " " << smallest << " " << number << " " << epoch << endl;
		}
	}
	double *ans;
	ans = new double[totalNeuron + 1];

	/*
	layerOutput(input[0], 1);
	layerOutput(input[0], 2);
	cout << input[0][0] << " " << input[0][1] << " " << input[0][totalNeuron] << " " << input[0][totalNeuron-1] << endl;
	*/
	//test();

	while (true)
	{
		cout << "done" << endl;
		cin >> ans[0];
		cin >> ans[1];
		for (int i = 1; i < layer; i++)
		{
			layerOutput(ans, i);
		}
		cout << ans[totalNeuron - 1] <<  endl;
	}


	return 0;
}

void fullUpdate()
{
	//cout << weight[6] << endl;
	for (int i = 0; i < numWeight; i++)
	{
		weight[i] += delWeight[i];
		//cout << setprecision(3) << weight[i] << " ";
	}
	//cout << endl;
	for (int i = 0; i < totalNeuron; i++)
	{
		threshold[i] += delThres[i];
		//cout << setprecision(3) << threshold[i] << " ";
	}
	//cout << endl;
}

double update(int layer, double input[])
{
	double graWeight = 0;
	int first = 0, second = 0, middle = 0, third = 0;
	int numNeuron = neuron[1];
	for (int i = 0; i < layer - 1; i++)
	{
		first += neuron[i];
	}
	for (int i = 0; i < layer; i++)
	{
		middle += neuron[i];
	}
	for (int i = 0; i < layer + 1; i++)
	{
		second += neuron[i];
	}
	for (int i = 0; i < layer + 2; i++)
	{
		third += neuron[i];
	}
	
	//cout << input[totalNeuron] << " " << input[totalNeuron - 1] << endl;
	double error = input[totalNeuron] - input[totalNeuron - 1];
	//cout << "yeah " << error << endl;
	for (int x = middle; x < second; x++)
	{
		graWeight = 0;
		if (x == totalNeuron - 1)
		{
			errorGra[x] = input[totalNeuron - 1] * (1 - input[totalNeuron - 1])*error;
			//cout << " a" << input[totalNeuron - 1] << endl;
		}
		else
		{
			for (int y = second; y < third; y++)
			{
				int index = getWeightIndex(layer + 1, x, y);
				graWeight += errorGra[y] * weight[index];
				//cout << "gra: " << x << "	" << y << " " << index << endl;
				//cout << "graWeight" << y << " " << index << " " << graWeight<< endl;
			}
			errorGra[x] = input[x] * (1 - input[x])*graWeight;
		}
		//cout << "Gra" << x << " " << errorGra[x] << " " << graWeight << " " << input[x] << endl;
		
		for (int y = first; y < middle; y++)
		{
			//cout << x << " " << y << endl;
			int index = getWeightIndex(layer, y, x);
			delWeight[index] = learning * input[y] * errorGra[x];
			delThres[index] = learning * -1 * errorGra[y];
			//cout << "delweight"<<index<< " " << delWeight[index] << endl;

		}

		delThres[x] = learning * -1 * errorGra[x];
		//cout << "Delthres "<< delThres[x] << endl;
		
	}
	return error;
}

double** readArray(int& num)
{
	double** input = NULL;;
	ifstream inFile;
	inFile.open("test1.txt");
	string line;
	num = 0;
	if (!inFile)
	{
		cout << "Error";
	}
	else
	{
		//getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			num++;
		}

		input = new double*[num];
		for (int i = 0; i < num; i++)
		{
			input[i] = new double[totalNeuron + 1];
		}
		int num1 = 0;
		inFile.clear();
		inFile.seekg(0, ios::beg);

		//getline(inFile, line);
		while (!inFile.eof())
		{
			//inFile >> line;
			for (int i = 0; i < neuron[0]; i++)
			{
				inFile >> line;
				input[num1][i] = stod(line);
				//cout << input[num1][i] << "	";
			}
			inFile >> line;
			input[num1][totalNeuron] = stod(line);
			//cout << endl;
			num1++;
		}
	}
	inFile.close();
	return input;
}

double** readArray1(int& num)
{
	double** input = NULL;;
	ifstream inFile;
	inFile.open("training.txt");
	string line;
	num = 0;
	if (!inFile)
	{
		cout << "Error";
	}
	else
	{
		getline(inFile, line);
		while (!inFile.eof())
		{
			getline(inFile, line);
			num++;
		}

		input = new double*[num];
		for (int i = 0; i < num; i++)
		{
			input[i] = new double[totalNeuron + 1];
		}
		int num1 = 0;
		inFile.clear();
		inFile.seekg(0, ios::beg);

		getline(inFile, line);
		while (!inFile.eof())
		{
			inFile >> line;
			for (int i = 0; i < neuron[0]; i++)
			{
				inFile >> line;
				input[num1][i] = stod(line);
				//cout << input[num1][i] << "	";
			}
			inFile >> line;
			input[num1][totalNeuron] = stod(line);
			//cout << endl;
			num1++;
		}
	}
	inFile.close();
	return input;
}


void layerOutput(double* input, int layer)
{

	double sum = 0;
	int first = 0, second = 0, middle = 0;
	int numNeuron = neuron[1];
	for (int i = 0; i < layer - 1; i++)
	{
		first += neuron[i];
	}
	for (int i = 0; i < layer; i++)
	{
		middle += neuron[i];
	}
	for (int i = 0; i < layer + 1; i++)
	{
		second += neuron[i];
	}


	for (int i = middle; i < second; i++)
	{
		sum = 0;
		for (int x = first; x < middle; x++)
		{
			//cout << "first " << x << endl;
			wx(layer, x, i, input);
			sum += wxValue[x];
		}
		//cout << sum << endl;
		sum -= threshold[i];
		//cout << "y"<< i<<" " << 1 / (1 + exp(-sum)) << endl;
		input[i] = 1 / (1 + exp(-sum));
	}
	//hidOutput = new double[numNeuron];
}

void wx(int layer, int node1, int node2, double input[])
{

	int result = 0;
	double wx[totalNeuron];
	int first = 0, second = 0;
	int index1 = node1, index2 = node2;
	for (int i = 0; i < layer - 1; i++)
	{
		first += neuron[i];
	}
	for (int i = 0; i < layer; i++)
	{
		second += neuron[i];
	}
	int index = getWeightIndex(layer, node1, node2);
	//cout << node1 << " " << node2 << " " << index << endl;
	wxValue[node1] = weight[index] * input[node1];
	//cout << wxValue[node1] << " " << weight[index] << " " << input[node1] << endl;
}

int getWeightIndex(int layer, int node1, int node2)
{
	int index1 = node1, index2 = node2;
	int start;
	if (layer == 1)
	{
		start = 0;
	}
	else
	{
		start = 0;
	}
	for (int i = 0; i < layer; i++)
	{
		start += neuron[i] * neuron[i-1];
		index2 -= neuron[i];
	}
	for (int i = 0; i < layer - 1; i++)
	{
		index1 -= neuron[i];
	}
	start += index2;
	int index = index1*neuron[layer];
	//cout << index << endl;
	index += start;
	//cout << node1 << " " << node2 << " " << start << " " << index << " " << layer << endl;
	return index;
}

void init()
{

	srand(time(0));
	for (int i = 0; i < numWeight; i++)
	{
		delWeight[i] = 0;
		weight[i] = (rand() % 3 - 1.5);
		//weight[i] = rand();
		//weight[i] = 0.5;
		//weight[i] = 0.1 * i;
	}
	srand(time(0));
	for (int i = 0; i < totalNeuron; i++)
	{
		errorGra[i] = 0;
		delThres[i] = 0;
		threshold[i] = (rand() % 3 - 1.5);
		//threshold[i] = rand();
		//threshold[i] = 0.5;
		//threshold[i] = 0.2* i;
	}

	learning = 0.1;
	/*
	weight[0] = 0.5;
	weight[1] = 0.9;
	weight[2] = 0.4;
	weight[3] = 1.0;
	weight[4] = -1.2;
	weight[5] = 1.1;
	threshold[0] = 0;
	threshold[1] = 0;
	threshold[2] = 0.8;
	threshold[3] = -0.1;
	threshold[4] = 0.3;
	*/
}

void smallestVa(double& smallest)
{
	ofstream outFile;
	outFile.open("smallest.txt");
	outFile << smallest << endl;
	/*
	for (int i = 0; i < num; i++)
	{
	outFile << saveErrors[i] << " ";
	}
	outFile << endl;
	for (int l = 0; l < num; l++)
	{
	for (int k = 0; k < numWeight; k++)
	{
	outFile << saveWeight[l][k] << "	";
	}
	outFile << endl;
	}
	for (int l = 0; l < num; l++)
	{
	for (int k = 0; k < totalNeuron; k++)
	{
	outFile << saveThre[l][k] << "	";
	}
	outFile << endl;
	}
	*/
	for (int i = 0; i < numWeight; i++)
	{
		outFile << weight[i] << "	";
	}
	outFile << endl;

	for (int i = 0; i < totalNeuron; i++)
	{
		outFile << threshold[i] << "	";
	}
	outFile << endl;
	outFile.close();
}

void test()
{
	ifstream inFile;
	inFile.open("test.txt");
	double num;
	while (!inFile.eof())
	{
		cout << "Iter" << endl;
		for (int i = 0; i < numWeight; i++)
		{
			inFile >> num;
			weight[i] = num;
		}
		for (int i = 0; i < totalNeuron; i++)
		{
			inFile >> num;
			threshold[i] = num;
		}
	}
}

#endif