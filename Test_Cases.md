# Veterinary Clinic Management System — Test Cases

## Category 1: Normal Operation

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-01** | Register new pet records (`Option 1`) | Register IDs `100` (`Joy`), `101` (`Meme`), `102` (`Mohsen`), `103` (`Tom`), `104` (`Lili`), `105` (`Coco`), `106` (`Cleo`), `107` (`Liza`), `108` (`Zico`), `109` (`Niko`) | Records are added to `PetList` and `PetBST` and confirmation is displayed. | `Pet "<Name>" (ID: <ID>) registered successfully.` | **PASS** |
| **TC-02** | Check-in pets to waiting queue (`Option 2`) | Check-in ID `102` (Priority `2`), ID `101` (Priority `0`), ID `103` (Priority `1`) | Pets are enqueued into `PetQueue` ordered by priority (`2` -> `1` -> `0`). | `Checked in <Name> (ID: <ID>) with priority <P>.` | **PASS** |
| **TC-03** | Complete next visit (`Option 3`) | Choose `3`, enter treatment note: `"Controlled head bleeding, cleaned wound with antiseptic, prescribed topical ointment"` | Dequeues ID `102` (Priority `2`), updates `medicalNote` in `PetList` and `PetBST`, and pushes log to `VisitStack`. | `Treating Pet: Mohsen (ID: 102, Owner: Mostafa)` -> `Visit completed, medical note updated, and visit logged to stack.` | **PASS** |
| **TC-04** | Undo / Pop last visit log (`Option 4`) | Choose `4` after completing visit for ID `102` | Pops the latest visit entry from `VisitStack` and displays it. | `Popped latest visit log: Pet #102 (Mohsen) - Controlled head bleeding, cleaned wound with antiseptic, prescribed topical ointment` | **PASS** |
| **TC-05** | Update existing pet record (`Option 8`) | Choose `8`, ID: `102`, Name: `Mohsen`, Species: `Turtle`, Age: `1`, Gender: `Male`, Owner: `Mostafa`, Phone: `01098765432`, Note: `"Deep wound bleeding on head"` | Updates record fields in both `PetList` and `PetBST` while keeping ID `102`. | `Pet ID 102 updated in both Linked List and BST.` | **PASS** |
| **TC-06** | Delete existing pet record (`Option 9`) | Choose `9`, ID: `108` (`Zico`) | Deletes ID `108` from `PetList` and `PetBST` and updates counts. | `Pet ID 108 deleted from records.` | **PASS** |

## Category 2: Empty Structure

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-07** | Undo / Pop when `VisitStack` is empty (`Option 4`) | Choose `4` when `VisitStack` is empty | Displays a message that the stack is empty without error. | `Visit history stack is empty. Nothing to undo/pop.` | **PASS** |
| **TC-08** | Complete visit when `PetQueue` is empty (`Option 3`) | Choose `3` when `waitingQueue` has no pets | Displays a message that no pets are waiting in the queue. | `No pets currently waiting in the queue.` | **PASS** |
| **TC-09** | Display overview with empty structures (`Option 10`) | Choose `10` when a structure (such as `VisitStack`) is empty | Shows size `0` and displays the empty-state message for that structure. | `Visit Stack Size: 0` / `Visit history stack is empty.` | **PASS** |

## Category 3: Boundary and Single Item

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-10** | First record insertion (`Option 1`) | Insert first record ID `100` (`Joy`) into empty `PetList` and `PetBST` | Initializes `head` in `PetList` and `root` in `PetBST` (`size = 1`). | `Pet "Joy" (ID: 100) registered successfully.` | **PASS** |
| **TC-11** | Delete leaf/last and middle nodes (`Option 9`) | Delete ID `108` (last/leaf node) and ID `103` (middle node) | Updates pointers in `PetList` and `PetBST` and removes `103` from queue. | `Pet ID 108 deleted from records.` / `Pet ID 103 deleted from records and removed from waiting queue.` | **PASS** |
| **TC-12** | Maximum capacity check (`MAX = 100`) | Attempt insertion/enqueue/push when `count == 100` | Rejects adding beyond `MAX` (`100`) and displays a full/error message. | `Error: Waiting queue is full.` / `Error: Could not insert into linked list (may be full).` | **PASS** |

## Category 4: Invalid Data

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-13** | Non-numeric and invalid menu input | Enter `"abs"`, then `19` in the main menu | Handles invalid input safely and prompts again without crashing. | `Invalid input. Please enter a valid integer.` / `Invalid menu option. Try again.` | **PASS** |
| **TC-14** | Duplicate Pet ID (`Option 1`) | Choose `1`, enter existing ID `102` | Rejects duplicate ID and shows an error message. | `Error: A pet with ID 102 already exists.` | **PASS** |
| **TC-15** | Invalid ID (`<= 0`) and negative age (`Option 1`) | Enter ID `-1`; then enter ID `109` with Age `-2` | Rejects non-positive ID and negative age with clear error messages. | `Error: ID must be greater than 0.` / `Error: Pet age cannot be negative.` | **PASS** |
| **TC-16** | Non-existent Pet ID (`Options 2, 5, 9`) | Check-in ID `109` (before registration); Search ID `1`; Delete ID `109` (before registration) | Reports that the ID was not found without changing system data. | `Error: Pet ID 109 not found. Register the pet first.` / `No pet found with ID 1.` / `Error: Pet with ID 109 was not found.` | **PASS** |
| **TC-17** | Non-existent Pet Name (`Option 6`) | Choose `6`, enter `"Asya"` | Reports that no pet with that name was found. | `No pet found with name "Asya".` | **PASS** |

## Category 5: Integration

| Test ID | Test Scenario | Input Data / Action | Expected Output | Actual Output | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-18** | Full workflow for Pet ID `102` (`Mohsen`) | Register (`1`) -> Check-in with Priority `2` (`2`) -> Complete Visit (`3`) -> Pop Log (`4`) -> Search ID (`5`) -> Update (`8`) | Record stays synchronized across `PetList`, `PetBST`, `PetQueue`, and `VisitStack`. | All steps executed with matching record details and medical notes. | **PASS** |
| **TC-19** | Delete pet present in waiting queue (`Option 9` + `Option 10`) | Delete ID `103` (`Tom`) while in `PetQueue` (Priority `1`), then view `Option 10` | Removes ID `103` from `PetList`, `PetBST`, and `PetQueue` with matching sizes. | `Pet ID 103 deleted from records and removed from waiting queue.` -> `Linked List Size: 8`, `BST Size: 8`, `Waiting Queue Size: 2`. | **PASS** |

## Category 6: Algorithm and Complexity

| Test ID | Algorithm / Operation | Input Data / Action | Output & Complexity | Time Complexity | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-20** | BST Search (`Option 5`) & Traversals (`Option 10`) | Search ID `102`; display `Inorder` and `Preorder` on IDs `100..107` | Finds ID `102`; `Inorder` prints IDs `100` to `107`; `Preorder` prints `100` to `107`. | Average: $O(\log n)$, Worst (skewed): $O(n)$, Traversal: $O(n)$ | **PASS** |
| **TC-21** | Linear Search by Name (`Option 6`) | Search `"Liza"` (found) and `"Asya"` (not found) | Returns matching record(s) for `"Liza"` or not-found message for `"Asya"`. | Best: $O(1)$, Average/Worst: $O(n)$ | **PASS** |
| **TC-22** | Insertion Sort by Name (`Option 7`) | Choose `7` on registered pets (`Cleo` through `Zico`) | Displays all pets sorted alphabetically (`A` to `Z`) by name. | Best: $O(n)$, Average/Worst: $O(n^2)$ | **PASS** |
| **TC-23** | Priority Queue Enqueue/Dequeue & Stack Push/Pop | Enqueue priorities `2, 1, 0`; dequeue (`Option 3`); push/pop visit log (`Option 4`) | Highest priority dequeues first; stack operates in LIFO order within `MAX = 100`. | Queue: $O(n)$, Stack: $O(1)$ | **PASS** |
