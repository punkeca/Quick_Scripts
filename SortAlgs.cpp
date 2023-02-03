#include <iostream>
#include <ctime>
#include <string>
#include <array>
#include <bits/stdc++.h>
using namespace std;
#define SIZE 1000

void bubbleSort(string *arr, int size){ //compares with neighbor and swaps if necessary n times.
	for(int i=0; i<size; i++){
		for(int j=0; j<size-1-i; j++){ // size-i because for each i the last part is at least +1 more ordered.
			if(arr[j+1] < arr[j] ){
				swap(arr[j+1], arr[j]); //from std library
			}
		}
	}
} //end bubbleSort

void selectionSort(string *arr, int size){ //finds the smallest element and sends it to front
	int minI;
	for(int i=0; i<size-1;i++){
		minI = i;
		for(int j = i+1; j<size; j++){
			if(arr[minI] > arr[j]) minI = j; //gets the smallest element position
		}
	swap(arr[minI], arr[i]);
	}
}

void insertionSort(string *arr, int size){
int j;
string aux;
	for(int i = 1; i < size; i++){
		aux = arr[i];
		for(j = i-1; (j >= 0) && arr[j] > aux; j--) //swaps j+i with j until i elem is bigger than j elem
			swap(arr[j+1], arr[j]);
		arr[j+1] = aux;
	}
}

void shellSort(string *arr, int size){
int j, h{size/2};
string aux;
	while( h >= 1){
		for(int i = 1; i<size; i++){
			aux = arr[i];
			for(j = i-h; (j >= 0) && (arr[j] > aux); j = j-h) //uses h instead of 1
				swap(arr[j+h], arr[j]);

			arr[j+h] = aux;
		}
		h = h/2; //important! divides by 2
	}
}

void mergeJoin(string *arr, string *aux, int beg, int middle, int end){
	int now, leftEnd, size;
	now = beg;
	leftEnd = middle-1;
	size = end - beg +1;

	while((beg <= leftEnd) && (middle <= end)){
		if(arr[beg] <= arr[middle]) //transfers first half or second half
			aux[now++] = arr[beg++];
		else
			aux[now++] = arr[middle++];
	}

	while(beg <= leftEnd)
		aux[now++] = arr[beg++];

	while(middle <= end)
		aux[now++] = arr[middle++];

	for(int i=0;i<size;i++){ //sets origin array
		arr[end] = aux[end];
		end--;
	}
}

void mergePartition(string *arr, string *aux, int beg, int end){
	int middle;
	if (end > beg){
			middle = (end+beg) /2;
			mergePartition(arr,aux,beg,middle);
			mergePartition(arr,aux,middle+1, end);
			mergeJoin(arr,aux, beg, middle+1, end);

	}
}

void mergeSort(string *arr, int size){
	string aux[size];
	mergePartition(arr,aux,0,size-1);
}


int quickPartition(string *arr, int beg, int end){
	string pivot = arr[end];
	int i = beg;
	for(int j = beg; j < end; j++){
		if(pivot >= arr[j]){
			swap(arr[i++], arr[j]);
		}
	}
	swap(arr[i], arr[end]);
	return i;
}

void quickSort(string *arr, int beg, int end){
	int middle;
	if(beg<end){
		middle = quickPartition(arr,beg,end);
		quickSort(arr, beg, middle-1);
		quickSort(arr, middle+1, end);
	}
}


void printArray(string *arr, int size){
	for(int i=0; i<size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main()
{
	fstream file;
	string word,filename {"aurelio40000.txt"}, arr[SIZE];
	int iTime, fTime, msTime;

	file.open(filename.c_str());

	for(int i=0; i<SIZE; i++){
		file >> word;
		arr[i] = word;
	}

	iTime = (int) clock();
	//bubbleSort(arr,SIZE);
	//selectionSort(arr, SIZE);
	//insertionSort(arr, SIZE);
	//shellSort(arr, SIZE);
	//mergeSort(arr, SIZE);
	//quickSort(arr, 0, SIZE);
	fTime = (int) clock();
	msTime = ((fTime - iTime)*1000/CLOCKS_PER_SEC);
	cout << msTime << endl;

	//printArray(arr, SIZE);
	file.close();
	return 0;
}
