#include <iostream>
#include <random> // for gen_data
#include <algorithm> // for sort
#include "data.h"
#include "utils.h"

std::random_device rd;

#define FLIP_PROB 0.2

int gen_data(int N, Data* d){
	//std::normal_distribution<double> normal(0.0, 1.0);
	std::uniform_real_distribution<double> uni(0.0, 1.0);
	for(int i=0; i<N; ++i){
		double x = uni(rd)*2-1;
		d->data_x.push_back( std::vector<double>(1,x) );
		int y = (x > 0) ? 1 : -1;
		y = (uni(rd) < FLIP_PROB) ? -y : y;
		d->data_y.push_back(y);
		//std::cout << x << '\t' << y << std::endl;
	}
	return 0;
}

int get_sorted_data(const Data* d,
	std::vector<double>& pos,
	std::vector<double>& neg)
{
	int N = d->data_y.size();
	for(int i=0; i<N; ++i){
		if(d->data_y[i]==1) pos.push_back( d->data_x[i][0] );
		else neg.push_back( d->data_x[i][0] );
	}
	std::sort(pos.begin(), pos.end());
	std::sort(neg.begin(), neg.end());
	return 0;
}

int get_count_vector(const std::vector<double>& pos, 
	const std::vector<double>& neg, 
	std::vector<int>& count)
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

int random_choose(const std::vector<int>& arr){
	int n = arr.size();
	if(n==1) return arr[0];
	std::uniform_int_distribution<int> uni(0, n-1);
	return arr[ uni(rd) ];
}

int get_min_err(const std::vector<int>& count, int ret[]){
	const int len = count.size();
	int pos=count[0], neg=0;
	int pos_min=0, neg_min=0;
	for(int i=0; i<len; ++i){
		if(i%2==0){
			neg += count[i];
			pos -= count[i];
			if(pos_min > pos) pos_min = pos;
		}
		else{
			neg -= count[i];
			pos += count[i];
			if(neg_min > neg) neg_min = neg;
		}
	}
	//std::cout << neg_min << std::endl;
	//std::cout << pos_min << std::endl;
	std::vector<int> location_pos, location_neg;
	if(neg_min==0) location_neg.push_back(0);
	pos=count[0];
	neg=0;
	for(int i=0; i<len; ++i){
		if(i%2==0){
			neg += count[i];
			pos -= count[i];
			if(pos_min == pos) location_pos.push_back(i);
		}
		else{
			neg -= count[i];
			pos += count[i];
			if(neg_min == neg) location_neg.push_back(i);
		}
		//std::cout << count[i] << ' '; 
	}
	//std::cout << std::endl;
	for(int i=1; i<len; ++i){
		if(i%2==0)pos_min += count[i];
		else neg_min += count[i];
	}
	if(pos_min <= neg_min){
		ret[0] = 1; // s
		int r = random_choose(location_pos);
		int sum = 0;
		for(int i=1; i<len && i<r; i+=2) sum += count[i];
		ret[1] = sum; // right index
		sum = 0;
		for(int i=0; i<len && i<=r; i+=2) sum += count[i];
		ret[2] = sum-1; // left index
		ret[3] = pos_min;
	}
	else{
		ret[0] = -1; // s
		int r = random_choose(location_neg);
		int sum = 0;
		for(int i=0; i<len && i<r; i+=2) sum += count[i];
		ret[1] = sum; // right index
		sum = 0;
		for(int i=1; i<len && i<=r; i+=2) sum += count[i];
		ret[2] = sum-1; // left index
		ret[3] = neg_min;
	}
	return 0;
}

int count_error(const int N,
	const double sorted_all[],
	const int y_all[],
	const double theta,
	const int s)
{
	int sum = 0;
	for(int ii=0; ii<N; ++ii){
		int y_hat = (sorted_all[ii] < theta) ? -s : s;
		if(y_hat != y_all[ii]) sum++;
	}
	return sum;
}

int get_sorted_all(const std::vector<double>& pos,
	const std::vector<double>& neg,
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

double count_Eout(int s, double theta)
{
	theta = (theta < 0) ? (-theta)/2 : theta/2;
	return (s==1) ? 
		theta*(1-FLIP_PROB) + (1-theta)*FLIP_PROB : 
		theta*(FLIP_PROB) + (1-theta)*(1-FLIP_PROB) ;
}

int experiment(int ret[], const int N){
	Data* train = new Data();
	gen_data(N, train);
	std::vector<double> pos, neg;
	get_sorted_data(train, pos, neg);
	std::vector<int> count;
	get_count_vector(pos, neg, count);
	//std::cout << "count size = " << count.size() << std::endl;
	int temp[4];
	get_min_err(count, temp);
	int s = temp[0];
	double right, left;
	double epsilon = 0.01;
	int p = pos.size(), n = neg.size();
	if(s>0){
		right = (temp[1]==p) ? neg[temp[2]]+epsilon :  pos[temp[1]];
		left = (temp[2]==-1) ? right-epsilon : neg[temp[2]];
	}
	else{
		right = (temp[1]==n) ? pos[temp[2]]+epsilon :  neg[temp[1]];
		left = (temp[2]==-1) ? right-epsilon : pos[temp[2]];
	}
	double theta = (right + left)/2;
	
	//for check
	/*
	double * sorted_all = new double[N];
	int * y_all = new int[N];
	get_sorted_all(pos, neg, sorted_all, y_all);
	int ccc = count_error(N, sorted_all, y_all, theta, s);
	
	if(ccc != temp[3]) {
		for(int ii = 0; ii<N; ++ii) std::cout << sorted_all[ii] << " : " << y_all[ii] << std::endl;

		std::cout << "s=" << s << std::endl;
		std::cout << temp[1] << std::endl;
		std::cout << temp[2] << std::endl;
		std::cout << left << std::endl; 
		std::cout << right  << std::endl; 
		std::cout << "theta=" << theta << std::endl; 
		
		std::cout << "min_err=" << temp[3] << std::endl;
		std::cout << ccc << std::endl;
	}
	delete y_all;
	delete sorted_all;
	*/

	delete train;
	ret[0] = temp[3];
	double Eout = count_Eout(s, theta);
	ret[1] = (int)( Eout * 10);
	return 0;
}

#define REPEAT 5000

int main(int argc, char* argv[]){
	if(argc < 2){
		std::cerr << argv[0] << " <data_size>" << std::endl;
		return -1;
	}
	else std::cerr << "starting!" << std::endl;

	int N;
	sscanf(argv[1], "%d", &N);

	int ret[REPEAT][2];
	for(int i=0; i<REPEAT; ++i){
		experiment(ret[i], N);
	}
	int avg[2] = {0};
	for(int i=0; i<REPEAT; ++i){
		avg[0] += ret[i][0];
		avg[1] += ret[i][1];
	}
	std::cout << "avg: " << (double)avg[0] / REPEAT / N << std::endl;
	std::cout << "avg: " << (double)avg[1] / REPEAT / 10 << std::endl;
	//get_histogram(ret[0], REPEAT);
	//get_histogram(ret[1], REPEAT);
}
