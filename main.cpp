#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "Patient.h"
#include "Queue.h"
#include "Sorting.h"

using namespace std;

 
bool sortByTriageThenArrival(const Patient& a, const Patient& b) {
    if (a.triageLevel != b.triageLevel) {
        return a.triageLevel < b.triageLevel;
    }
    return a.arrivalTime < b.arrivalTime; 
}

bool sortByID(const Patient& a, const Patient& b) {
    return a.patientID < b.patientID;
}


bool loadPatients(const string& filename, ClinicQueue<Patient>& q) {
    ifstream in(filename.c_str());
    if (!in) {
        cout << "Could not open file: " << filename << endl;
        return false;
    }

    int id, triage, arrival;
    string name;
    int count = 0;

    while (in >> id >> name >> triage >> arrival) {
        try {
            q.enqueue(Patient(id, name, triage, arrival));
            count++;
        } catch (runtime_error& e) {
            cout << "Stopped loading: " << e.what() << endl;
            break;
        }
    }
    in.close();
    return count > 0;
}


void savePatients(const string& filename, const ClinicQueue<Patient>& q) {
    ofstream out(filename.c_str());
    if (!out) {
        cout << "Could not create file: " << filename << endl;
        return;
    }
    
    for (int i = 0; i < q.size(); i++) {
        Patient p = q.getAt(i);
        out << p.patientID << " " << p.fullName << " " 
            << p.triageLevel << " " << p.arrivalTime << "\n";
    }
    out.close();
    cout << "Saved updated records to " << filename << endl;
}



void testA1_QueueOperations() {
    cout << "\n--- A1: Queue Operations (Loading from patients.txt) ---" << endl;
    
   
    ClinicQueue<Patient> q(20);
    
    if (!loadPatients("patients.txt", q)) {
        cout << "Failed to load patients." << endl;
        return;
    }
    
    cout << "Successfully loaded " << q.size() << " patients from file." << endl;
    cout << "Next patient in line (Front): " << q.peekFront() << endl;

   
    Patient served = q.dequeue();
    cout << "Served patient: " << served.fullName << endl;
    
    
    q.enqueue(Patient(2001, "NewArrival", 1, 13));
    cout << "Added NewArrival. Queue size is now: " << q.size() << endl;

   
    savePatients("patients_updated.txt", q);

    
    try {
        ClinicQueue<Patient> smallQueue(1);
        smallQueue.enqueue(Patient(1, "A", 1, 1));
        smallQueue.enqueue(Patient(2, "B", 1, 2)); // This should throw an error
    } catch (runtime_error& e) {
        cout << "[PASS] Boundary Test: Caught error -> " << e.what() << endl;
    }
}

void testA2_SortsAndSearch() {
    cout << "\n--- A2: Sorting and Binary Search ---" << endl;
    
    ClinicQueue<Patient> q(20);
    if (!loadPatients("patients.txt", q)) return;

    
    int n = q.size();
    Patient* arr = new Patient[n];
    for (int i = 0; i < n; i++) {
        arr[i] = q.getAt(i);
    }

    
    quickSort(arr, n, sortByTriageThenArrival);
    cout << "\nAfter QuickSort (Triage Level, then Arrival):" << endl;
    for (int i = 0; i < n; i++) cout << "  " << arr[i] << endl;

    
    insertionSort(arr, n, sortByID);

    int searchID = 1004;
    int index = binarySearchById(arr, n, searchID);
    if (index != -1) {
        cout << "\n[PASS] Binary search found ID " << searchID << " -> " << arr[index].fullName << endl;
    } else {
        cout << "\n[FAIL] Binary search did not find ID " << searchID << endl;
    }

    int missingID = 9999;
    index = binarySearchById(arr, n, missingID);
    if (index == -1) {
        cout << "[PASS] Binary search correctly returned -1 for missing ID " << missingID << endl;
    }

    delete[] arr; 
}

void testA4_Timing() {
    cout << "\n--- A4: Timing (Insertion vs QuickSort) ---" << endl;
    cout << "n\tInsertion(s)\tQuickSort(s)" << endl;
    cout << fixed << setprecision(5);

    ofstream csv("timing.csv");
    csv << "n,insertion,quicksort\n";

    for (int n = 1000; n <= 64000; n *= 2) {
        double totalIns = 0, totalQuick = 0;

        for (int trial = 0; trial < 3; trial++) {
            Patient* base = new Patient[n];
            for (int i = 0; i < n; i++) {
                base[i] = Patient(1000 + i, "P", (rand() % 3) + 1, i);
            }

            Patient* copy1 = new Patient[n];
            Patient* copy2 = new Patient[n];
            for (int i = 0; i < n; i++) { copy1[i] = base[i]; copy2[i] = base[i]; }

            auto start = chrono::high_resolution_clock::now();
            insertionSort(copy1, n, sortByTriageThenArrival);
            auto end = chrono::high_resolution_clock::now();
            totalIns += chrono::duration<double>(end - start).count();

            start = chrono::high_resolution_clock::now();
            quickSort(copy2, n, sortByTriageThenArrival);
            end = chrono::high_resolution_clock::now();
            totalQuick += chrono::duration<double>(end - start).count();

            delete[] base; delete[] copy1; delete[] copy2;
        }

        double avgIns = totalIns / 3.0;
        double avgQuick = totalQuick / 3.0;
        
        cout << n << "\t" << avgIns << "\t\t" << avgQuick << endl;
        csv << n << "," << avgIns << "," << avgQuick << "\n";
    }
    csv.close();
    cout << "Saved timing data to timing.csv\n";
}

int main() {
    srand(time(0)); 

    testA1_QueueOperations();
    testA2_SortsAndSearch();
    testA4_Timing();

    return 0;
}