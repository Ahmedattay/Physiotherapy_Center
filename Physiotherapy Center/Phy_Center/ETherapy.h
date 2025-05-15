#pragma once
#include "Treatment.h"
class Resource;
class Schedular;
class ETherapy :public Treatment
{
	Schedular *schedular;
public:
	ETherapy();
	ETherapy(int Duration);
	bool canAssign(Resource* res)override;
	void moveToWait(Patient* p)override;
	~ETherapy();
};