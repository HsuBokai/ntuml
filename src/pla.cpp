#include <iostream>
#include <cstdlib>
#include <vector>

#include "data.h"
#include "pla.h"

double PLA::inner_dot(const double * const w, 
	const vector<double>& x)
{
	double sum = 0;
	size_t dimension = x.size();
	for(int j=0; j<dimension; ++j){
		sum += w[j] * x[j];
	}
	return sum;
}

int PLA::check_consistent(const double * const w, 
	const int& start)
{
	size_t N = train->data_y.size();
	for(int i=start; i<N; ++i){
		int predict = ( inner_dot(w, train->data_x[i]) > 0 ) ? 1 : -1;
		if( predict * train->data_y[i] < 0 ) return i;
	}
	for(int i=0; i<start; ++i){
		int predict = ( inner_dot(w, train->data_x[i]) > 0 ) ? 1 : -1;
		if( predict * train->data_y[i] < 0 ) return i;
	}
	return N;
}

int PLA::run_pla()
{
	size_t dimension = train->data_x[0].size();
	// init w
	double * const w = new double[dimension];
	for(int i=0; i<dimension; ++i) w[i] = 0;

	// iteration
	size_t N = train->data_y.size();
	int start = rand() % N;
	int error_index;
	int iter = 0;
	while( (error_index = check_consistent(w, start)) < N) {
		for(int i=0; i<dimension; ++i){
			w[i] = w[i] + (double)(train->data_y[error_index]) * train->data_x[error_index][i] * 0.5;
		}
		//cout << "error_index: " << error_index << endl;
		iter ++;
		//start = rand() % N;
	}

	//for(int i=0; i<dimension; ++i){
	//	cout << "w[" << i << "]: " << w[i] << endl;
	//}
	delete [] w;

	return iter;
}

