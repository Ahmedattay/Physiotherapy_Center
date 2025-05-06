#include "Schedular.h"
#include <fstream>
Schedular::Schedular(int currentTime)
{
    srand(time(0));      // Seed random number generator
    totalTimesteps = 0;
    cancelledPatients = 0;
    rescheduledPatients = 0;
    current_step = currentTime;
    NUM_E = 0;
    NUM_U = 0;
    NUM_G = 0;
    PCancel = 0;
    PResc = 0;
    Total_patients = 0;  // Initialize Total_patients
    Pstatus = IDLE;      // Initialize Pstatus
    Ptype = NP;          // Initialize Ptype
    char_type = '\0';    // Initialize char_type
    gymCap = 0;          // Initialize gymCap
    patient = nullptr;   // Initialize patient
    resource = nullptr;  // Initialize resource
    inout = nullptr;
}

void Schedular::processArrivals(int currentTime) {
    Patient* patient = nullptr;
    while (ALL_Patients.peek(patient) && patient->getArrival_Time() <= currentTime) {
        
        ALL_Patients.dequeue(patient);

        if (patient->getStatus() == FNSH) {
            Finished.push(patient);
            continue;
        }

        if (patient->getArrival_Time() < patient->getAppoinment_Time()) {
            Early_Patients.enqueue(patient, patient->getAppoinment_Time());
            Status pstat;
            pstat = ERLY;
            patient->setStatus(pstat);

        }
        else if (patient->getArrival_Time() > patient->getAppoinment_Time()) {
            int penalty = (patient->getArrival_Time() - patient->getAppoinment_Time()) / 2;
            int effectiveTime = patient->getArrival_Time() + penalty;
            Late_Patients.enqueue(patient, effectiveTime);
            /*patient->setAppoinment_Time(penalty+ patient->getAppoinment_Time());*/
            Status pstat;
            pstat = LATE;
            patient->setStatus(pstat);
        }
        else {
            if (patient->getCurrentTreatment()) {
                char treatmentType = patient->getCurrentTreatment()->GetType();
               AddToWait(patient, treatmentType);
            }
        }
    }
}
void Schedular::processEarlyList(int currentTime) {
    Patient* patient;
    int pri;
    while (!Early_Patients.isEmpty())
    {
        Early_Patients.dequeue(patient, pri);

        Treatment* treatment = patient->getCurrentTreatment();

        if (treatment)
        {

            treatment->moveToWait(patient);
            Status pstat;
            pstat = WAIT;
            patient->setStatus(pstat);
        }



    }
}
void Schedular::processLateList(int currentTime)
 {
    Patient* patient;
    int pri;
    while (!Late_Patients.isEmpty())
    {
        Late_Patients.dequeue(patient, pri);

        Treatment* treatment = patient->getCurrentTreatment();

        if (treatment)
        {
            treatment->moveToWait(patient);
            Status pstat;
            pstat = WAIT;
            patient->setStatus(pstat);
        }
    }
}
void Schedular::processWaitingLists(int currentTime) {
    Patient* patient;
    while (!E_Waiting.isEmpty()) 
    {
        E_Waiting.peek(patient);
        // Verify treatment type matches waiting list
        if (patient && patient->getCurrentTreatment() && patient->getCurrentTreatment()->GetType() == 'E') {
            E_Waiting.dequeue(patient);
            assignTreatment(patient, E_Divces, currentTime);
        }
        else if (patient && patient->getCurrentTreatment())
        {
            // Handle mismatch - move to correct waiting list
            char correctType = patient->getCurrentTreatment()->GetType();
            E_Waiting.dequeue(patient);
            AddToWait(patient, correctType);
            continue;
        }
    }

    // Process U-Waiting
    while (!U_Waiting.isEmpty()) {
        Patient* patient;
        U_Waiting.peek(patient);

        if (patient && patient->getCurrentTreatment() &&
            patient->getCurrentTreatment()->GetType() == 'U') {
            U_Waiting.dequeue(patient);
            assignTreatment(patient, U_Divces, currentTime);
        }
        else 
        {
            char correctType = patient->getCurrentTreatment()->GetType();
            U_Waiting.dequeue(patient);
            AddToWait(patient, correctType);
            continue;
        }
    }

    while (!X_Waiting.isEmpty()) {
        Resource* room;
        X_Rooms.peek(room);
        if (room && room->getCurrentPatients() < room->getCapacity()) {
            Patient* patient;
            X_Waiting.peek(patient);

            if (patient && patient->getCurrentTreatment() &&
                patient->getCurrentTreatment()->GetType() == 'X') {
                X_Waiting.dequeue(patient);
                assignTreatment(patient, X_Rooms, currentTime);
            }
            else {
                char correctType = patient->getCurrentTreatment()->GetType();
                X_Waiting.dequeue(patient);
                AddToWait(patient, correctType);
            }
        }
    }

}
void Schedular::processInTreatment(int currentTime) {
    Patient* patient = nullptr;
    int finishTime;

    while (In_Treatment.peek(patient, finishTime) && finishTime <= currentTime) {
        In_Treatment.dequeue(patient, finishTime);
        releaseTreatment(patient);

        if (patient->moveToNextTreatment()) {
            // For normal patients, get next treatment in sequence
            char nextType = patient->getCurrentTreatment()->GetType();
            AddToWait(patient, nextType);
        }
        else {
            patient->setFinishTime(currentTime);
            Status pstat;
            pstat = FNSH;
            patient->setStatus(pstat);
            Finished.push(patient);
        }
    }
}
void Schedular::processCancellations() {
    if (X_Waiting.isEmpty()) return;

    // Check each patient in X-Waiting
    LinkedQueue<Patient*> tempQueue;
    while (!X_Waiting.isEmpty()) {
        Patient* patient = nullptr;
        X_Waiting.dequeue(patient);

        if (patient &&
            patient->getCurrentTreatment() &&
            patient->getCurrentTreatment()->GetType() == 'X' &&
            patient->getRemainingTreatments() == 1) {
            // Eligible for cancellation
            if (rand() % 100 < PCancel) {
                cancelledPatients++;
                cout << "CANCELLED: Patient " << patient->getPatientID() << endl;
                delete patient;
                continue;
            }
        }
        tempQueue.enqueue(patient);
    }

    // Restore non-cancelled patients
    while (!tempQueue.isEmpty()) {
        Patient* patient = nullptr;
        tempQueue.dequeue(patient);
        X_Waiting.enqueue(patient);
    }
}
void Schedular::processRescheduling() {
    if (Early_Patients.isEmpty()) return;

    // Check each early patient
    priQueue<Patient*> tempQueue;
    while (!Early_Patients.isEmpty()) {
        Patient* patient = nullptr;
        int oldPT;
        Early_Patients.dequeue(patient, oldPT);

        if (patient && (rand() % 100 < PResc)) {
            int newPT = oldPT + (rand() % 10) + 1; // 1-10 timesteps later
            patient->setAppoinment_Time(newPT);
            tempQueue.enqueue(patient, newPT);
            rescheduledPatients++;
            cout << "RESCHEDULED: Patient " << patient->getPatientID()
                << " to PT=" << newPT << endl;
        }
        else {
            tempQueue.enqueue(patient, oldPT);
        }
    }

    // Restore patients
    while (!tempQueue.isEmpty()) {
        Patient* patient = nullptr;
        int pt;
        tempQueue.dequeue(patient, pt);
        Early_Patients.enqueue(patient, pt);
    }
}
/////////////////////////////////////////////////////
void Schedular::moveToRandomWaiting(Patient* patient)
{
    int N = rand() % 100;

    if (N < 33) // E-Waiting
    {
        E_Waiting.insertSorted(patient);
    }
    else if (N < 66) // U-Waiting
    {
        U_Waiting.insertSorted(patient);
    }
    else // X-Waiting
    {
        X_Waiting.insertSorted(patient);
    }

}
void Schedular::loadFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    // --- Read Resources ---
    // Line 1: NE NU NG (number of E/U/X resources)
    inputFile >> NUM_E >> NUM_U >> NUM_G;

    // Line 2: Gym capacities (one per gym room, total of NUM_G values)
    int* gymCaps = new int[NUM_G];  // Dynamic array to store capacities
    for (int i = 0; i < NUM_G; i++) {
        inputFile >> gymCaps[i];  // Read each gym room's capacity
    }

    // Initialize resources
    for (int i = 0; i < NUM_E; i++) {
        E_Divces.enqueue(new EDevice(i + 1));
    }
    for (int i = 0; i < NUM_U; i++) {
        U_Divces.enqueue(new UDevice(i + 1));
    }
    for (int i = 0; i < NUM_G; i++) {
        X_Rooms.enqueue(new GymRoom(i + 1, gymCaps[i]));  // Assign unique capacity
    }
    delete[] gymCaps;  // Free memory

    // --- Read Probabilities ---
    // Line 3: PCancel PResc
    inputFile >> PCancel >> PResc;

    // --- Read Patients ---
    // Line 4: Total_patients (P)
    inputFile >> Total_patients;

    for (int i = 0; i < Total_patients; i++) {
        char char_type;  // N or R
        int pt, vt, nt;  // Appointment time, Arrival time, Num treatments
        inputFile >> char_type >> pt >> vt >> nt;

        Patient* patient = new Patient(i + 1, char_type, pt, vt);
        int totalTreatmentTime = 0;
        // Read treatments (T1 D1 T2 D2 ...)
        for (int j = 0; j < nt; j++) {
            char tType;  // E, U, or X
            int duration;
            inputFile >> tType >> duration;
            totalTreatmentTime += duration;
            Treatment* treatment = nullptr;
            switch (tType) {
            case 'E':
                treatment = new ETherapy(duration);
                break;
            case 'U':
                treatment = new UTherapy(duration);
                break;
            case 'X':
                treatment = new XTherapy(duration);
                break;
            default:
                cerr << "Error: Unknown treatment type '" << tType << "' for PID " << i + 1 << endl;
                break;
            }
            if (treatment) {
                patient->addTreatment(treatment);
            }
        }
        patient->setFinishTime(vt + totalTreatmentTime);

        patient->setTotalTreatmentTime(totalTreatmentTime);
        ALL_Patients.enqueue(patient);
    }

    inputFile.close();
}
void Schedular::runSimulation(int currentTime)
{  

        // Process in strict order
        processArrivals(currentTime);
        processEarlyList(currentTime);
        processLateList(currentTime);
        processWaitingLists(currentTime);
        processInTreatment(currentTime); 

        /*UI ui(this);*/
       /* ui.displayCurrentStatus(currentTime);*/

        // Use your existing print functions exactly as provided

}
void Schedular::AddToWait(Patient* patient, char Type) {
    if (!patient) return;
    patient->setWaitingStartTime(current_step);
    if (Type == 'E') E_Waiting.insertSorted(patient);
    else if (Type == 'U') U_Waiting.insertSorted(patient);
    else if (Type == 'X') X_Waiting.insertSorted(patient);
}
bool Schedular::shouldContinue() const {

    if (Finished.size() == Total_patients)
        return false;
    else
        return true;
}
//////////////////////////////////////////////////////
void Schedular::assignTreatment(Patient* patient, LinkedQueue<Resource*>& resourceQueue, int currentTime) {
    if (!patient || resourceQueue.isEmpty()) return;

    Resource* resource;
    // Get current treatment type
    char treatmentType = patient->getCurrentTreatment()->GetType();
    resourceQueue.peek(resource);
    char resourceType = resource->getResourceType();

    // Verify treatment and resource types match
    if (treatmentType != resourceType) {
        AddToWait(patient, treatmentType);
        return;
    }

    resourceQueue.dequeue(resource);

    // Special handling for X-therapy rooms
    if (resource->getResourceType() == 'X') {
        GymRoom* room = static_cast<GymRoom*>(resource);
        if (room->getCurrentPatients() >= room->getCapacity()) {
            resourceQueue.enqueue(resource);
            return;
        }
        room->addPatient(patient);
        
    }

    // Assign treatment
    patient->getCurrentTreatment()->setResource(resource);
    int finishTime = patient->getAppoinment_Time() + patient->getCurrentTreatment()->GetDuration();
    In_Treatment.enqueue(patient, finishTime);
    Status pstat;
    pstat = SERV;
    patient->setStatus(pstat);
}
void Schedular::assignResources() {
    // Assign E-Therapy resources
    if (!E_Waiting.isEmpty() && !E_Divces.isEmpty()) {
        Patient* patient = nullptr;
        E_Waiting.dequeue(patient);

        if (patient && patient->getCurrentTreatment()) {
            Resource* device = nullptr;
            E_Divces.dequeue(device);

            if (device) {
                // Assign resource and move to in-treatment
                patient->getCurrentTreatment()->setResource(device);
                int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
                In_Treatment.enqueue(patient, finishTime);
                Status pstat = SERV;
                patient->setStatus(pstat);

                cout << "Assigned E-device to patient " << patient->getPatientID()
                    << " (finishes at timestep " << finishTime << ")" << endl;
            }
            else {
                E_Waiting.enqueue(patient); // Return to queue if no device available
            }
        }
    }
    // Assign U-Therapy resources
    if (!U_Waiting.isEmpty() && !U_Divces.isEmpty()) {
        Patient* patient = nullptr;
        U_Waiting.dequeue(patient);

        if (patient && patient->getCurrentTreatment()) {
            Resource* device = nullptr;
            U_Divces.dequeue(device);

            if (device) {
                patient->getCurrentTreatment()->setResource(device);
                int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
                In_Treatment.enqueue(patient, finishTime);
                Status pstat = SERV;
                patient->setStatus(pstat);

                cout << "Assigned U-device to patient " << patient->getPatientID()
                    << " (finishes at timestep " << finishTime << ")" << endl;
            }
            else {
                U_Waiting.enqueue(patient);
            }
        }
    }

    // Assign X-Therapy resources (gym rooms)
    if (!X_Waiting.isEmpty() && !X_Rooms.isEmpty()) {
        Patient* patient = nullptr;
        X_Waiting.dequeue(patient);

        if (patient && patient->getCurrentTreatment()) {
            Resource* room = nullptr;
            X_Rooms.peek(room); // Peek first to check capacity

            if (room && room->getCurrentPatients() < room->getCapacity()) {
                X_Rooms.dequeue(room);
                room->addPatient(patient);
                patient->getCurrentTreatment()->setResource(room);
                int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
                In_Treatment.enqueue(patient, finishTime);
                Status pstat = SERV;
                patient->setStatus(pstat);
                X_Rooms.enqueue(room); // Return room to available queue

                cout << "Assigned X-room to patient " << patient->getPatientID()
                    << " (finishes at timestep " << finishTime << ")" << endl;
            }
            else {
                X_Waiting.enqueue(patient);
            }
        }
    }
}
void Schedular::assignETreatment() {
    if (E_Waiting.isEmpty() || E_Divces.isEmpty()) return;

    Patient* patient;
    E_Waiting.dequeue(patient);
    if (patient) {
        patient->addWaitingTime(current_step - patient->getWaitingStartTime());
        Resource* device;
        E_Divces.dequeue(device);

        device->addPatient(patient);
        patient->getCurrentTreatment()->setResource(device);
        int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
        In_Treatment.enqueue(patient, finishTime);
        Status pstat;
        pstat = SERV;
        patient->setStatus(pstat);
    }
}
void Schedular::assignUTreatment() {
    if (U_Waiting.isEmpty() || U_Divces.isEmpty()) return;

    Patient* patient;
    U_Waiting.dequeue(patient);
    patient->addWaitingTime(current_step - patient->getWaitingStartTime());
    Resource* device;
    U_Divces.dequeue(device);

    device->addPatient(patient);
    patient->getCurrentTreatment()->setResource(device);
    int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
    In_Treatment.enqueue(patient, finishTime);
    Status pstat = SERV;
    patient->setStatus(pstat);
}
void Schedular::assignXTreatment() {
    if (X_Waiting.isEmpty() || X_Rooms.isEmpty()) return;

    Patient* patient;
    X_Waiting.peek(patient);
    patient->addWaitingTime(current_step - patient->getWaitingStartTime());
    Resource* room;
    X_Rooms.peek(room);

    if (room->getCurrentPatients() < room->getCapacity()) {
        X_Waiting.dequeue(patient);
        X_Rooms.dequeue(room);

        room->addPatient(patient);
        patient->getCurrentTreatment()->setResource(room);
        int finishTime = current_step + patient->getCurrentTreatment()->GetDuration();
        In_Treatment.enqueue(patient, finishTime);
        Status pstat = SERV;
        patient->setStatus(pstat);

        X_Rooms.enqueue(room);
    }
}
//////////////////////////////////////////////////////
void Schedular::Create_Out_File(int timestep) 
{
    ofstream outfile;
    Patient* patient;
    int totalWaitTime = 0;
    int totalTreatmentTime = 0;
    int totalPatients = 0;

    // Open the output file
    string fileName = "../OutPut_File.txt";
    outfile.open(fileName);

    // Write header to the file
    outfile << "PID\tPType\tPT\tVT\tFT\tWT\tTT\tCancel\tResc" << endl;

    // Process each patient in the Finished stack
    while (!Finished.isEmpty()) {
        Finished.pop(patient);

        if (patient) {
            // Write patient details to the file
            outfile << patient->getPatientID() << "\t"
                << patient->getType() << "\t"
                << patient->getAppoinment_Time() << "\t"
                << patient->getArrival_Time() << "\t"
                << patient->getFinsihTime() << "\t"
                << patient->getTotalWaitTime() << "\t"
                << patient->getTotalTreatmentTime() << "\t"
                << (patient->hasAcceptedCancellation() ? "T" : "F") << "\t"
                << (patient->hasAcceptedRescheduling() ? "T" : "F") << endl;

            // Update statistics
            totalWaitTime += patient->getTotalWaitTime();
            totalTreatmentTime += patient->getTotalTreatmentTime();
            totalPatients++;

        }
    }

    // Calculate and write statistics
    float avgWaitTime = totalWaitTime / static_cast<float>(totalPatients);
    float avgTreatmentTime = totalTreatmentTime / static_cast<float>(totalPatients);

    outfile << "Total number of patients: " << totalPatients << endl;
    outfile << "Average waiting time: " << avgWaitTime << endl;
    outfile << "Average treatment time: " << avgTreatmentTime << endl;
    outfile << "Simulation ended at timestep: " << timestep << endl;

    // Close the output file
    outfile.close();

    // Print message
    inout->PrintMessage("Output File Created, Simulation Complete.");
}
//----------------------Getter Functions----------------------//
int Schedular::getCurrentTime() const { return current_step; }
int Schedular::getAvailableEDevices() const { return availableEDevices; }
int Schedular::getAvailableUDevices() const { return availableUDevices; }
int Schedular::getAvailableGRooms() const { return availableGRooms; }
int Schedular::getNumE() const { return NUM_E; }
int Schedular::getNumU() const { return NUM_U; }
int Schedular::getNumG() const { return NUM_G; }
int Schedular::getGymCapacity() const { return gymCap; }
const LinkedQueue<Patient*>& Schedular::getAllPatients() const { return ALL_Patients; }
const LinkedQueue<Patient*>& Schedular::getEWaiting() const { return E_Waiting; }
const LinkedQueue<Patient*>& Schedular::getUWaiting() const { return U_Waiting; }
const LinkedQueue<Patient*>& Schedular::getXWaiting() const { return X_Waiting; }
const priQueue<Patient*>& Schedular::getEarlyPatients() const { return Early_Patients; }
const priQueue<Patient*>& Schedular::getLatePatients() const { return Late_Patients; }
const priQueue<Patient*>& Schedular::getInTreatment() const { return In_Treatment; }
const ArrayStack<Patient*>& Schedular::getFinishedPatients() const { return Finished; }
const LinkedQueue<Resource*>& Schedular::getEDevices() const { return E_Divces; }
const LinkedQueue<Resource*>& Schedular::getUDevices() const { return U_Divces; }
const LinkedQueue<Resource*>& Schedular::getXRooms() const { return X_Rooms; }
//-----------------------------------------------------------//
void Schedular::releaseTreatment(Patient* patient) {
    if (!patient || !patient->getCurrentTreatment()) return;

    Resource* resource = patient->getCurrentTreatment()->GetResource();
    if (resource) {
        resource->removePatient();

        // Return resource to appropriate available queue
        switch (resource->getResourceType()) {
        case 'E':
            E_Divces.enqueue(resource);
            break;
        case 'U':
            U_Divces.enqueue(resource);
            break;
        case 'X':
            X_Rooms.enqueue(resource);
            break;
        }
    }
}
/////////////////////////////////////////
Schedular::~Schedular() {  
 Patient* p;  
 int pri;  
 while (ALL_Patients.dequeue(p)) delete p;  
 while (Early_Patients.dequeue(p, pri)) delete p;  
 while (Late_Patients.dequeue(p, pri)) delete p;  
 while (E_Waiting.dequeue(p)) delete p;  
 while (U_Waiting.dequeue(p)) delete p;  
 while (X_Waiting.dequeue(p)) delete p;  
 while (In_Treatment.dequeue(p, pri)) delete p;  
 while (!Finished.isEmpty()) {  
     Finished.pop(p);  
     delete p;  
 }  

 Resource* r;
 while (E_Divces.dequeue(r)) delete r;  
 while (U_Divces.dequeue(r)) delete r;  
 while (X_Rooms.dequeue(r)) delete r;  
}