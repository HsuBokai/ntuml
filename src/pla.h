#ifndef _PLA_H_
#define _PLA_H_

#include <vector>
using namespace std;

class PLA
{
public:
	PLA(Data* t) :train(t) {};
	virtual ~PLA(){};

	virtual int run_pla();
	
protected:
	Data* train;

	double inner_dot(const double * const w, 
		const vector<double>& x);
	int check_consistent(const double * const w, 
		const int& start);
};

#endif
