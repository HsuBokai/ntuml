
#ifndef _DATA_H_
#define _DATA_H_

class Data
{
public:
	Data(){};
	virtual ~Data(){};

	std::vector< std::vector<double> > data_x;
	std::vector<int> data_y;
	
	int read_data(const char filename[], const int& dim);
	
	int gen_data(int N);

	int get_errors(int& e_in, int& e_out);

	int get_multi_dim_ein(
		int& e_in,
		int& s,
		double& theta,
		int& dim_th);
	
	int test_decision_stump(
		const int& s, 
		const double& theta, 
		const int& dim_th,
		int& e_out_hat);

};

#endif
