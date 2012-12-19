#include<iostream>
#include "quicksort.h"
using namespace std;

bool binarySearch(int array[], int start, int end, int mid, int search){
	if (search<array[start] || search > array[end]){
		cout<<"cannot find search number"<<endl;
		return false;
	}
	else if (array[mid] == search){
		cout<<"Search number found at "<<mid+1<<endl;
		return true;
	}
	else if (search < array[mid])
	{
		end = mid-1;
		mid = (start + end)/2;
		binarySearch(array, start, end, mid, search); 
	}
	else if (search > array[mid])
	{
		start = mid+1;
		mid = (start+end)/2;
		binarySearch(array, start, end, mid, search);
	}
	return false;
}

int main(void){
	int array[] = {2,5,4,6,1,25,8,10};
	int searchNumber = 0;
	cout<<"Enter a number"<<endl;
	cin>>searchNumber;
	int start = 0;
	int end = sizeof(array)/sizeof(int);
	int mid = (start + end)/2;
	quicksort(array, 0, end -1);
	printArray(array, end);
	binarySearch(array, start, end, mid, searchNumber);
}
