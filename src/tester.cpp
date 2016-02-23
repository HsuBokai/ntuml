#include <cstdlib>
#include <vector> // for data.h
using namespace std;

#include "data.h"
#include "tester.h"

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

double Tester::test(const double * const w)
{
	int N = te_->data_y.size();
	int error = 0;
	for(int i=0; i<N; ++i){
		int predict = ( inner_dot(w, te_->data_x[i]) > 0 ) ? 1 : -1;
		if( predict * te_->data_y[i] < 0 ) error++;
	}
	return (double)error / N;
}

