#include <iostream>
#include <string>
#include <map>
using namespace std;

// patient structure
struct Patient {
    string id;
    string name;
    int age;
    string condition;
};

// treatment node for stack
struct Treatment {
    string details;
    Treatment* next;
};

// Stack to store treatments
class TreatmentStack {
private:
    Treatment* top;
public:
    TreatmentStack() {
       top = nullptr;
    }


    void push(string details) {
        Treatment* newNode = new Treatment;
        newNode->details = details;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "No treatments to undo.\n";
            return;
        }
        cout << "Undoing treatment: " << top->details << endl;
        Treatment* temp = top;
        top = top->next;
        delete temp;
    }

    void display() {
        if (!top) {
            cout << "No treatments recorded.\n";
            return;
        }
        Treatment* temp = top;
        while (temp) {
            cout << "  - Treatment: " << temp->details << endl;
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Priority queue node
struct PriorityNode {
    Patient patient;
    int priority;
    PriorityNode* next;
};

// Priority queue for emergencies
class PriorityQueue {
private:
    PriorityNode* front;
public:
    PriorityQueue() {
        front = nullptr;
    }  


    void enqueue(Patient patient, int priority) {
        PriorityNode* newNode = new PriorityNode;
        newNode->patient = patient;
        newNode->priority = priority;
        newNode->next = nullptr;

        if (front == nullptr || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            PriorityNode* temp = front;

            while (temp->next && temp->next->priority <= priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        cout << "Added to emergency queue: " << patient.name << " (Priority: " << priority << ")\n";
    }
};

map<string, Patient> patients;
map<string, TreatmentStack> treatments;
int main() {
    PriorityQueue emergencyList;
    string userChoice;

    while (true) {
        // Show menu
        cout << "\n--- Hospital Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Add to Emergency Queue\n";
        cout << "3. Add Treatment\n";
        cout << "4. Remove Last Treatment\n";
        cout << "5. Show All Patients\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        // Add new patient
        if (userChoice == "1") {
            Patient newPatient;
            cout << "Enter ID: ";
            cin >> newPatient.id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, newPatient.name);
            cout << "Enter Age: ";
            cin >> newPatient.age;
            cin.ignore();
            cout << "Enter Condition: ";
            getline(cin, newPatient.condition);

            patients[newPatient.id] = newPatient;
            cout << "Patient added.\n";
        }

        // Add patient to emergency queue
        else if (userChoice == "2") {
            string patientId;
            int priority;
            cout << "Enter Patient ID: ";
            cin >> patientId;
            cout << "Enter Priority (1=High, 2=Medium, 3=Low): ";
            cin >> priority;

            if (patients.count(patientId)) {
                emergencyList.enqueue(patients[patientId], priority);
            } else {
                cout << "Patient not found.\n";
            }
        }

        // Add treatment for a patient
        else if (userChoice == "3") {
            string patientId, treatmentInfo;
            cout << "Enter Patient ID: ";
            cin >> patientId;
            cin.ignore();
            if (patients.count(patientId)) {
                cout << "Enter Treatment Info: ";
                getline(cin, treatmentInfo);
                treatments[patientId].push(treatmentInfo);
                cout << "Treatment saved.\n";
            } else {
                cout << "Patient not found.\n";
            }
        }

        // Undo last treatment
        else if (userChoice == "4") {
            string patientId;
            cout << "Enter Patient ID: ";
            cin >> patientId;
            if (treatments.count(patientId)) {
                treatments[patientId].pop();
            } else {
                cout << "No treatments found.\n";
            }
        }

        // Show all patient info
        else if (userChoice == "5") {
            for (auto& item : patients) {
                Patient newPatient = item.second;
                cout << "\nID: " << newPatient.id << ", Name: " << newPatient.name
                     << ", Age: " << newPatient.age << ", Condition: " << newPatient.condition << endl;
                cout << "Treatments:\n";

                if (treatments.count(newPatient.id)) {
                    treatments[newPatient.id].display();
                } else {
                    cout << "  No treatments recorded.\n";
                }
            }
        }

        // Exit the system
        else if (userChoice == "6") {
            cout << "Goodbye!\n";
            break;
        }

        // If the user enters something wrong
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
 
