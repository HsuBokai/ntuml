#include <iostream>
#include <ctime>
using namespace std;

#include "data.h"
#include "pocket_pla.h"

#define REPEAT 2000

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << argv[0] << " <file_train.data> <file_test.data>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;

	// read data
	Data* train = new Data();
	train->read_data(argv[1]);
	Data* test = new Data();
	test->read_data(argv[2]);

	// PLA
	PLA* pla = new PocketPLA(train, test);
	srand(time(NULL));
	int error_rate[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		error_rate[i] = pla->run_pla();
		//cout << "error_rate: " << error_rate[i] << endl;
	}
	pla->get_histogram(error_rate, REPEAT);
	int avg = 0;
	for(int i=0; i<REPEAT; ++i){
		avg += error_rate[i];
	}
	cout << "avg: " << (double)avg / REPEAT << endl;

	delete test;
	delete train;
	delete pla;
	return 0;
}
