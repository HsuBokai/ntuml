#include <iostream>
#include <vector> // for data.h
using namespace std;

#include "data.h"
#include "utils.h"
#include "gradient_descent.h"
#include "tester.h"

#define REPEAT 1

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << argv[0] << " <file_train.data> <file_test.data>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;

	// read data
	const int dim = 20;
	Data* tr = new Data();
	tr->read_data(argv[1], dim);
	GD* gd = new GD(tr);
	
	Data* te = new Data();
	te->read_data(argv[2], dim);
	Tester* tester = new Tester(te);

	
	int error_rate[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		double * const w = new double[dim+1];
		gd->run(w);
		double r = tester->test(w);
		error_rate[i] = (int)(r*100);
		delete [] w;
		//cout << "error_rate: " << error_rate[i] << endl;
	}
	get_histogram(error_rate, REPEAT);
	int avg = 0;
	for(int i=0; i<REPEAT; ++i){
		avg += error_rate[i];
	}
	cout << "avg: " << (double)avg / REPEAT /100 << endl;

	delete tester;
	delete te;
	delete gd;
	delete tr;
	
	return 0;
}
