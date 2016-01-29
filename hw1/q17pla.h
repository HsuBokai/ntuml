
#ifndef _Q17_H_
#define _Q17_H_

#include <vector>
using namespace std;

class Q17PLA
{
public:
	int main(int argc, char* argv[]);
	
private:
	vector< vector<double> > data_x;
	vector<int> data_y;

	int read_data(const char filename[]);
	
	double inner_dot(const double * const w, 
		const vector<double>& x);
		
	int check_consistent(const double * const w, 
		const int& start);
	
	int PLA(double * const w);
	
	int get_histogram(const int iter[], 
		const size_t len);
};

#endif
