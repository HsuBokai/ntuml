#include <iostream>
using namespace std;

int get_histogram(const int arr[], 
	const size_t len)
{
	int min=arr[0], max=arr[0];
	for(int i=0; i<len; ++i){
		if(arr[i] < min) min = arr[i];
		if(arr[i] > max) max = arr[i];
	}
	size_t range = max-min+1;
	int * const histogram = new int [range];
	for(int i=0; i<range; ++i){
		histogram[i] = 0;
	}
	for(int i=0; i<len; ++i){
		histogram[arr[i]-min]++;
	}
	for(int i=0; i<range; ++i){
		if(histogram[i] > 0) cout << min+i << "\t:\t" << histogram[i] << endl;
	}
	delete [] histogram;
	return 0;
}


