#include <iostream> // for check e_in
#include <string>
#include <vector>
#include <fstream>
#include <random> // for gen_data
using namespace std;

#include "utils.h"
#include "data.h"
#include "sorted_data.h"

#define FLIP_PROB 0.2

static random_device rd;

bool isBlank(const char& c){
	return c==' ' || c=='\t';
}

int Data::read_data(const char filename[], const int& dim){
	ifstream fs(filename, ifstream::in );
	string buffer;
	while( getline(fs, buffer) ){
		double x[dim+1];
		x[0] = 1.0;
		const char * const buf = buffer.c_str();
		int index = 0;
		for(int d=0; d<dim; ++d){
			while(isBlank(buf[index])) index++;
			sscanf(buf + index, "%lf", x+d+1);
			while(!isBlank(buf[index])) index++;
		}
		
		while(isBlank(buf[index])) index++;
		int y;
		sscanf(buf + index, "%d", &y);
		
		// for bonus question, scaling x 
		//for(int i=0; i<1+dim; ++i) x[i] *= 0.01;
		
		data_x.push_back( vector<double>(x, x+dim+1) );
		data_y.push_back( y );
	}
	fs.close();
	return 0;
}

int Data::gen_data(int N){
	uniform_real_distribution<double> uni(0.0, 1.0);
	for(int i=0; i<N; ++i){
		double x = uni(rd)*2-1;
		vector<double>d_x (2,x);
		d_x[0] = 1.0;
		data_x.push_back( d_x );
		int y = (x > 0) ? 1 : -1;
		y = (uni(rd) < FLIP_PROB) ? -y : y;
		data_y.push_back(y);
		//cout << x << '\t' << y << endl;
	}
	return 0;
}

double count_Eout(int s, double theta)
{
	theta = (theta < 0) ? (-theta)/2 : theta/2;
	return (s==1) ? 
		theta*(1-FLIP_PROB) + (1-theta)*FLIP_PROB : 
		theta*(FLIP_PROB) + (1-theta)*(1-FLIP_PROB) ;
}

int count_error(const int N,
	const double sorted_all[],
	const int y_all[],
	const double theta,
	const int s)
{
	int sum = 0;
	for(int ii=0; ii<N; ++ii){
		int y_hat = (sorted_all[ii] < theta) ? -s : s;
		if(y_hat != y_all[ii]) sum++;
	}
	return sum;
}

int Data::get_errors(int& e_in, int& e_out){
	SortedData* sd = new SortedData(this, 1);

	vector<int> count;
	sd->get_count_vector(count);
	//cout << "count size = " << count.size() << endl;
	int s;
	double theta;
	sd->get_decision(count, e_in, s, theta);
	e_out = (int)( count_Eout(s, theta) * 10);

	/*
	int N = data_y.size();
	double * sorted_all = new double[N];
	int * y_all = new int[N];
	sd->get_sorted_all(sorted_all, y_all);
	int ccc = count_error(N, sorted_all, y_all, theta, s);
	if(ccc != e_in) {
		for(int ii = 0; ii<N; ++ii) cout << sorted_all[ii] << " : " << y_all[ii] << endl;
		cout << "s=" << s << endl;
		cout << "theta=" << theta << endl; 
		cout << "e_in=" << e_in << " === " << ccc << endl;
	}
	delete y_all;
	delete sorted_all;
	*/

	delete sd;
	return 0;
}

int Data::get_multi_dim_ein(
	int& e_in_min,
	int& s_min,
	double& theta_min,
	int& dim_th)
{
	const int dim = data_x[0].size()-1;
	
	int * e_in = new int[dim];
	int * s = new int[dim];
	double * theta = new double[dim];
	
	int N = data_y.size();
	e_in_min = N;
	for(int d=0; d<dim; ++d){
		SortedData* sd = new SortedData(this, d+1);
		vector<int> count;
		sd->get_count_vector(count);
		//cout << "count size = " << count.size() << endl;
		sd->get_decision(count, e_in[d], s[d], theta[d]);
		if(e_in[d] < e_in_min) e_in_min = e_in[d];
		delete sd;
	}
	vector<int> indexs;
	for(int d=0; d<dim; ++d)
		if(e_in[d]==e_in_min)
			indexs.push_back(d);
	dim_th = random_choose(indexs)+1;
	s_min = s[dim_th];
	theta_min = theta[dim_th];

	delete theta;
	delete s;
	delete e_in;

	return 0;
}

int Data::test_decision_stump(
	const int& s, 
	const double& theta, 
	const int& dim_th,
	int& e_out_hat)
{
	int N = data_y.size();
	double * sorted_all = new double[N];
	int * y_all = new int[N];
	SortedData* sd = new SortedData(this, dim_th);
	sd->get_sorted_all(sorted_all, y_all);
	e_out_hat = count_error(N, sorted_all, y_all, theta, s);

	delete sd;
	delete y_all;
	delete sorted_all;
	return 0;
}
