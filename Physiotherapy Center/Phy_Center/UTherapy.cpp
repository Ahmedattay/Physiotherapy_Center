#include "UTherapy.h"
UTherapy::UTherapy() :Treatment() {}
UTherapy::UTherapy(int Duration) :Treatment(Duration, 'X') {}
bool UTherapy::canAssign(Resource* res) {
	if (res->getCapacity() == res->getCurrentPatients())
		return false;
	else
		return true;
}
void UTherapy::moveToWait(Patient* p) {
	schedular->AddToWait(p, 'X');
}
UTherapy::~UTherapy() {}