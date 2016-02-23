#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;

#include "data.h"
#include "gradient_descent.h"

static double inner_dot(const double * const w, 
	const vector<double>& x)
{
	double sum = 0;
	size_t dimension = x.size();
	for(int j=0; j<dimension; ++j){
		sum += w[j] * x[j];
	}
	return sum;
}

/*
int GD::check_consistent(const double * const w, 
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
*/

double GD::gradient(const double * const w, const int i)
{	
	int N = train->data_y.size();
	double sum = 0;
	for(int n = 0; n<N; ++n){
		double p = 1.0/(1.0 + exp((double)(train->data_y[n]) * inner_dot(w, train->data_x[n])));
		sum += p * (double)(train->data_y[n]) * train->data_x[n][i];
	}
	return sum / N;
}

double GD::stochastic_gradient(const double * const w, const int i)
{
	static int n = 0;
	int N = train->data_y.size();
	n = (n+1)%N;
	double p = 1.0/(1.0 + exp((double)(train->data_y[n]) * inner_dot(w, train->data_x[n])));
	return p * (double)(train->data_y[n]) * train->data_x[n][i];
}

int GD::run(double * const w)
{
	size_t dimension = train->data_x[0].size();
	// init w
	for(int i=0; i<dimension; ++i) w[i] = 0;
	
	// iteration
	int iter = 0;
	while( iter < 2000 ) {
		for(int i=0; i<dimension; ++i){
			// for hw3 q18
			// w[i] = w[i] + 0.001 * gradient(w, i);
			// for hw3 q19
			// w[i] = w[i] + 0.01 * gradient(w, i);
			// for hw3 q20
			 w[i] = w[i] + 0.001 * stochastic_gradient(w, i);
		}
		iter ++;
	}
	for(int i=0; i<dimension; ++i){
		cout << "w[" << i << "]: " << w[i] << endl;
	}
	return iter;
}

