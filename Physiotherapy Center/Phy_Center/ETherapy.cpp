#include "ETherapy.h"
#include "Schedular.h"  // For Schedular definition
#include "Resource.h"   // For Resource definition
#include "Patient.h" 

ETherapy::ETherapy() :Treatment() {}
ETherapy::ETherapy(int Duration) :Treatment(Duration, 'E') {}
bool ETherapy::canAssign(Resource* res) {
	if (res->getCapacity() == res->getCurrentPatients())
		return false;
	else
		return true;
}
void ETherapy::moveToWait(Patient* p) {
	schedular->AddToWait(p, 'E');
}
ETherapy::~ETherapy() {}