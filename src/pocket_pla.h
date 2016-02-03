#ifndef _POCKET_PLA_H_
#define _POCKET_PLA_H_

#include "pla.h"

class PocketPLA : public PLA
{
public:
	PocketPLA(Data* tr, Data* te) :PLA(tr), test(te) {};
	virtual ~PocketPLA(){};

	virtual int run_pla();
protected:
	Data* test;
	
	int testing(const double * const w);
};

#endif
