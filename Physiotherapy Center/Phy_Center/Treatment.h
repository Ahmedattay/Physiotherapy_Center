#pragma once
class Patient;
class Resource;
class Treatment
{
protected:
	int duration;
	int assignmentTime;
	char type;
	bool isAssigned;
	Resource* resource;
	Resource* assignedResource;
public:
	//----------------------Constructor Functions----------------------//
	Treatment();
	Treatment(int Duration, char Type);
	//----------------------virtual Functions----------------------//
	virtual bool canAssign(Resource* res) = 0;
	virtual void moveToWait(Patient* p) = 0;
	//----------------------Setter Functions----------------------//
	void SetDuration(int Duration);
	void SetAssignmentTime(int AssignmentTime);
	void SetType(char Type);
	void SetIsAssigned(bool IsAssigned);
	void setResource(Resource* Resource);
	//----------------------Getter Functions----------------------//
	int GetDuration();
	int GetAssignmentTime();
	char GetType();
	bool GetIsAssigned();
	void assignResource(Resource* res);
	Resource* getAssignedResource() const;
	Resource* GetResource();
	//----------------------Destructor Functions----------------------//
	virtual ~Treatment();

};

