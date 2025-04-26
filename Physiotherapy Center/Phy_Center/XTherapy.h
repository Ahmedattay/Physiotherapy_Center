#pragma once
#include "Treatment.h"
#include "Schedular.h"
class XTherapy:public Treatment
{
	Schedular *schedular;
public:
	XTherapy();
	XTherapy(int Duration);
	bool canAssign(Resource* res)override;
	void moveToWait(Patient* p)override;
	~XTherapy();
};

