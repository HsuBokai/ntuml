#include <cstdlib>
#include "data.h"
#include "pocket_pla.h"

int PocketPLA::run_pla(){
	size_t dimension = train->data_x[0].size();
	// init w
	double * const w = new double[dimension];
	for(int i=0; i<dimension; ++i) w[i] = 0;

	double * const w_optimal = new double[dimension];
	for(int i=0; i<dimension; ++i) w_optimal[i] = 0;
	int min_error;
	
	// iteration
	size_t N = train->data_y.size();
	for(int iter=0; iter<50; ++iter){
		int start = rand() % N;
		int error_index = check_consistent(w, start);
		if(error_index >= N) break;
		for(int i=0; i<dimension; ++i){
			w[i] = w[i] + (double)(train->data_y[error_index]) * train->data_x[error_index][i];
		}

		//testing
		int error = testing(w);
		if(iter==0) min_error = error;
		if(error < min_error) {
			min_error = error;
			for(int i=0; i<dimension; ++i) w_optimal[i] = w[i];
		}
	}

	// for q19
	//min_error = testing(w);

	delete [] w_optimal;
	delete [] w;

	return min_error;
}

int PocketPLA::testing(const double * const w)
{
	size_t N = test->data_y.size();
	int error = 0;
	for(int i=0; i<N; ++i){
		int predict = ( inner_dot(w, test->data_x[i]) > 0 ) ? 1 : -1;
		if( predict * test->data_y[i] < 0 ) error++;
	}
	return error;
}

