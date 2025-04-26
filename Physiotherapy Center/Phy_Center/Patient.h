#ifndef PATIENT_H
#define PATIENT_H

#include "LinkedQueue.h"
#include <string>
class Treatment;
using namespace std;

enum Type {
    NP,
    RP
};
enum Status
{
    IDLE,
    ERLY,
    LATE,
    WAIT,
    FNSH,
    SERV
};
class Patient {
private:
    int patientID;
    Type type;
    Status status;
    int Appoinment_Time;
    int Arrival_Time;

    LinkedQueue<Treatment*> Required_Treatments;

    bool isCancelled;
    bool isResc;

    int FinsihTime;
    int TotalWaittime;
    int TotalTreatmenttime;

public:

    Patient();
    Patient(int pid, char ptype, int pt, int vt);

    int getPatientID() const;
    void setPatientID(int id);//id

    Type getType() const;
    void setType(Type& type);//type

    Status getStatus() const;
    void setStatus(Status& st);//status

    LinkedQueue<Treatment*> getTreatment()const;
    void setRequiredTreatments(LinkedQueue<Treatment*> rt);//treatment

    bool getIsclosed() const;
    void setIsclosed(bool c);//isclosed

    bool getIsResc() const;
    void setIsResc(bool r);//isresc

    int getFinsihTime()const;
    void setFinishTime(int F);//FT

    int getTotalWaitTime()const;
    void setTotalWaitTime(int TW);//TW

    int getTotalTreatmentTime()const;
    void setTotalTreatmentTime(int TT);//TT

    int getArrival_Time() const;
    void setArrival_Time(int Vt);//VT

    int getAppoinment_Time();
    void setAppoinment_Time(int Pt);//PT
    void addTreatment(Treatment *t) ;
    Treatment* getCurrentTreatment();
    bool isFinished() const;
    int getRemainingTreatments() const;
    bool moveToNextTreatment();
    ~Patient();
};

#endif // PATIENT_H