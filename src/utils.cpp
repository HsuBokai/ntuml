#include <iostream>
#include <random> // for random_choose
using namespace std;

static random_device rd;

int random_choose(const vector<int>& arr){
	int n = arr.size();
	if(n==1) return arr[0];
	uniform_int_distribution<int> uni(0, n-1);
	return arr[ uni(rd) ];
}

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


