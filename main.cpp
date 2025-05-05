#include <iostream>
#include <string>
#include <map>
using namespace std;

// ========== Patient Structure ==========
struct Patient {
    string id;
    string name;
    int age;
    string condition;
};

// ========== Treatment Structure & Stack ==========
struct Treatment {
    string treatmentDetails;
    Treatment* next;
};

class TreatmentStack {
private:
    Treatment* top;
public:
    TreatmentStack() : top(nullptr) {}

    void push(string details) {
        Treatment* newNode = new Treatment;
        newNode->treatmentDetails = details;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "No treatments to undo.\n";
            return;
        }
        cout << "Undoing treatment: " << top->treatmentDetails << endl;
        Treatment* temp = top;
        top = top->next;
        delete temp;
    }

    void display() {
        Treatment* temp = top;
        if (!temp) {
            cout << "No treatments recorded.\n";
            return;
        }
        while (temp) {
            cout << "  - Treatment: " << temp->treatmentDetails << endl;
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// ========== Priority Queue ==========
struct PriorityPatientNode {
    Patient data;
    int priority;
    PriorityPatientNode* next;
};

class PriorityQueue {
private:
    PriorityPatientNode* front;
public:
    PriorityQueue() : front(nullptr) {}

    void enqueue(Patient p, int priority) {
        PriorityPatientNode* newNode = new PriorityPatientNode;
        newNode->data = p;
        newNode->priority = priority;
        newNode->next = nullptr;

        if (!front || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            PriorityPatientNode* temp = front;
            while (temp->next && temp->next->priority <= priority)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        cout << "Added to emergency queue: " << p.name << " (Priority: " << priority << ")\n";
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// ========== General Patient Records ==========
map<string, Patient> patientMap; // key = ID
map<string, TreatmentStack> treatmentHistory; // key = ID

// ========== Main Program ==========
int main() {
    PriorityQueue emergencyQueue;
    string choice;

    while (true) {
        cout << "\n--- Hospital System Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Patient to Emergency Queue\n";
        cout << "3. Record Treatment\n";
        cout << "4. Undo Last Treatment\n";
        cout << "5. Show Patient History\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1") {
            Patient p;
            cout << "Enter ID: "; cin >> p.id;
            cin.ignore();
            cout << "Enter Name: "; getline(cin, p.name);
            cout << "Enter Age: "; cin >> p.age;
            cin.ignore();
            cout << "Enter Condition: "; getline(cin, p.condition);

            patientMap[p.id] = p;
            cout << "\nPatient added successfully:\n";
            cout << "ID: " << p.id << ", Name: " << p.name << ", Age: " << p.age << ", Condition: " << p.condition << endl;
        }
        else if (choice == "2") {
            string id;
            int priority;
            cout << "Enter Patient ID: "; cin >> id;
            cout << "Enter Priority (1=critical, 2=medium, 3=low): "; cin >> priority;
            if (patientMap.find(id) != patientMap.end()) {
                emergencyQueue.enqueue(patientMap[id], priority);
            } else {
                cout << "Error: Patient ID not found.\n";
            }
        }
        else if (choice == "3") {
            string id, details;
            cout << "Enter Patient ID: "; cin >> id;
            cin.ignore();
            if (patientMap.find(id) != patientMap.end()) {
                cout << "Enter Treatment Details: "; getline(cin, details);
                treatmentHistory[id].push(details);
                cout << "Treatment recorded.\n";
            } else {
                cout << "Error: Patient ID not found.\n";
            }
        }
        else if (choice == "4") {
            string id;
            cout << "Enter Patient ID: "; cin >> id;
            if (treatmentHistory.find(id) != treatmentHistory.end()) {
                treatmentHistory[id].pop();
            } else {
                cout << "No treatment history found for this ID.\n";
            }
        }
        else if (choice == "5") {
            cout << "\n--- Full Patient History ---\n";
            if (patientMap.empty()) {
                cout << "No patients available.\n";
            } else {
                for (auto& entry : patientMap) {
                    Patient p = entry.second;
                    cout << "\nID: " << p.id << ", Name: " << p.name << ", Age: " << p.age << ", Condition: " << p.condition << endl;
                    cout << "Treatments:" << endl;
                    if (treatmentHistory.find(p.id) != treatmentHistory.end())
                        treatmentHistory[p.id].display();
                    else
                        cout << "  No treatments recorded.\n";
                }
            }
        }

        else if (choice == "7") {
            cout << "Exiting system. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}
