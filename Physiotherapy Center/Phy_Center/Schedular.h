#pragma once
#include "Patient.h"
#include "EDevice.h"
#include "UDevice.h"
#include "GymRoom.h"
#include "Resource.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "QueueADT.h"
#include "ArrayStack.h"
#include "EU_Waitlist.h"
#include "EarlyPlist.h"
#include "X_Waitlist.h"
#include"ETherapy.h"
#include"UTherapy.h"
#include"XTherapy.h"

#include <fstream>
#include <sstream>
#include<iostream>
class Schedular
{
private:


	LinkedQueue<Patient*> ALL_Patients;

	EarlyPlist Early_Patients;
	priQueue<Patient*> Late_Patients;

	EU_WaitList E_Waiting;
	EU_WaitList U_Waiting;
	X_WaitList X_Waiting;

	priQueue<Patient*> In_Treatment;
	ArrayStack<Patient*> Finished;


	LinkedQueue<Resource*> EarlyPlist;
	LinkedQueue<Resource*> U_Divces;
	LinkedQueue<Resource*> E_Divces;
	LinkedQueue<Resource*> X_Rooms;
	LinkedQueue<Treatment*>  treatments;

	Patient* patient;
	Resource* resource;

	int totalTimesteps;
	int cancelledPatients;
	int rescheduledPatients;
	int availableEDevices;
	int availableUDevices;
	int availableGRooms;
	int current_step;
	Status Pstatus;
	char char_type;
	Type Ptype;

	int NUM_E, NUM_U, NUM_G;
	int gymCap;
	int PCancel, PResc;
	int Total_patients;

public:
	Schedular(int currentTime);
	void moveToRandomWaiting(Patient* patient);
	void processArrivals(int currentTime);
	void processEarlyList(int currentTime);
	void processLateList(int currentTime);

	void assignResources();
	void processWaitingLists(int currentTime);
	void processInTreatment(int currentTime);
	void processCancellations();
	void processRescheduling();
	bool shouldContinue() const;
	void AddToWait(Patient* Patient, char Type);
	void loadFile(const string& filename);
	void runSimulation(int currentTime);
	void assignXTreatment();
	void assignUTreatment();
	void assignETreatment();
	int getCurrentTime() const;
int getTotalPatients() const { return Total_patients; }
int getAvailableEDevices() const;
int getAvailableUDevices() const;
int getAvailableGRooms() const;
int getNumE() const;
int getNumU() const;
int getNumG() const;
int getGymCapacity() const;

const LinkedQueue<Patient*>& getAllPatients() const;
const LinkedQueue<Patient*>& getEWaiting() const;
const LinkedQueue<Patient*>& getUWaiting() const;
const LinkedQueue<Patient*>& getXWaiting() const;
const priQueue<Patient*>& getEarlyPatients() const;
const priQueue<Patient*>& getLatePatients() const;
const priQueue<Patient*>& getInTreatment() const;
const ArrayStack<Patient*>& getFinishedPatients() const;

const LinkedQueue<Resource*>& getEDevices() const;
const LinkedQueue<Resource*>& getUDevices() const;
const LinkedQueue<Resource*>& getXRooms() const;

	void assignTreatment(Patient* patient, LinkedQueue<Resource*>& resourceQueue, int currentTime);
	void releaseTreatment(Patient* patient);
	~Schedular();
};