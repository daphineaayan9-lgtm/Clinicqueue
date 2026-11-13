#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>


struct Patient {
    int patientID;      
    std::string fullName; 
    int triageLevel;     
    int arrivalTime;    

   
    Patient() {
        patientID = 0;
        fullName = "";
        triageLevel = 3;
        arrivalTime = 0;
    }

   
    Patient(int id, std::string name, int triage, int time) {
        patientID = id;
        fullName = name;
        triageLevel = triage;
        arrivalTime = time;
    }
};


inline std::ostream& operator<<(std::ostream& out, const Patient& p) {
    out << "ID=" << p.patientID 
        << " | Name=" << p.fullName 
        << " | Triage=" << p.triageLevel 
        << " | Arrival=" << p.arrivalTime;
    return out;
}

#endif