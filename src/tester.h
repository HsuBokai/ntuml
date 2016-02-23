#ifndef _TESTER_H_
#define _TESTER_H_

class Tester
{
public:
	Tester(Data* te) : te_(te) {};
	virtual ~Tester(){};

	double test(const double * const w);
protected:
	Data* te_;
};

#endif
