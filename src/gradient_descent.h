#ifndef _GD_H_
#define _GD_H_

class GD
{
public:
	GD(Data* t) :train(t) {};
	virtual ~GD(){};

	virtual int run(double * const w);
	
protected:
	Data* train;
	
	double gradient(const double * const w, const int i);
	double stochastic_gradient(const double * const w, const int i);
};

#endif
