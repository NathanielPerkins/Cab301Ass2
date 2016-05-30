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

long long BF_STEPS = 0;
long long M_STEPS = 0;
double BF_TIME = 0.0;
double M_TIME = 0.0;

void testBruteForce();
int bruteForceMedian(int A[],int size);
int bruteForceMedianCLK(int A[],int size);
int ceilingDiv(int num, int div);
int median(int A[],int size);
int select(int A[], int l, int m, int h);
int partition(int A[],int l, int h);
int medianCLK(int A[],int size);
int selectCLK(int A[], int l, int m, int h);
int partitionCLK(int A[],int l, int h);
void testMedian();
vector<int> randomMedArray(int A[],int size);
void checkAll();
bool SaveData(double time,long long n, long long steps,string filename);
void testing();

int main(){
	testing();
    return 0;
}
//WORK IN PROGRESS
void testing(){
	/** \Main function to find comparison of BF and Median method, saving
	 *  data to csv files with following data
	 *  Array size, steps taken, time taken
	 */
	string bruteFile = "bruteForceMedianData.csv";
	string medianFile = "medianData.csv";

	clock_t start; //to time individual array checks
	clock_t total; //total time taken for testing function
	const int REPEAT = 50; //number of times to repeat
	const int MAX_ITERATION = 100000; //max array size
	int inc = 10;
	total = clock();
	cout<<"BEGGINNING TESTING OF BOTH METHODS"<<endl;
	cout<<"Iteration: "<<MAX_ITERATION<<endl;
	cout<<"Repeated:  "<<REPEAT<<endl;

    cout<<"\nTesting currently in progress!"<<endl;

	for (long i=10; i<=MAX_ITERATION;i+=inc){
		srand(time(NULL)); //reset each iteration in case repeating values
		BF_STEPS = 0; //Reset global variables for this iteration
		M_STEPS = 0;
		BF_TIME = 0.0;
		M_TIME = 0.0;

		for (int j=0; j<REPEAT;j++){ //to take average results
			int A[i]; //allocate new array
			int B[i]; //Copy to hold A
			//median algorithm partially sorts the array, so generate new
			//random instance each time
			vector<int> med = randomMedArray(A,i);
			for (int k=0;k<i;k++){
				B[k] = A[k];
			}
			start = clock();
			//check brute force first as median changes the array, only checking time
			int check = 0;
			try{
				check = bruteForceMedianCLK(A,i);
				if (check != med[0]){ //med[0] = BF median value
					throw;
				}
			}
			catch(...){
				cout<<"DEBUGGING: Brute Force Median Method failed to return correct median"<<endl;
				cout<<"Iteration (i,j):      "<<i<<j<<endl;
				cout<<"Correct median value: "<< med[0]<<endl;
				cout<<"BFM Method value:     "<< check<<endl;
			}
			BF_TIME += (clock() - start)/(double)CLOCKS_PER_SEC;

			start = clock();
			//check Median
			try{
				check = medianCLK(A,i);
				if (check != med[1]){ //med[1] = median method value
					throw;
				}
			}
			catch(...){
				cout<<"DEBUGGING: Median Method failed to return correct median"<<endl;
				cout<<"Iteration (i,j):      "<<i<<j<<endl;
				cout<<"Correct median value: "<< med[1]<<endl;
				cout<<"Median Method value:  "<< check<<endl;
			}

			M_TIME += (clock() - start)/(double)CLOCKS_PER_SEC;

			//Now check computation steps
			try{
				check = bruteForceMedian(B,i);
				if (check != med[0]){ //med[0] = BF median value
					throw;
				}
			}
			catch(...){
				cout<<"DEBUGGING: Brute Force Median Method failed to return correct median"<<endl;
				cout<<"Iteration (i,j):      "<<i<<j<<endl;
				cout<<"Correct median value: "<< med[0]<<endl;
				cout<<"BFM Method value:     "<< check<<endl;
			}
			BF_TIME += (clock() - start)/(double)CLOCKS_PER_SEC;

			//check Median
			try{
				check = median(B,i);
				if (check != med[1]){ //med[1] = median method value
					throw;
				}
			}
			catch(...){
				cout<<"DEBUGGING: Median Method failed to return correct median"<<endl;
				cout<<"Iteration (i,j):      "<<i<<j<<endl;
				cout<<"Correct median value: "<< med[1]<<endl;
				cout<<"Median Method value:  "<< check<<endl;
			}
		}

		BF_STEPS /= REPEAT; //Average the values
		M_STEPS /= REPEAT;
		BF_TIME /= (double)REPEAT;
		M_TIME /= (double)REPEAT;
		SaveData(BF_TIME,i,BF_STEPS,bruteFile.c_str());
		SaveData(M_TIME,i,M_STEPS,medianFile.c_str());
	}
	cout<<"FINISHED"<<endl;
	cout<<"Total Time taken: "<< (clock()-total)/(double)CLOCKS_PER_SEC <<"s"<<endl;
}
void checkAll(){
	//Calls both check functions and ensures any changes still results in working functions
	testBruteForce();
	testMedian();
}
bool SaveData(double time,long long n, long long steps,string filename){
	/** \Saves all the data to a csv file
	 *  \param time floating point value
	 * 	\param n integer number
	 * 	\param steps integer number
	 * 	\param filename string
	 * 	\return bool True if data saved and stored, False otherwise
	 */
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
	/** \Finds the median of an array using quicksort functionality
	 *  \param A char array to find the median of
	 *  \param size size of A
	 *  \return median of A
	 */
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
	int pivotLoc = l;
	for (int j = l+1;j<=h;j++){
		M_STEPS++; //Increments every array comparison
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
int medianCLK(int A[],int size){
	/** \Finds the median of an array using quicksort functionality
	 *  \param A char array to find the median of
	 *  \param size size of A
	 *  \return median of A
	 */
	if (size == 1){
		return A[0];
	}
	else {
		return select(A,0,size/2,size-1);
	}
}
int selectCLK(int A[],int l, int m, int h){
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
int partitionCLK(int A[],int l, int h){
	int pivotVal = A[l];
	int pivotLoc = l;
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
void testBruteForce(){
	/** \ Tests the potential cases of the BruteForceMedian algorithm
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

}
void testMedian(){
	/** \ Tests the potential cases of the Median algorithm
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

}
vector<int> randomMedArray(int A[],int size){
	/** \ Builds an array of random elements to a given size, returning the median of the array
	 *  \param A[] array to generate by reference
	 *  \param size size of A[]
	 *  \returns vector<int> where [0] = median for bruteforce
	 *  						   [1] = median for Median method
	 *  						   [0] = [1] if size is odd
	 */

	//If Even
	vector<int> median;
	if (size%2 == 0){
		int start = rand()%10+1;
		A[0] = start;
		for (int i=1;i<size;i++){
			A[i] = rand()%10+A[i-1];
		}
		//10 element array returns A[4] and A[5] as the possible median solutions
		median.push_back(A[size/2 - 1]);
		median.push_back(A[size/2]);
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
		for (int i=1;i<size;i++){
			A[i] = rand()%10+A[i-1];
		}
		median.push_back(A[size/2]);
		median.push_back(A[size/2]);
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
	/** \Finds the median value of an array
	 *  \param A char array to find median of
	 *  \param size int size of A
	 *  \return median of A
	 */
	int k = ceilingDiv(size,2);
	for (int i = 0;i<size;i++){
		int numSmaller = 0;
		int numEqual = 0;
		for (int j = 0;j<size;j++){
			BF_STEPS++; //Every array comparison, similar to Median method
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
int bruteForceMedianCLK(int A[], int size){
	/** \Finds the median value of an array
	 *  \param A char array to find median of
	 *  \param size int size of A
	 *  \return median of A
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
	/** \Finds the integer ceiling division of two numbers
	 *  \param num integer numerator of division
	 *  \param div integer divisor of division
	 *  \return int ceiling(num/div)
	 */
	if (num%div == 0){
		return num/div;
	}
	else {return num/div + 1;}
}

