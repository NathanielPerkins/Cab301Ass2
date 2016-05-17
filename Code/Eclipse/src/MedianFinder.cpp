//============================================================================
// Name        : MedianFinder.cpp
// Author      : Nathan Perkins & Lachlan Cesca
// Version     :
// Copyright   : No Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

using namespace std;

bool testBruteForce();
int bruteForceMedian(int A[],int size);
int median(int A[],int size);
int ceilingDiv(int num, int div);
int select(int A[], int l, int m, int h);
int partition(int A[],int l, int h);
bool testMedian();
vector<int> randomMedArray(int A[],int size);
void checkBoth();
bool SaveData(double time,int n, int steps,string filename);
void testing();

int main(){
	srand(time(NULL));
	int size = 11;
	int A[size];
    vector<int> med= randomMedArray(A,size);
    cout<<"Array A[] = ";
    for (int i=0;i<size;i++){
    	cout<<A[i]<< " ";
    }
    cout<<endl;
    cout<<"median values: ";
	for (unsigned int i=0;i<med.size();i++){
		cout<<med[i]<< " ";
	}
    return 0;
}
//WORK IN PROGRESS
void testing(){
	string bruteFile = "bruteForceMedianData.csv";
	string medianFile = "medianData.csv";

	int inc = 1;
	int count = 0;
	clock_t start;
	double time;
	int steps = 0;
	const int REPEAT = 100;
	const int MAX_ITERATION = 10000;
	for (int i=0; i<MAX_ITERATION;i+=inc){
		count++;
		if(count >= 9){
			inc *= 10;
			count = 0;
		}
		double timeAve = 0;
		int stepsAve = 0;
		time = 0;
		// get the average of REPEAT number of times
		for (int j=0;j<REPEAT;j++){
			int A[i];
			vector<int> med = randomMedArray(A,i);
			start = clock();
			int median = bruteForceMedian(A,i);

		}
	}
}
void checkBoth(){
	bool checkBrute = testBruteForce();
	bool checkMedian = testMedian(); //currently not working
}
bool SaveData(double time,int n, int steps,string filename){
	ofstream myfile;
	myfile.open(filename.c_str(),ios::app);
	if(myfile.is_open()){
		myfile<<n<<","<<steps<<","<<time<<"\n";
		myfile.close();
		return true;
	}
	return false;
}

int median(int A[],int size){
	if (size == 1){
		return A[0];
	}
	else {
		return select(A,0,size/2,size-1);
	}
}
int select(int A[],int l, int m, int h){
	int pos = partition(A,l,h);
	if (pos == m){
		return A[pos];
	}
	if (pos > m){
		return select(A,l,m,pos-1);
	}
	if (pos < m){
		return select(A,pos+1,m,h);
	}
	return 0;
}
int partition(int A[],int l, int h){
	int pivotVal = A[l];
	int pivotLoc = 1;
	for (int j = l+1;j<=h;j++){
		if (A[j]<pivotVal){
			pivotLoc++;
			int temp = A[pivotLoc];
			A[pivotLoc] = A[j];
			A[j] = temp;
		}
	}
	int temp = A[l];
	A[l] = A[pivotLoc];
	A[pivotLoc] = temp;
	return pivotLoc;
}
bool testBruteForce(){
	/* testBruteForce is a test driver for the brute force method. Testing individual cases
	 * Returns: True if all tests pass, Fail if any haven't.
	 */
	cout<<"Beginning testing of bruteForceMedian"<<endl;
	bool check = true;
	//setup tests
	int odd[] = {1,2,3,4,5,6,7,8,9,10,11}; //11 elements
	int oddSize = 11;
	int oddMed = 6;
	int even[] = {1,2,3,4,5,6,7,8,9,10}; //10 elements
	int evenSize = 10;
	int evenMed = 5;
	int unsortedEven[] = {3,2,1,5,6,8,9,10,6,2}; //10 elements
	int unsortedEMed = 5;
	int unsortedOdd[] = {3,2,1,5,6,8,9,10,6,2,5}; //11 elements
	int unsortedOMed = 5;
	int same[] = {1,1,1,1,1,1,1,1,1,1}; //10 elements
	int sameMed = 1;

	//run testing, set check = false if failed and print diagnostics
	int medValue = bruteForceMedian(odd,oddSize);
	if (medValue != oddMed){
		check = false;
		cout<<"odd failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"odd passed:"<<endl;

	medValue = bruteForceMedian(even,evenSize);
	if (medValue != evenMed){
		check = false;
		cout<<"Even failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"even passed:"<<endl;

	medValue = bruteForceMedian(unsortedEven,evenSize);
	if (medValue != unsortedEMed){
		check = false;
		cout<<"Unsorted Even failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Unsorted Even passed:"<<endl;

	medValue = bruteForceMedian(unsortedOdd,oddSize);
	if (medValue != unsortedOMed){
		check = false;
		cout<<"Unsorted Odd failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Unsorted Odd passed:"<<endl;

	medValue = bruteForceMedian(same,evenSize);
	if (medValue != sameMed){
		check = false;
		cout<<"Same failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Same passed:"<<endl;

	if (check) { cout<< "All tests have passed"<<endl;}
	else { cout<<"Some tests have failed"<<endl;}

	return check;
}
bool testMedian(){
	/* testMedian is a test driver for the median method. Testing individual cases
	 * Returns: True if all tests pass, Fail if any haven't.
	 */
	cout<<"Beginning testing of median"<<endl;
	bool check = true;
	//setup tests
	int odd[] = {1,2,3,4,5,6,7,8,9,10,11}; //11 elements
	int oddSize = 11;
	int oddMed = 6;
	int even[] = {1,2,3,4,5,6,7,8,9,10}; //10 elements
	int evenSize = 10;
	int evenMed = 6;//rightmost value of 2 median pair
	int unsortedEven[] = {3,2,1,5,6,8,9,10,6,2}; //10 elements
	int unsortedEMed = 6;
	int unsortedOdd[] = {3,2,1,5,6,8,9,10,6,2,5}; //11 elements
	int unsortedOMed = 5;
	int same[] = {1,1,1,1,1,1,1,1,1,1}; //10 elements
	int sameMed = 1;

	//run testing, set check = false if failed and print diagnostics
	int medValue = median(odd,oddSize);
	if (medValue != oddMed){
		check = false;
		cout<<"odd failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"odd passed:"<<endl;

	medValue = median(even,evenSize);
	if (medValue != evenMed){
		check = false;
		cout<<"Even failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"even passed:"<<endl;

	medValue = median(unsortedEven,evenSize);
	if (medValue != unsortedEMed){
		check = false;
		cout<<"Unsorted Even failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Unsorted Even passed:"<<endl;

	medValue = median(unsortedOdd,oddSize);
	if (medValue != unsortedOMed){
		check = false;
		cout<<"Unsorted Odd failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Unsorted Odd passed:"<<endl;

	medValue = median(same,evenSize);
	if (medValue != sameMed){
		check = false;
		cout<<"Same failed:"<<endl;
		cout<<"median = "<<medValue<<endl;
	}
	else cout<<"Same passed:"<<endl;

	if (check) { cout<< "All tests have passed"<<endl;}
	else { cout<<"Some tests have failed"<<endl;}

	return check;
}
vector<int> randomMedArray(int A[],int size){
	/*
	 * Builds an array of random elements to a given size,
	 * returning the median of the array
	 * A[]: array to generate
	 * size: size of A[]
	 * returns:
	 * vector<int>: returns median value in a vector, if size
	 * is even, it contains 2 values, corresponding to
	 * vec[0] = bruteForceMedian
	 * vec[1] = median
	 * If size is odd, only returns one value
	 */
	//If Even
	vector<int> median;
	if (size%2 == 0){
		int start = rand()%10+1;
		A[0] = start;
		cout<<"Generating Array: ";
		cout<<A[0]<<" ";
		for (int i=1;i<size;i++){
			A[i] = rand()%10+A[i-1];
			cout<<A[i]<<" ";
		}
		//10 element array returns A[4] and A[5] as the possible median solutions
		median.push_back(A[size/2 - 1]);
		median.push_back(A[size/2]);
		cout<<endl;
		for (int i=0;i<size;i++){ //randomize the array, median remains unchanged
			int index = rand()%size;
			int swap = A[i];
			A[i] = A[index];
			A[index] = swap;
		}

	}
	//If Odd
	else{
		int start = rand()%10+1;
		A[0] = start;
		cout<<"Generating Array: ";
		cout<<A[0]<<" ";
		for (int i=1;i<size;i++){
			A[i] = rand()%10+A[i-1];
			cout<<A[i]<<" ";
		}
		median.push_back(A[size/2]);
		cout<<endl;
		for (int i=0;i<size;i++){ //randomize the array, median remains unchanged
			int index = rand()%size;
			int swap = A[i];
			A[i] = A[index];
			A[index] = swap;
		}

	}
	return median;
}

int bruteForceMedian(int A[], int size){
	/*
	 * Finds the median of a given array
	 * int A[]: array of integers to find median of
	 * int size: integer size of A[]
	 * returns: Median value of A[]
	 *
	 * currently fails on the odd array
	 */
	int k = ceilingDiv(size,2);
	for (int i = 0;i<size;i++){
		int numSmaller = 0;
		int numEqual = 0;
		for (int j = 0;j<size;j++){
			if (A[j]<A[i]){
				numSmaller++;
			}
			else{
				if(A[i]==A[j]){
					numEqual++;
				}
			}
		}
		if ((numSmaller < k)&&(k <= (numSmaller+numEqual))){
			return A[i];
		}
	}
	return 0;
}
int ceilingDiv(int num, int div){
	if (num%div == 0){
		return num/div;
	}
	else {return num/div + 1;}
}

