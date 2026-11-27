# CS212 – Veterinary Clinic Management System

A console-based Veterinary Clinic Management System developed in C++ using Object-Oriented Programming and manually implemented Data Structures to manage pet registrations, clinic visits, waiting lists, and visit history.

---

## 1. Project Overview

The **Veterinary Clinic Management System** is a C++ application designed to simulate the basic operations of a veterinary clinic.

The system provides an organized way to register pets, store their information, search for pet records, manage the clinic's waiting queue, process visits, and track recently completed visits.

The project demonstrates the practical application of fundamental Data Structures and algorithms, integrating multiple structures to perform real-world clinic management operations efficiently.

---

## 2. System Features

### Pet Management
- Register new pets with unique IDs.
- Store pet information, including name, species, age, gender, owner details, phone number, and medical notes.
- Prevent duplicate Pet IDs.
- Validate user inputs and required information.
- Delete existing pet records.
- Search for pets by their unique ID.
- Display all registered pets.

### Clinic Operations
- Check in registered pets for examination.
- Prevent a pet from being added to the waiting queue more than once.
- Organize waiting pets according to priority.
- Process the next pet for examination.
- Record completed visits.
- Display recent visit history.
- Sort registered pets alphabetically by name.

---

## 3. Data Structures & Algorithms

The project implements its data structures manually without relying on STL containers such as `list`, `queue`, `stack`, or `map` for the core implementations.

### 1. Linked List

**Purpose:** Stores and manages pet records.

**Implementation:**
- Singly Linked List.
- Each node contains a pet record and a pointer to the next node.
- Supports insertion, deletion, searching, traversal, and displaying pet records.
- Maintains the number of stored records.
- Uses a destructor to release dynamically allocated nodes.

**Operations:**
- `insert()`
- `deletePet()`
- `search()`
- `display()`
- `isEmpty()`
- `size()`
- `copyToArray()`

---

### 2. Binary Search Tree (BST)

**Purpose:** Organizes pet records by their unique IDs to support searching and management.

**Implementation:**
- Each node stores a pet record.
- Smaller IDs are stored in the left subtree.
- Larger IDs are stored in the right subtree.
- Insertion, searching, and deletion are implemented recursively.
- Duplicate IDs are rejected.
- Deletion handles all three cases: leaf node, one child, and two children.
- The inorder traversal displays pets in ascending order of ID.
- The preorder traversal displays the tree structure order.
- A destructor clears the dynamically allocated tree nodes.

**Operations:**
- `insert()`
- `search()`
- `deletePet()`
- `updatePet()`
- `inorder()`
- `preorder()`
- `clear()`
- `isEmpty()`
- `size()`

---

### 3. Priority Queue

**Purpose:** Organizes pets waiting for examination according to their priority.

**Implementation:**
- Implemented using a fixed-size array.
- Maximum capacity: 100 pets.
- Higher-priority pets are placed before lower-priority pets.
- Pets with equal priority maintain their insertion order.
- The front element represents the next pet to be examined.

**Operations:**
- `enqueue()`
- `dequeue()`
- `front()`
- `rear()`
- `contains()`
- `removeById()`
- `display()`
- `isEmpty()`
- `isFull()`
- `size()`

---

### 4. Stack

**Purpose:** Stores completed clinic visits and provides access to recent visit history.

**Implementation:**
- Implemented using a fixed-size array.
- Follows the LIFO (Last In, First Out) principle.
- The most recently completed visit is displayed first.
- Maximum capacity: 100 visit records.

**Operations:**
- `push()`
- `pop()`
- `peek()`
- `display()`
- `clear()`
- `isEmpty()`
- `isFull()`
- `size()`

---

### 5. Sorting Algorithm – Bubble Sort

**Purpose:** Sorts registered pets alphabetically by name.

**Implementation:**
- Copies pet records from the Linked List into an array.
- Uses the Bubble Sort algorithm to sort the copied records.
- Compares adjacent pet names and swaps them when necessary.
- Displays the sorted results without changing the original Linked List order.

**Time Complexity:** O(n²)

---

## 4. System Architecture

The system is organized into separate classes, each responsible for a specific data structure or operation.

| Class | Responsibility |
|---|---|
| `Pet` | Stores pet information |
| `PetList` | Manages pet records using a Linked List |
| `PetBST` | Organizes and searches pet records using a Binary Search Tree |
| `PetQueue` | Manages the waiting list using a Priority Queue |
| `VisitStack` | Stores completed visits using a Stack |
| `ClinicOperations` | Coordinates registration, check-in, visit completion, validation, and sorting |

The `ClinicOperations` class connects the different data structures to ensure that clinic operations work together.

---

## 5. Technologies Used

- **Programming Language:** C++
- **Programming Concepts:** Object-Oriented Programming (OOP)
- **Data Structures:** Linked List, Binary Search Tree, Priority Queue, Stack
- **Algorithms:** Recursive Searching, Recursive Insertion, Recursive Deletion, Bubble Sort
- **Memory Management:** Dynamic Memory Allocation and Destructors
- **Development Environment:** Visual Studio / Visual Studio Code
- **Version Control:** Git & GitHub

---

## 6. How to Run the Project

### Requirements

- A C++ compiler such as GCC or MinGW.
- Visual Studio or Visual Studio Code.

### Steps

1. Clone or download the repository.
2. Open the project folder in your development environment.
3. Make sure a C++ compiler is installed and configured.
4. Compile the source files.
5. Run the generated executable.

### Compilation

Using GCC:

```bash
g++ *.cpp -o VeterinaryClinic
```

### Run on Windows

```bash
VeterinaryClinic.exe
```

### Run on Linux / macOS

```bash
./VeterinaryClinic
```

---

## 7. Program Menu

The application provides the following interactive menu:

```text
====================================
       VETERINARY CLINIC SYSTEM
====================================

1. Register New Pet
2. Search Pet By ID
3. Delete Pet
4. Display All Pets
5. Check In Pet
6. Complete Visit
7. Display Recent Visit History
8. Sort Pets By Name
0. Exit

====================================
Enter your choice:
```

---

## 8. Team Members & Responsibilities

| Team Member | Team Member id | Responsibility |
|---|---|---|
| Malak Sherif Abdelaziz | 200076464 | Linked List Implementation |
| Salma Sameh Ahmed | 200067927 | Binary Search Tree Implementation |
| Dalia Mahmoud Muhyi | 200069159 |Queue Implementation |
| Nagwa Hossam Khalil | 200068520 |Stack Implementation |
| Arwa Tamer Mohamed | 200067685 |Clinic Operations, Searching, Sorting, Validation & int main |

---

## 9. Course Information

**Course:** CS212 – Data Structures  
**Project:** Veterinary Clinic Management System  
**Academic Year:** 2026–2027  
**Semester:** Fall

---

## 10. Project Objectives

The main objectives of this project are:

- Apply Data Structures concepts to a practical real-world problem.
- Understand how different data structures can work together in one system.
- Implement data structures manually using C++.
- Practice Object-Oriented Programming.
- Improve problem-solving and algorithmic thinking.
- Apply searching, sorting, insertion, deletion, traversal, and memory management techniques.
- Develop teamwork and collaborative programming skills using GitHub.

---

## 11. Conclusion

The Veterinary Clinic Management System demonstrates how fundamental Data Structures can be integrated into a practical C++ application.

By using a Linked List for pet records, a Binary Search Tree for ID-based management, a Priority Queue for waiting pets, and a Stack for visit history, the project provides an organized solution for managing the essential operations of a veterinary clinic while demonstrating the practical importance of Data Structures and algorithms.
