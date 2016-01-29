
#ifndef _DATA_H_
#define _DATA_H_

#include <vector>

class Data
{
public:
	Data(){};
	virtual ~Data(){};

	std::vector< std::vector<double> > data_x;
	std::vector<int> data_y;
	
	int read_data(const char filename[]);
};

#endif
