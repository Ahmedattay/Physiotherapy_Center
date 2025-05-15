#include "Treatment.h"
//----------------------Constructor Functions----------------------//
Treatment::Treatment() : resource(nullptr), isAssigned(false), assignmentTime(-1), duration(-1), type('d'){}
Treatment::Treatment(int Duration, char Type) : resource(nullptr), isAssigned(false), assignmentTime(-1) {
	duration = Duration;
	type = Type;
}
//----------------------Setter Functions----------------------//
void Treatment::SetDuration(int Duration) { duration = Duration; }
void Treatment::SetAssignmentTime(int AssignmentTime) { assignmentTime = AssignmentTime; }
void Treatment::SetType(char Type) { type = Type; }
void Treatment::SetIsAssigned(bool IsAssigned) { isAssigned = IsAssigned; }
void Treatment::setResource(Resource* Resource) { resource = Resource; }
//----------------------Getter Functions----------------------//
int Treatment::GetDuration() { return duration; }
int Treatment::GetAssignmentTime() { return assignmentTime; }
char Treatment::GetType() { return type; }
bool Treatment::GetIsAssigned() { return isAssigned; }
Resource* Treatment::GetResource() { return resource; }
void Treatment::assignResource(Resource* res) {
    assignedResource = res;
}
Resource* Treatment::getAssignedResource() const {
    return assignedResource;
}
//----------------------Destructor Functions----------------------//
Treatment:: ~Treatment() {

}