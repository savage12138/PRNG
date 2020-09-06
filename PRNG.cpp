/*
	Author: Yida Wang
	Last Date Modified: February 21st, 2020
	Description:
	This program compares system's build-in
	random number generation function with
	LFSR and LCG implementations of pseudo-
	random number generators.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;

double RAN_LFSR()
{
	// initialize a temp for shift logic;
	int temp;
	// initialize next least significant-bit
	int nlsb;
	// initialize a 25 bit integer with most significant bit is 1
	// use to delete the extra 1 after logical shift left by 1.
	int x25 = (int)pow(2, 24) - 1;
	// initialize LFSR
	// first initialized as a integer
	static int LFSR = (int)pow(2, 24) - 1;
	// convert LFSR to binary
	string LFSRb = bitset<24>(LFSR).to_string();
	// generate a 24 bit integer with most significant bit is 1
	// which is x^24
	int x24 = (int)pow(2, 23);

	// Logical AND LFSR with x^24 to get the value
	// at the 24th bit
	int LFSR24 = LFSR & x24;
	// determine the index is 1 or 0
	if (LFSR24 != 0)
	{
		LFSR24 = 1;
	}
	else
	{
		LFSR24 = 0;
	}

	// generate a 24 bit integer with 23rd bit is 1
	// which is x^23
	int x23 = (int)pow(2, 22);

	// Logical AND LFSR with x^23 to get the value
	// at the 23rd bit
	int LFSR23 = LFSR & x23;
	// determine the index is 1 or 0
	if (LFSR23 != 0)
	{
		LFSR23 = 1;
	}
	else
	{
		LFSR23 = 0;
	}

	// generate a 24 bit integer with 22nd bit is 1
	// which is x^22
	int x22 = (int)pow(2, 21);

	// Logical AND LFSR with x^23 to get the value
	// at the 22nd bit
	int LFSR22 = LFSR & x22;
	// determine the index is 1 or 0
	if (LFSR22 != 0)
	{
		LFSR22 = 1;
	}
	else
	{
		LFSR22 = 0;
	}

	// generate a 24 bit integer with 17th bit is 1
	// which is x^17
	int x17 = (int)pow(2, 16);

	// Logical AND LFSR with x^17 to get the value
	// at the 17th bit
	int LFSR17 = LFSR & x17;
	// determine the index is 1 or 0
	if (LFSR17 != 0)
	{
		LFSR17 = 1;
	}
	else
	{
		LFSR17 = 0;
	}

	// XORed 24, 23, 22, 17th bits
	if ((LFSR24 ^ LFSR23 ^ LFSR22 ^ LFSR17) == 1)
	{
		nlsb = 1;
	}
	else
	{
		nlsb = 0;
	}
	// shift left 1 bit.
	if (nlsb == 0)
	{
		temp = (LFSR << 1) & x25;
		LFSR = temp;
		// LFSRb = bitset<24>(LFSR).to_string();
		// display in binary
		// cout << "new LFSR in binary: " << LFSRb << endl;
	}
	else
	{
		temp = ((LFSR << 1) + 1) & x25;
		LFSR = temp;
		// LFSRb = bitset<24>(LFSR).to_string();
		// display in binary
		// cout << "new LFSR in binary: " << LFSRb << endl;
	}
	return (LFSR / pow(2, 24));
}

double RAN_LCG()
{
	// initialze variables
	int a = 1140671485;
	int c = 12820163;
	double m = pow(2, 24);
	static double LCG = pow(2, 24) - 1;
	// calculate LCG by plug in the formula
	LCG = fmod((a * LCG + c), m);
	return (LCG / pow(2, 24));
}
int calculationBuildIn(int n)
{
	// initialize variables
	int i;
	double sum = 0;
	double mean = 0;
	double stddev = 0;
	// initialize (xi - mean)^2 to calculate variance
	double sqDiff = 0;
	// initialize arrays 
	double buildInRand[10000];
	// generate random numbers
	for (i = 0; i < n; ++i)
	{
		buildInRand[i] = (double)rand() / RAND_MAX;
		// cout << buildInRand[i] << endl;
		sum += buildInRand[i];
	}
	mean = sum / n;
	cout << "mean of build-in function is: " << mean << endl;
	// calculate sqDiff then divide by n
	// to calculate variance
	for (i = 0; i < n; ++i)
	{
		sqDiff += (buildInRand[i] - mean) * (buildInRand[i] - mean);
	}
	// calculate standard deviation
	stddev = sqrt(sqDiff / n);
	cout << "std dev of build-in function is: " << stddev << endl;
	return 0;
}

int calculationLFSR(int n)
{
	// initialize variables
	int i;
	double sum = 0;
	double mean = 0;
	double stddev = 0;
	// initialize (xi - mean)^2 to calculate variance
	double sqDiff = 0;
	// initialize arrays 
	double LFSRarray[10000];
	// generate random numbers
	for (i = 0; i < n; ++i)
	{
		LFSRarray[i] = RAN_LFSR();
		// cout << LFSRarray[i] << endl;
		sum += LFSRarray[i];
	}
	mean = sum / n;
	cout << "mean of LFSR is: " << mean << endl;
	// calculate sqDiff then divide by n
	// to calculate variance
	for (i = 0; i < n; ++i)
	{
		sqDiff += (LFSRarray[i] - mean) * (LFSRarray[i] - mean);
	}
	// calculate standard deviation
	stddev = sqrt(sqDiff / n);
	cout << "std dev of LFSR is: " << stddev << endl;
	return 0;
}
int calculationLCG(int n)
{
	// initialize variables
	int i;
	double sum = 0;
	double mean = 0;
	double stddev = 0;
	// initialize (xi - mean)^2 to calculate variance
	double sqDiff = 0;
	// initialize arrays 
	double LCGarray[10000];
	// generate random numbers
	for (i = 0; i < n; ++i)
	{
		LCGarray[i] = RAN_LCG();
		// cout << LCGarray[i] << endl;
		sum += LCGarray[i];
	}
	mean = sum / n;
	cout << "mean of LCG is: " << mean << endl;
	// calculate sqDiff then divide by n
	// to calculate variance
	for (i = 0; i < n; ++i)
	{
		sqDiff += (LCGarray[i] - mean) * (LCGarray[i] - mean);
	}
	// calculate standard deviation
	stddev = sqrt(sqDiff / n);
	cout << "std dev of LCG is: " << stddev << endl;
	return 0;
}
int main()
{
	int n = 10000;
	cout << setprecision(6);
	calculationBuildIn(n);
	calculationLFSR(n);
	calculationLCG(n);
}
