# CS212 — Data Structures: Project Testing & Verification Report

* **University:** Misr University for Science & Technology (MUST) — College of Information Technology
* **Course:** CS212 — Data Structures (Fall 2026–2027)
* **Selected Project (Idea #17):** Veterinary Clinic Management System
* **Implementation:** Menu-Driven C++ Application with Manual Data Structures (`PetList`, `PetBST`, `PetQueue`, `VisitStack`)

---

## 1. Compliance with Mandatory Technical Specifications (R1–R10)

This testing suite directly verifies the technical requirements defined in **Section 03** and **Section 09** of the CS212 Course Project Guidelines:

* **R1–R5 (Manual Core Structures):** Verifies manual implementations of `VisitStack` (`push`, `pop`, `peek`, `isEmpty`, `size`), `PetQueue` (`enqueue`, `dequeue`, `front`, `isEmpty`, `size`), `PetList` (singly linked list insertion, deletion, search, traversal), and `PetBST` (insert, delete, unique-key search, inorder/preorder traversals, duplicate-key rejection).
* **R6 (Searching & Sorting):** Verifies **Linear Search** by pet name and **Insertion Sort** alphabetically by name, alongside **BST Search** by unique ID.
* **R7–R8 (Usable Menu & Validation):** Verifies repeatable console menu handling, non-numeric input recovery, out-of-range options, duplicate/negative IDs, negative ages, empty structures, and fixed-capacity bounds (`MAX = 100`).
* **R9 (Integrated End-to-End Workflow):** Verifies synchronization across `PetList`, `PetBST`, `PetQueue`, and `VisitStack` during registration, priority check-in, visit completion, updates, and deletions.
* **R10 (Testing Categories & Complexity):** Organized strictly according to the **6 Required Test Categories** in **Section 09 (Page 11)** along with Big-O complexity verification and system limitations.

---

## 2. Test Cases by Official CS212 Test Categories

### Category 1: Normal Operation
> *Guideline Expectation: Insert a valid record, search it, update it, process a waiting item, and display the outcome.*

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output (Verified) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-01** | Register valid new pet records (`Option 1`) | Register IDs `100` (`Joy`), `101` (`Meme`), `102` (`Mohsen`), `103` (`Tom`), `104` (`Lili`), `105` (`Coco`), `106` (`Cleo`), `107` (`Liza`), `108` (`Zico`), `109` (`Niko`) | Records are inserted into both `PetList` and `PetBST`, and confirmation is printed. | `Pet "<Name>" (ID: <ID>) registered successfully.` | **PASS** |
| **TC-02** | Check-in pets into waiting queue with priorities (`Option 2`) | Check-in ID `102` (Priority `2`), ID `101` (Priority `0`), ID `103` (Priority `1`) | Pets are inserted into `PetQueue` ordered by priority (`2` -> `1` -> `0`). | `Checked in <Name> (ID: <ID>) with priority <P>.` | **PASS** |
| **TC-03** | Process highest-priority waiting item (`Option 3`) | Choose `3`, enter treatment note: `"Controlled head bleeding, cleaned wound with antiseptic, prescribed topical ointment"` | Dequeues ID `102` (highest priority `2`), updates `medicalNote` in both `PetList` and `PetBST`, and pushes log to `VisitStack`. | `Treating Pet: Mohsen (ID: 102, Owner: Mostafa)` -> `Visit completed, medical note updated, and visit logged to stack.` | **PASS** |
| **TC-04** | Undo / Pop latest visit log from stack (`Option 4`) | Choose `4` after completing visit for ID `102` | Pops top entry from `VisitStack` (LIFO) and displays the removed log. | `Popped latest visit log: Pet #102 (Mohsen) - Controlled head bleeding, cleaned wound with antiseptic, prescribed topical ointment` | **PASS** |
| **TC-05** | Update existing pet record (`Option 8`) | Choose `8`, ID: `102`, Name: `Mohsen`, Species: `Turtle`, Age: `1`, Gender: `Male`, Owner: `Mostafa`, Phone: `01098765432`, Note: `"Deep wound bleeding on head"` | Updates record fields across both `PetList` and `PetBST` while preserving key `102`. | `Pet ID 102 updated in both Linked List and BST.` | **PASS** |
| **TC-06** | Delete existing pet record (`Option 9`) | Choose `9`, ID: `108` (`Zico`) | Removes node from both `PetList` and `PetBST` and decrements counts. | `Pet ID 108 deleted from records.` | **PASS** |

---

### Category 2: Empty Structure
> *Guideline Expectation: Attempt pop/dequeue/delete/search before any element exists (or when emptied); show safe message.*

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output (Verified) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-07** | Pop / Undo on empty `VisitStack` (`Option 4`) | Choose `4` when `VisitStack` has `0` elements | Safely detects `isEmpty()` without underflow crash and prints informative message. | `Visit history stack is empty. Nothing to undo/pop.` | **PASS** |
| **TC-08** | Dequeue / Complete Visit on empty `PetQueue` (`Option 3`) | Choose `3` when `waitingQueue.isEmpty()` is true | Safely returns without modifying records or pushing to stack. | `No pets currently waiting in the queue.` | **PASS** |
| **TC-09** | Display Overview when structures are empty (`Option 10`) | Choose `10` on fresh startup or empty stack | Reports `size = 0` and prints empty-state messages for empty structures. | `Visit Stack Size: 0` / `Visit history stack is empty.` | **PASS** |

---

### Category 3: Boundary and Single Item
> *Guideline Expectation: Operate with one record, first/last node, root-only BST, and maximum array capacity if relevant.*

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output (Verified) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-10** | Single-item / Root-only insertion & boundary ID `100` (`Option 1`) | Insert first record ID `100` (`Joy`) into empty `PetList` and `PetBST` | Creates `head` node in `PetList` and `root` node in `PetBST` (`size = 1`). | `Pet "Joy" (ID: 100) registered successfully.` | **PASS** |
| **TC-11** | Delete head/first node & leaf/tail node (`Option 9`) | Delete ID `108` (last/leaf node in skewed BST) and ID `103` (middle node) | Re-links `PetList` pointers and restructures `PetBST` pointers cleanly without memory leaks. | `Pet ID 108 deleted from records.` / `Pet ID 103 deleted from records and removed from waiting queue.` | **PASS** |
| **TC-12** | Fixed-capacity array guard (`MAX = 100`) | Attempt `PetList::insert`, `PetQueue::enqueue`, or `VisitStack::push` when `count == 100` | Enforces `MAX_LIST_SIZE`, `MAX_QUEUE_SIZE`, and `MAX_VISITS` (`100`) bounds and rejects overflow safely. | `Error: Waiting queue is full.` / `Error: Could not insert into linked list (may be full).` | **PASS** |

---

### Category 4: Invalid Data
> *Guideline Expectation: Non-numeric choices, duplicate ID, nonexistent key, unexpected input; show recovery.*

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output (Verified) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-13** | Non-integer & out-of-range menu choices | Enter `"abs"`, then `19` at main menu prompt | `cin.clear()` + `cin.ignore()` recovers stream cleanly; loop re-prompts without crashing. | `Invalid input. Please enter a valid integer.` / `Invalid menu option. Try again.` | **PASS** |
| **TC-14** | Duplicate Pet ID registration (`Option 1`) | Choose `1`, enter existing ID `102` | `PetBST::search(102)` detects duplicate key and aborts insertion. | `Error: A pet with ID 102 already exists.` | **PASS** |
| **TC-15** | Non-positive ID & negative age validation (`Option 1`) | Enter ID `-1`; then enter ID `109` with Age `-2` | `validatePetID()` and `validatePetInput()` reject invalid values with clear errors. | `Error: ID must be greater than 0.` / `Error: Pet age cannot be negative.` | **PASS** |
| **TC-16** | Non-existent Pet ID in Queue, BST Search, and Delete (`Options 2, 5, 9`) | Check-in ID `109` (before registration); Search ID `1`; Delete ID `109` (before registration) | Safely reports missing record without altering any structure. | `Error: Pet ID 109 not found. Register the pet first.` / `No pet found with ID 1.` / `Error: Pet with ID 109 was not found.` | **PASS** |
| **TC-17** | Search for non-existent Pet Name (`Option 6`) | Choose `6`, enter `"Asya"` | Completes linear scan and reports zero matches cleanly. | `No pet found with name "Asya".` | **PASS** |

---

### Category 5: Integration (End-to-End Cross-Structure Workflow)
> *Guideline Expectation: Follow one record or action from creation through multiple structures, explaining synchronization.*

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output (Verified) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-18** | End-to-End Lifecycle of `Mohsen` (`ID: 102`) | 1) Register `102` (`Option 1`) -> 2) Enqueue `102` with Priority `2` (`Option 2`) -> 3) Complete Visit (`Option 3`) -> 4) Pop Log (`Option 4`) -> 5) Search ID `102` (`Option 5`) -> 6) Update `102` (`Option 8`) | Demonstrates coordinated data flow across all 4 structures: `PetList` & `PetBST` store/update medical notes, `PetQueue` prioritizes emergency triage, and `VisitStack` logs/reverts completed visits. | All 6 stages executed sequentially with consistent medical note and state updates across `PetList` and `PetBST`. | **PASS** |
| **TC-19** | Cross-structure deletion synchronization (`Option 9` + `Option 10`) | Delete `ID: 103` (`Tom`) while queued at Priority `1`, then run `Option 10` (`System Overview`) | Removes `103` from `PetList`, `PetBST`, and `PetQueue` simultaneously; `PetList Size` and `PetBST Size` remain equal (`8`), and `103` disappears from `Waiting Queue`. | `Pet ID 103 deleted from records and removed from waiting queue.` -> `Linked List Size: 8`, `BST Size: 8`, `Waiting Queue Size: 2`. | **PASS** |

---

### Category 6: Algorithm and Complexity Verification
> *Guideline Expectation: Show searching/sorting output and explain approximate Big-O of the chosen operations.*

| Test ID | Algorithm / Operation | Input Data / Action | Output & Complexity Verification | Time Complexity | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-20** | **Binary Search Tree Lookup** (`Option 5`) & **Traversals** (`Option 10`) | Search ID `102`; run `Inorder` & `Preorder` traversals on IDs `100..107` | Located `ID: 102` directly; `Inorder` printed sorted IDs `100` to `107`; `Preorder` reflected insertion order (`100` -> `107`). | Search: $O(\log n)$ avg, $O(n)$ worst (skewed)<br>Traversal: $O(n)$ | **PASS** |
| **TC-21** | **Linear Search by Name** (`Option 6`) | Search `"Liza"` (`ID: 107`) and `"Niko"` (`ID: 109`) across unsorted linked list records | Scans copied array sequentially from index `0` to $n-1$ and outputs all matching records. | Best: $O(1)$<br>Average / Worst: $O(n)$ | **PASS** |
| **TC-22** | **Insertion Sort by Name** (`Option 7`) | Sort 9 registered pets (`Joy`, `Meme`, `Mohsen`, `Tom`, `Lili`, `Coco`, `Cleo`, `Liza`, `Zico`) alphabetically | Outputs sorted order: `1. Cleo`, `2. Coco`, `3. Joy`, `4. Lili`, `5. Liza`, `6. Meme`, `7. Mohsen`, `8. Tom`, `9. Zico`. | Best: $O(n)$<br>Average / Worst: $O(n^2)$ | **PASS** |

---

## 3. Summary of Big-O Complexity & System Limitations (Requirement R10)

| Data Structure / Algorithm | Core Operation | Time Complexity | Space Complexity | Implementation Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Singly Linked List (`PetList`)** | Insert at tail / Search / Delete | $O(n)$ | $O(n)$ | Stores full `Pet` records dynamically up to `MAX_LIST_SIZE = 100`. |
| **Binary Search Tree (`PetBST`)** | Search / Insert / Delete | $O(\log n)$ avg, $O(n)$ worst | $O(n)$ | Indexed by unique `Pet.id`; degrades to $O(n)$ if IDs are inserted sequentially. |
| **Priority Queue (`PetQueue`)** | `enqueue` (sorted insert) / `dequeue` | `enqueue`: $O(n)$, `dequeue`: $O(n)$ | $O(1)$ fixed (`100`) | Array-based priority queue (`0` = normal, `1` = urgent, `2` = emergency). |
| **Stack (`VisitStack`)** | `push` / `pop` / `peek` | $O(1)$ | $O(1)$ fixed (`100`) | LIFO log of completed visit notes enabling instant undo (`Option 4`). |
| **Linear Search (`searchPetByName`)** | Search by `Pet.name` | $O(n)$ | $O(n)$ temp array | Necessary because `PetBST` is keyed by `id`, not `name`. |
| **Insertion Sort (`sortPetsByName`)** | Sort records alphabetically | $O(n^2)$ worst, $O(n)$ best | $O(n)$ temp array | Efficient for small-to-medium clinic datasets (`n <= 100`) without altering list order. |

### Identified System Limitations (Required by R10)
1. **Unbalanced BST Degradation:** Inserting sequential Pet IDs (e.g., `100` to `109`) creates a right-skewed tree, degrading BST search from $O(\log n)$ to $O(n)$. An **AVL Tree** self-balancing mechanism would guarantee $O(\log n)$ worst-case lookup.
2. **Volatile In-Memory Storage & Fixed Array Caps:** `PetQueue` and `VisitStack` use fixed arrays of size `100`, and records are not persisted to disk files upon exit (`Option 0`).
