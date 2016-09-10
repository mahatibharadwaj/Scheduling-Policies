#include <iostream>
#include <fstream>
using namespace std;

string pID[100];
int arrivalTime[100];
int serviceTime[100];
int priority[100];
int waitTime[100];
int finishTime[100];
int TAT[100];
int size;

void readFile() {
	ifstream inputFile;
	inputFile.open("config.txt");
	int i = 0;
	while( inputFile.good() ) {
		inputFile >> pID[i];
		inputFile >> arrivalTime[i];
		inputFile >> serviceTime[i];
		inputFile >> priority[i];
		i++;
	}
	size = i - 1;
	inputFile.close();
}

void SJF() {
	
	//this method assumes that the process appear in increasing order of arrival time
	vector<int> q(size);
	for( int k = 1; k < size; k++ ) {
		if( arrivalTime[k] < finishTime[k-1] ) {
			q.push_back(serviceTime[k]);
		}
		int min = 10000;
		int ind = -1;
		for( int i = 0; i < k; i++ ) {
			if( q[i] < min ) {
				min = q[i];
				ind = i;
			}
		}

void FCFS() {
	//sorting arrival time using bubble sort
	for( int i = 0; i < size; i++ ) {
		for( int j = i+1; j < size-1; j++ ) {
			if( arrivalTime[j] > arrivalTime[j+1] ) {
				//whichever process arrived first
				int t = arrivalTime[j];
				arrivalTime[j] = arrivalTime[j+1];
				arrivalTime[j+1] = t;
				
				//swapping all necessary information
				t = priority[j];
				priority[j] = priority[j+1];
				priority[j+1] = t;
				
				t = serviceTime[j];
				serviceTime[j] = serviceTime[j+1];
				serviceTime[j+1] = t;
				
				string pid = pID[j];
				pID[j] = pID[j+1];
				pID[j+1] = pid;
			}
			else if( arrivalTime[j] == arrivalTime[j+1] ) {
				//in case 2 processes have the same arrival time, they are scheduled according to their priority
				if( priority[j] < priority[j+1] ) {
					int t = arrivalTime[j];
				arrivalTime[j] = arrivalTime[j+1];
				arrivalTime[j+1] = t;
				
				t = priority[j];
				priority[j] = priority[j+1];
				priority[j+1] = t;
				
				t = serviceTime[j];
				serviceTime[j] = serviceTime[j+1];
				serviceTime[j+1] = t;
				
				string pid = pID[j];
				pID[j] = pID[j+1];
				pID[j+1] = pid;
				}
			}
		}
	}
}

void assign() {
	
	//setting finish times and wait times;
	//it is assumed that the first process arrives at time 0 and not some other instant
	finishTime[0] = serviceTime[0];
	waitTime[0] = 0;
	TAT[0] = serviceTime[0];
	for( int i = 1; i < size; i++ ) {
		finishTime[i] = finishTime[i-1] + serviceTime[i];
		waitTime[i] = finishTime[i-1] - arrivalTime[i];
		if( waitTime[i] < 0 )
			waitTime[i] = 0;
		TAT[i] = finishTime[i] - arrivalTime[i];
	}
}

void writeFile() {
	ofstream outFile;
	outFile.open("Output.txt");
	outFile << "Process ID 	Arrival Time 	Service Time 	Priority 	Finish Time 	Turn around Time    Total Wait Time" << endl;
	for( int i = 0; i < size; i++ ) {
		cout << i << " ";
		outFile << pID[i] << " 		" << arrivalTime[i] << " 		" << serviceTime[i] << " 		" << priority[i] << " 		" << finishTime[i] << " 		" << TAT[i] << "		 	" << waitTime[i] << endl;
	}
}

int main() {
	readFile();
	FCFS();
	assign();
	writeFile();
	return 0;
}
