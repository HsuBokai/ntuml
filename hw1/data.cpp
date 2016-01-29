#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "data.h"

int Data::read_data(const char filename[]){
	ifstream fs(filename, ifstream::in );
	string buffer;
	while( getline(fs, buffer) ){
		double x[5];
		int y;
		sscanf(buffer.c_str(), "%lf %lf %lf %lf %d", x+1, x+2, x+3, x+4, &y);
		x[0] = 1;
		data_x.push_back( vector<double>(x, x+5) );
		data_y.push_back( y );
	}
	fs.close();
	return 0;
}
