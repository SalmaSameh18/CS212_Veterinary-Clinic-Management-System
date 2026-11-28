# CS212 – Data Structures Course Project
## Idea #17: Veterinary Clinic Management System

* **University:** Misr University for Science & Technology (MUST)
* **College:** College of Information Technology
* **Course:** CS212 – Data Structures (Practical Part)
* **Semester:** Fall 2026–2027
* **Language & Standard:** C++ (C++17), 100% Manual Data Structure Implementation (Zero STL Containers)

---

## 1. Project Overview & Scope

The **Veterinary Clinic Management System** is an integrated, menu-driven C++ console application designed to streamline daily veterinary clinic operations. It manages pet medical records, coordinates patient check-ins using urgency-based priority queuing, tracks completed consultations in a LIFO visit log, and provides fast record lookup and alphabetical sorting.

### Integrated End-to-End Clinic Workflow
1. **Registration:** A new pet is validated (positive unique ID, non-empty required fields, non-negative age) and inserted into the **Singly Linked List (`PetList`)**, with its key mirrored into the **Binary Search Tree (`PetBST`)** for fast $O(\log n)$ indexing.
2. **Triage & Check-In:** Registered pets are checked into the waiting room via a **Priority Queue (`PetQueue`)** based on medical urgency (`0 = Normal`, `1 = Urgent`, `2 = Emergency`), preserving FIFO order among equal priorities.
3. **Consultation & Completion:** The highest-priority pet is dequeued, treated, and has its `medicalNote` updated consistently across both `PetList` and `PetBST`. A timestamped/formatted summary of the visit is then pushed onto the **Visit History Stack (`VisitStack`)**.
4. **Review & Undo:** Staff can inspect or pop the most recent visit log from `VisitStack`, search pets by ID (`PetBST`) or Name (`Linear Search`), sort pets alphabetically (`Insertion Sort`), and update or delete records across all synchronized structures.

---

## 2. Repository & Source File Structure

Recommended repository layout per CS212 submission guidelines:

```text
CS212_Veterinary_Clinic/
├── README.md
├── Source_Code/
│   ├── Pet.h
│   ├── pet_BST.h
│   ├── Pet_BST.cpp
│   ├── Pet_List.h
│   ├── Pet_List.cpp
│   ├── Pet_Queue.h
│   ├── Pet_Queue.cpp
│   ├── Pet_Stack.h
│   ├── Pet_Stack.cpp
│   ├── Pet_Clinic_Operations.h
│   ├── Pet_Clinic_Operation.cpp
│   ├── pet_main.h
│   └── pet_main.cpp
├── Report.pdf
├── Screenshots/
└── Tests/
```

### Source Files Breakdown

| File(s) | Module / Class | Responsibility |
| :--- | :--- | :--- |
| `Pet.h` | `struct Pet` | Core data model (`id`, `name`, `species`, `age`, `gender`, `owner`, `phone`, `medicalNote`) with default constructor |
| `Pet_List.h`, `Pet_List.cpp` | `PetList` | Dynamic Singly Linked List storing complete pet medical records |
| `pet_BST.h`, `Pet_BST.cpp` | `PetBST` | Binary Search Tree keyed by unique `Pet::id` for fast search and sorted traversal |
| `Pet_Queue.h`, `Pet_Queue.cpp` | `PetQueue` | Array-based Priority Queue managing waiting room patients (`MAX_QUEUE_SIZE = 100`) |
| `Pet_Stack.h`, `Pet_Stack.cpp` | `VisitStack` | Array-based LIFO Stack tracking recent completed visits (`MAX_VISITS = 100`) |
| `Pet_Clinic_Operations.h`, `Pet_Clinic_Operation.cpp` | `ClinicOperations` | Controller class handling input validation, cross-structure synchronization, searching, sorting, and the interactive menu |
| `pet_main.h`, `pet_main.cpp` | `main()` | Aggregates module headers and launches `ClinicOperations::runMenu()` |

---

## 3. Compliance with CS212 Technical Specifications (R1–R10)

| Req | Requirement | Implementation Details |
| :--- | :--- | :--- |
| **R1** | **Original C++ Implementation** | All data structures (`PetList`, `PetBST`, `PetQueue`, `VisitStack`) are built manually using pointers, dynamic memory (`new`/`delete`), and fixed-capacity arrays—without `std::list`, `std::stack`, `std::queue`, or `std::map`. |
| **R2** | **Stack (`VisitStack`)** | Implements `push`, `pop`, `peek`, `isEmpty`, `isFull`, `size`, `display`, and `clear` to maintain a LIFO log of completed visits and support popping/undoing the latest visit log. |
| **R3** | **Queue (`PetQueue`)** | Implements `enqueue`, `dequeue`, `front`, `rear`, `contains`, `removeById`, `isEmpty`, `isFull`, `size`, and `display` for urgency-aware waiting room management (ties follow FIFO). |
| **R4** | **Linked List (`PetList`)** | Implements node-based `insert`, `deletePet`, `updatePet`, `search`, `display`, `copyToArray`, `isEmpty`, `size`, and destructor cleanup (`~PetList`). |
| **R5** | **Binary Search Tree (`PetBST`)** | Keyed by unique `Pet::id`; supports `insert` (rejecting duplicate IDs), `deletePet` (0, 1, and 2-child cases via inorder successor), `search`, `updatePet`, `inorder`, `preorder`, and `clear`. |
| **R6** | **Searching & Sorting** | **BST Search** for unique ID lookup; **Linear Search** for non-unique pet names; **Insertion Sort** for alphabetical ordering by pet name on a copied array. |
| **R7** | **Usable Console Application** | Repeatable 11-option menu (options `1–10` plus safe `0` Exit) with formatted outputs and full CRUD support. |
| **R8** | **Input & State Validation** | Guards against non-integer menu/numeric inputs (`cin.fail()` recovery), non-positive IDs, negative ages, empty required strings, duplicate IDs, duplicate queue check-ins, empty-structure operations, and full-capacity limits (`MAX = 100`). |
| **R9** | **Integrated Behavior** | Registering, updating, treating (`completeVisit`), and deleting a pet automatically synchronizes state across `PetList`, `PetBST`, `PetQueue`, and `VisitStack`. |
| **R10** | **Complexity & Limitations** | Includes Big-O analysis below and explicitly documents array-capacity and tree-balance limitations. |

---

## 4. Searching, Sorting & Big-O Complexity Analysis

### Algorithm Justifications
* **BST Search (by Pet ID):** Chosen because `Pet::id` is a unique primary key, enabling $O(\log n)$ average lookup time instead of scanning all records sequentially.
* **Linear Search (by Pet Name):** Chosen because multiple pets can share the same name and names are not the BST key; inspects all copied records in $O(n)$ time to return every matching pet.
* **Insertion Sort (by Pet Name):** Chosen because clinic datasets are bounded (`MAX_CLINIC_PETS = 100`), it sorts in-place on a copied array with $O(1)$ auxiliary space, runs in $O(n)$ on nearly-sorted data, and is **stable** (preserving relative registration order for pets with identical names).

### Time & Space Complexity Summary

| Data Structure / Algorithm | Operation | Average Time | Worst-Case Time | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **`PetList` (Singly Linked List)** | `insert` (at tail) | $O(n)$ | $O(n)$ | $O(1)$ per node |
| | `search` / `deletePet` / `updatePet` | $O(n)$ | $O(n)$ | $O(1)$ |
| | `display` / `copyToArray` | $O(n)$ | $O(n)$ | $O(1)$ |
| **`PetBST` (Binary Search Tree)** | `insert` / `search` / `deletePet` / `updatePet` | $O(\log n)$ | $O(n)$ *(skewed)* | $O(h)$ recursion stack |
| | `inorder` / `preorder` / `clear` | $O(n)$ | $O(n)$ | $O(h)$ recursion stack |
| **`PetQueue` (Priority Queue)** | `enqueue` (sorted insertion) | $O(n)$ | $O(n)$ | $O(1)$ |
| | `dequeue` (shift elements) | $O(n)$ | $O(n)$ | $O(1)$ |
| | `front` / `rear` / `isEmpty` / `size` | $O(1)$ | $O(1)$ | $O(1)$ |
| **`VisitStack` (Array Stack)** | `push` / `pop` / `peek` / `isEmpty` / `size` | $O(1)$ | $O(1)$ | $O(1)$ |
| **Linear Search (by Name)** | `searchPetByName` | $O(n)$ | $O(n)$ | $O(n)$ *(temp array)* |
| **Insertion Sort (by Name)** | `sortPetsByName` | $O(n^2)$ | $O(n^2)$ ($O(n)$ best) | $O(n)$ *(temp array)* |

### Known System Limitations
1. **Fixed Capacity Bounds:** `PetList`, `PetQueue`, `VisitStack`, and temporary search/sort buffers are capped at `100` records (`MAX = 100`).
2. **Unbalanced BST Worst Case:** `PetBST` is a standard Binary Search Tree rather than a self-balancing AVL tree; inserting strictly sorted IDs degrades lookup time from $O(\log n)$ to $O(n)$.
3. **In-Memory Storage Only:** Records exist in RAM during runtime and are not persisted to disk upon exit.

---

## 5. How to Compile & Run

Open a terminal inside the directory containing all `.h` and `.cpp` files (e.g., `Source_Code/`):

### Windows (PowerShell / CMD with `g++`)
```powershell
g++ -std=c++17 -Wall -Wextra pet_main.cpp Pet_List.cpp Pet_BST.cpp Pet_Queue.cpp Pet_Stack.cpp Pet_Clinic_Operation.cpp -o clinic_app.exe
.\clinic_app.exe
```

### Linux / macOS / Git Bash
```bash
g++ -std=c++17 -Wall -Wextra pet_main.cpp Pet_List.cpp Pet_BST.cpp Pet_Queue.cpp Pet_Stack.cpp Pet_Clinic_Operation.cpp -o clinic_app
./clinic_app
```

---

## 6. Interactive Menu Options

```text
========== VETERINARY CLINIC MENU ==========
1. Register New Pet
2. Check In Pet to Waiting Queue (Priority)
3. Complete Next Visit (Queue -> Update Record -> Stack)
4. Undo / Pop Last Visit Log (Stack)
5. Search Pet by ID (BST)
6. Search Pet by Name (Linear Search)
7. Sort & Display Pets by Name (Insertion Sort)
8. Update Pet Record
9. Delete Pet Record
10. Display Full System Overview
0. Exit
```

---

## 7. Team Members & Contributions

* **Registered Practical Section:** `[7182]`
* **Team ID / Number:** `[17]`

| # | Student Full Name | University ID | Assigned Role & Deliverables |
| :--- | :--- | :--- | :--- |
| 1 | Salma Sameh Ahmed | 200067927 | `PetBST` implementation (`pet_BST.h`, `Pet_BST.cpp`) & ID search integration |
| 2 | Malak Sherif Abdelaziz | 200076464 | `PetList` implementation (`Pet_List.h`, `Pet_List.cpp`) & `Pet.h` data model |
| 3 | Dalia Mahmoud Muhyi | 200069159 | `PetQueue` implementation (`Pet_Queue.h`, `Pet_Queue.cpp`) & triage workflow |
| 4 | Nagwa Hossam Khalil | 200068520 | `VisitStack` implementation (`Pet_Stack.h`, `Pet_Stack.cpp`) & visit logging |
| 5 | Arwa Tamer Mohamed | 200067685 | `ClinicOperations` (`Pet_Clinic_Operations.h`, `Pet_Clinic_Operation.cpp`), validation, sorting & integration |
