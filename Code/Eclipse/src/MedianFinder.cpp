//============================================================================
// Name        : MedianFinder.cpp
// Author      : Nathan Perkins & Lachlan Cesca
// Version     :
// Copyright   : No Copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

bool testBruteForce();
int bruteForceMedian(int A[],int size);
int median(int A[],int size);
int ceilingDiv(int num, int div);
int select(int A[], int l, int m, int h);
int partition(int A[],int l, int h);
bool testMedian();

int main(){
	bool checkBrute = testBruteForce();
	bool checkMedian = testMedian();
    return 0;
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
	int evenMed = 6;
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

