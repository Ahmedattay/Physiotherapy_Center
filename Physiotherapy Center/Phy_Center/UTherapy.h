#pragma once
#include "Treatment.h"
#include "Schedular.h"
class UTherapy :public Treatment
{
	Schedular *schedular;
public:
	UTherapy();
	UTherapy(int Duration);
	bool canAssign(Resource* res)override;
	void moveToWait(Patient* p)override;
	~UTherapy();
};