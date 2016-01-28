#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

int read_data(vector< vector<double> >& data_x, 
	vector< int >& data_y,
	const char filename[])
{
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

double inner_dot(const double * const w, 
	const vector<double>& x)
{
	double sum = 0;
	size_t dimension = x.size();
	for(int j=0; j<dimension; ++j){
		sum += w[j] * x[j];
	}
	return sum;
}

int check_consistent(const double * const w, 
	const vector< vector<double> >& data_x, 
	const vector<int>& data_y,
	const int& start)
{
	size_t N = data_y.size();
	for(int i=start; i<N; ++i){
		int predict = ( inner_dot(w, data_x[i]) > 0 ) ? 1 : -1;
		if( predict * data_y[i] < 0 ) return i;
	}
	for(int i=0; i<start; ++i){
		int predict = ( inner_dot(w, data_x[i]) > 0 ) ? 1 : -1;
		if( predict * data_y[i] < 0 ) return i;
	}
	return N;
}

int PLA(double * const w, 
	const vector< vector<double> >& data_x, 
	const vector<int>& data_y)
{
	size_t dimension = data_x[0].size();
	size_t N = data_y.size();
	int start = rand() % N;
	int error_index;
	int iter = 0;
	while( (error_index = check_consistent(w, data_x, data_y, start)) < N) {
		for(int i=0; i<dimension; ++i){
			w[i] = w[i] + (double)data_y[error_index] * data_x[error_index][i] * 0.5;
		}
		//cout << "error_index: " << error_index << endl;
		iter ++;
		//start = rand() % N;
	}
	return iter;
}

int get_histogram(const int iter[], 
	const size_t len)
{
	int min=iter[0], max=iter[0];
	for(int i=0; i<len; ++i){
		if(iter[i] < min) min = iter[i];
		if(iter[i] > max) max = iter[i];
	}
	size_t range = max-min+1;
	int * const histogram = new int [range];
	for(int i=0; i<range; ++i){
		histogram[i] = 0;
	}
	for(int i=0; i<len; ++i){
		histogram[iter[i]-min]++;
	}
	for(int i=0; i<range; ++i){
		if(histogram[i] > 0) cout << min+i << "\t:\t" << histogram[i] << endl;
	}
	delete [] histogram;
	return 0;
}

#define REPEAT 2000

int main(int argc, char* argv[]){
	if(argc < 2){
		cerr << argv[0] << " <file_train.data>" << endl;
		return -1;
	}
	else cerr << "starting!" << endl;
	// read data
	vector< vector<double> > data_x;
	vector< int > data_y;
	read_data(data_x, data_y, argv[1]);
	
	// init w
	size_t dimension = data_x[0].size();
	double * const w = new double[dimension];

	// PLA
	srand(time(NULL));
	int iter[REPEAT];
	for(int i=0; i<REPEAT; ++i){
		for(int i=0; i<dimension; ++i) w[i] = 0;
		iter[i] = PLA(w, data_x, data_y);
		//cout << "iter: " << iter[i] << endl;
		//for(int i=0; i<dimension; ++i){
		//	cout << "w[" << i << "]: " << w[i] << endl;
		//}
	}
	delete [] w;
	get_histogram(iter, REPEAT);
	int avg = 0;
	for(int i=0; i<REPEAT; ++i){
		avg += iter[i];
	}
	cout << "avg: " << (double)avg / REPEAT << endl;
	return 0;
}
