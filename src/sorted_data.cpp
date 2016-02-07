#include <algorithm> // for sort
#include <vector> // for data.h
using namespace std;

#include "utils.h"
#include "data.h"
#include "sorted_data.h"


SortedData::SortedData(const Data* d, const int& dim_th){
	int N = d->data_y.size();
	for(int i=0; i<N; ++i){
		if(d->data_y[i]==1) pos.push_back( d->data_x[i][dim_th] );
		else neg.push_back( d->data_x[i][dim_th] );
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
}


int SortedData::get_count_vector(vector<int>& count)
{	
	int p = pos.size(), n = neg.size();
	int i=0, j=0;
	int c = 0;
	int y = -1;
	while(i<p && j<n){
		int test;
		if(pos[i] < neg[j]){
			test = 1;
			i++;
		}
		else{
			test = -1;
			j++;
		}
		if(y!=test){
			count.push_back(c);
			y=-y;
			c=0;
		}
		c++;
	}
	if(c>0) count.push_back(c);
	if(i<p){
		if(c==0) count.push_back(0);
		count.push_back(p-i);
	}
	else{
		count.push_back(n-j);
	}


	return 0;
}



int SortedData::get_decision(
	const vector<int>& count, 
	int& e_in, 
	int& s, 
	double& theta)
{
	const int len = count.size();
	int pos_sum = count[0], neg_sum = 0;
	int pos_min = 0, neg_min = 0;
	for(int i=0; i<len; ++i){
		if(i%2==0){
			neg_sum += count[i];
			pos_sum -= count[i];
			if(pos_min > pos_sum) pos_min = pos_sum;
		}
		else{
			neg_sum -= count[i];
			pos_sum += count[i];
			if(neg_min > neg_sum) neg_min = neg_sum;
		}
	}
	//cout << neg_min << endl;
	//cout << pos_min << endl;
	vector<int> location_pos, location_neg;
	if(neg_min==0) location_neg.push_back(0);
	pos_sum = count[0];
	neg_sum = 0;
	for(int i=0; i<len; ++i){
		if(i%2==0){
			neg_sum += count[i];
			pos_sum -= count[i];
			if(pos_min == pos_sum) location_pos.push_back(i);
		}
		else{
			neg_sum -= count[i];
			pos_sum += count[i];
			if(neg_min == neg_sum) location_neg.push_back(i);
		}
		//cout << count[i] << ' '; 
	}
	//cout << endl;
	for(int i=1; i<len; ++i){
		if(i%2==0)pos_min += count[i];
		else neg_min += count[i];
	}

	double right, left;
	double epsilon = 0.01;
	int p = pos.size(), n = neg.size();
	if(pos_min <= neg_min){
		s = 1; // s
		int r = random_choose(location_pos);
		int sum = 0;
		for(int i=1; i<len && i<r; i+=2) sum += count[i];
		int right_index = sum; // right index
		sum = 0;
		for(int i=0; i<len && i<=r; i+=2) sum += count[i];
		int left_index = sum-1; // left index

		right = (right_index==p) ? neg[left_index]+epsilon :  pos[right_index];
		left = (left_index==-1) ? right-epsilon : neg[left_index];
		e_in = pos_min;
	}
	else{
		s = -1; // s
		int r = random_choose(location_neg);
		int sum = 0;
		for(int i=0; i<len && i<r; i+=2) sum += count[i];
		int right_index = sum; // right index
		sum = 0;
		for(int i=1; i<len && i<=r; i+=2) sum += count[i];
		int left_index = sum-1; // left index
		right = (right_index==n) ? pos[left_index]+epsilon :  neg[right_index];
		left = (left_index==-1) ? right-epsilon : pos[left_index];
		e_in = neg_min;
	}
	theta = (right + left)/2;
	return 0;
}


int SortedData::get_sorted_all(
	double * const sorted_all,
	int * const y_all)
{
	int p = pos.size(), n = neg.size();
	int i=0, j=0, k=0;
	while(i<p && j<n){
		if(pos[i] < neg[j]){
			y_all[k]=1;
			sorted_all[k++] = pos[i++];
		}
		else{
			y_all[k]=-1;
			sorted_all[k++] = neg[j++];
		}
	}
	while(i<p) {
		y_all[k]=1;
		sorted_all[k++] = pos[i++];
	}
	while(j<n){
		y_all[k]=-1;
		sorted_all[k++] = neg[j++];
	}
	return 0;
}


