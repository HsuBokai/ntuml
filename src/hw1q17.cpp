#include <iostream>
#include <ctime>
using namespace std;

#include "data.h"
#include "pla.h"
#include "utils.h"

#define REPEAT 2000

int main(int argc, char* argv[]){
	if(argc < 2){
		cerr << argv[0] << " <file_train.data>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;

	// read data
	Data* train = new Data();
	train->read_data(argv[1]);

	// PLA
	PLA* pla = new PLA(train);
	srand(time(NULL));
	int iter[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		iter[i] = pla->run_pla();
		//cout << "iter: " << iter[i] << endl;
	}
	get_histogram(iter, REPEAT);
	int avg = 0;
	for(int i=0; i<REPEAT; ++i){
		avg += iter[i];
	}
	cout << "avg: " << (double)avg / REPEAT << endl;

	delete train;
	delete pla;
	return 0;
}
