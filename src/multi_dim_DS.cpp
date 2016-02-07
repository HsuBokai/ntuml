#include <iostream>
#include <vector> // for data.h
using namespace std;

#include "data.h"
#include "utils.h"

#define REPEAT 5000

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << argv[0] << " <file_train.data> <file_test.data>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;

	const int dim = 9;
	Data* train = new Data();
	train->read_data(argv[1], dim);
	Data* test = new Data();
	test->read_data(argv[2], dim);
	int N = train->data_y.size();
	int N_test = test->data_y.size();

	int e_in[REPEAT], e_out[REPEAT], s[REPEAT], dim_th[REPEAT];
	double theta[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		train->get_multi_dim_ein(e_in[i], s[i], theta[i], dim_th[i]);
		test->test_decision_stump(s[i], theta[i], dim_th[i], e_out[i]);
	}
	int avg[5] = {0};
	for(int i=0; i<REPEAT; ++i){
		avg[0] += e_in[i];
		avg[1] += e_out[i];
		avg[2] += s[i];
		avg[3] += theta[i];
		avg[4] += dim_th[i];
	}
	get_histogram(e_in, REPEAT);
	cout << "avg: " << (double)avg[0] / REPEAT / N << endl;
	get_histogram(e_out, REPEAT);
	cout << "avg: " << (double)avg[1] / REPEAT / N_test << endl;
	get_histogram(s, REPEAT);
	cout << "avg: " << (double)avg[2] / REPEAT << endl;
	//get_histogram(theta, REPEAT);
	cout << "avg: " << (double)avg[3] / REPEAT << endl;
	get_histogram(dim_th, REPEAT);
	cout << "avg: " << (double)avg[4] / REPEAT << endl;
}
