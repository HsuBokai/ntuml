#include <iostream>
#include <vector> // for data.h
using namespace std;

#include "data.h"
#include "utils.h"

#define REPEAT 5000

int experiment(const int N, int& e_in, int& e_out){
	Data* train = new Data();
	train->gen_data(N);
	train->get_errors(e_in, e_out);
	return 0;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		cerr << argv[0] << " <data_size>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;

	int N;
	sscanf(argv[1], "%d", &N);

	int e_in[REPEAT], e_out[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		experiment(N, e_in[i], e_out[i]);
	}
	int avg[2] = {0};
	for(int i=0; i<REPEAT; ++i){
		avg[0] += e_in[i];
		avg[1] += e_out[i];
	}
	get_histogram(e_in, REPEAT);
	cout << "avg: " << (double)avg[0] / REPEAT / N << endl;
	get_histogram(e_out, REPEAT);
	cout << "avg: " << (double)avg[1] / REPEAT / 10 << endl;
}
