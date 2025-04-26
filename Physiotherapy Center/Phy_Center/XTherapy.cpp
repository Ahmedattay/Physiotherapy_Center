#include "XTherapy.h"
XTherapy::XTherapy() :Treatment() {}
XTherapy::XTherapy(int Duration) :Treatment(Duration, 'X') {}
bool XTherapy::canAssign(Resource* res) {
	if (res->getCapacity() == res->getCurrentPatients())
		return false;
	else
		return true;
}
void XTherapy::moveToWait(Patient* p) {
	schedular->AddToWait(p, 'X');
}
XTherapy::~XTherapy() {}