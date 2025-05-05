# Hospital Patient Record Management System

## Overview
This project is a C++ console-based simulation of a hospital management system. It provides basic functionalities to register patients, manage emergency room queues based on condition priority, and maintain treatment records per patient. The system is designed to mimic how real-time hospital operations might handle patient intake, treatment logging, and information retrieval.

## Features
-  Add new patients with ID, name, age, and condition.
-  View all registered patients.
-  Search for a patient by ID and view their full information (including treatment history).
-  Add patients to an emergency queue with criticality-based priority.
-  Record treatments only for existing patients.
-  Undo the last treatment entry (stack-based).
-  View complete treatment history per patient.
-  View complete patient history (ID, name, condition, and their treatments if available).


## Data Structures Used
- **Singly Linked List**: To store the general patient records.
- **Priority Queue (custom implementation)**: For handling the emergency room queue, prioritizing critical conditions.
- **Stack**: To enable undo functionality for the most recent treatment operation.
- **Maps (unordered_map)**: To map patient IDs to their treatment records for fast access and validation.

### Requirements:
- Any C++ compiler (e.g., g++, clang++)
- A terminal or command prompt

Menu Options (Example Run):

--- Hospital System Menu ---
1. Add Patient
2. Add Patient to Emergency Queue
3. Record Treatment
4. Undo Last Treatment
5. Show Patient History
6. Exit

After adding a patient, their full info will be printed as confirmation.
Treatments can only be added for patients already registered in the system.
Patient Info will show treatment history if any; otherwise, it informs you that there's no treatment.


Example Treatment Recording:
Enter Patient ID: P001
Enter Treatment: Antibiotics - 500mg daily
-> Treatment recorded successfully

