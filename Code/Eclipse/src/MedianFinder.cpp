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

//function pointer examples for quick reference
void my_int_func(int x){
    cout<<x<<endl;
}
void my_int_func2(int x){
	cout<<2*x<<endl;
}
void funcP( void (*f)(int) ){
	f(2);
}

bool testBruteForce();
int bruteForceMedian(int array[],int size);
int median(int array[]);

int main(){
	bool check = testBruteForce();
    return 0;
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


int bruteForceMedian(int array[], int size){
	/*
	 * currently fails on the odd array
	 */
	int k = size/2;
	for (int i = 0;i<size;i++){
		int numSmaller = 0;
		int numEqual = 0;
		for (int j = 0;j<size;j++){
			if (array[j]<array[i]){
				numSmaller++;
			}
			else{
				if(array[i]==array[j]){
					numEqual++;
				}
			}
		}
		if ((numSmaller < k)&&(k <= (numSmaller+numEqual))){
			return array[i];
		}
	}
	return 0;
}

