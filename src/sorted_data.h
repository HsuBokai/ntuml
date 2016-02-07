
#ifndef _SORTED_DATA_H_
#define _SORTED_DATA_H_

class SortedData
{
public:
	SortedData(const Data* d, const int& dim_th);
	virtual ~SortedData(){};

	std::vector<double> pos;
	std::vector<double> neg;
	
	int get_count_vector(std::vector<int>& count);
	
	int get_decision(const std::vector<int>& count, int& e_in, int& s, double& theta);
	
	int get_sorted_all(double * const sorted_all, int * const y_all);

};

#endif
