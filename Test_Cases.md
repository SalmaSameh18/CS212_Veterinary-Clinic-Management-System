# Veterinary Clinic Management System -- Test Cases

**Project:** Veterinary Clinic Management System

**Language:** C++

**Test file purpose:** Record normal and edge-case tests for the project.

## 1. Test Environment

* Compiler: g++

* Standard: C++11

* Source: complete project code provided by the team

* Build command:

```bash
g++ main.cpp -std=c++11 -o clinic
```

* Run:

  * Windows: `clinic.exe`

  * Linux/macOS: `./clinic`

The submitted source was successfully compiled with `g++ -std=c++11 Source_code/Main/Pet_main.cpp -o clinic`.

## 2. Test Cases

| Test ID | Feature | Test input / action | Expected result | Actual result | Status | 
| ----- | ----- | ----- | ----- | ----- | ----- | 
| TC-01 | Register first pet | Register ID `100`, Name `Joy`, Species `Dog`, Age `1`, Owner `Karma`, Phone `01020078341`, Gender `Male`, Medical Note `Requires regular checkups` | Pet is added to the Linked List and BST; success message appears | `Pet registered successfully!` | PASS | 
| TC-02 | Register second pet | Register ID `101`, Name `Kati`, Species `Cat`, Age `2`, Owner `Lina`, Phone `01095643764`, Gender `Female`, Medical Note `Recovering from a minor infection` | Second pet is registered successfully | `Pet registered successfully!` | PASS | 
| TC-03 | Register additional pets | Register ID `102` (`Meme`), ID `103` (`Lolo`), ID `104` (`Mohsen`), and ID `105` (`Losi`) with valid details | All remaining pets are registered successfully | `Pet registered successfully!` appeared for all four pets | PASS | 
| TC-04 | Search existing pet | Select `2`, enter ID `102` | The pet's stored information is displayed | `Pet Found!` displayed with `ID: 102`, `Name: Meme`, `Species: Dog`, `Age: 2`, `Owner: Jessy` | PASS | 
| TC-05 | Search missing pet | Select `2`, enter an ID that does not exist (`109`) | `Pet not found.` is displayed | `Pet not found.` | PASS | 
| TC-06 | Duplicate ID | Try to register another pet using existing ID `101` | Registration is rejected and duplicate-ID message appears | `Pet ID already exists.` | PASS | 
| TC-07 | Invalid ID | Try registering a pet with negative ID `-2` | Registration is rejected because the ID must be positive | `Invalid ID. ID must be positive.` | PASS | 
| TC-08 | Invalid age | Try registering ID `106` (`Dodi`) with negative age `-2` | Registration is rejected with `Invalid age.` | `Invalid age.` | PASS | 
| TC-09 | Empty pet name | Try registering ID `107` with an empty pet name | Registration is rejected with `Pet name cannot be empty.` | `Pet name cannot be empty.` | PASS | 
| TC-10 | Check in existing pet | Select `5`, enter ID `101` | Pet is added to the waiting queue | `Pet checked in successfully!` | PASS | 
| TC-11 | Check in same pet twice | Check in ID `101` again before completing its visit | Duplicate queue entry is rejected | `Pet is already in the waiting queue.` | PASS | 
| TC-12 | Check in missing pet | Select `5`, enter missing ID `109` | `Pet not found.` is displayed and queue remains unchanged | `Pet not found.` | PASS | 
| TC-13 | Complete visit | Select `6` while ID `101` (`Kati`) is waiting | Pet is removed from the queue and a visit record is pushed onto the Stack | `Visit completed successfully!`, `Pet Name: Kati`, `Pet ID: 101` | PASS | 
| TC-14 | Display visit history | Select `7` after completing TC-13 | The latest completed visit is displayed first | `Recent visits (newest first):` with `- ID: 101 \| Name: Kati` | PASS | 
| TC-15 | Sort pets by name | After deleting ID `105`, select `8` | Pets are displayed alphabetically by name | `Pets Sorted By Name:` displayed `Joy (100)`, `Kati (101)`, `Lolo (103)`, `Meme (102)`, `Mohsen (104)` | PASS | 
| TC-16 | Delete existing pet | Select `3`, enter ID `105` (`Losi`) | Pet is deleted from the Linked List and BST | `Pet deleted successfully.` | PASS | 
| TC-17 | Delete missing pet | Select `3`, enter missing ID `109` | `Pet not found.` is displayed | `Pet not found.` | PASS | 
| TC-18 | Display all pets | Select `4` after deleting ID `105` | Only remaining pet records are displayed | Displayed IDs `100`, `101`, `102`, `103`, and `104`; ID `105` (`Losi`) was absent | PASS | 
| TC-19 | Empty waiting queue | Select `6` when no pets are waiting | `No pets waiting for a visit.` is displayed | `No pets waiting for a visit.` | PASS | 
| TC-20 | Empty visit history | Select `7` before completing any visit | `No completed visits yet.` is displayed | `No completed visits yet.` | PASS | 
| TC-21 | Invalid menu choice | Enter an unlisted menu number (`16`) | Invalid-choice message appears and menu is shown again | `Invalid choice. Please try again.` | PASS | 
| TC-22 | Non-numeric menu input | Enter text (`Hello`) instead of a menu number | Invalid-input message appears; program continues | `Invalid input. Please enter a number.` | PASS | 
| TC-23 | Exit | Select `0` | Program exits safely and displays a thank-you message | `Thank you for using the system!` | PASS | 

## 3. Executed End-to-End Test

The following workflow was executed successfully:

1. Verified empty visit history (`No completed visits yet.`) and empty waiting queue (`No pets waiting for a visit.`) before adding records.

2. Registered `Joy` (ID `100`), `Kati` (ID `101`), `Meme` (ID `102`), `Lolo` (ID `103`), `Mohsen` (ID `104`), and `Losi` (ID `105`).

3. Tested registration validation errors: duplicate ID (`101`), negative ID (`-2`), negative age (`-2` for `Dodi`), and empty pet name (ID `107`).

4. Searched for `Meme` using ID `102` (found) and ID `109` (not found).

5. Checked `Kati` (ID `101`) into the waiting queue, confirmed duplicate check-in rejection for ID `101`, and verified rejection for missing ID `109`.

6. Completed `Kati`'s visit (ID `101`) and verified `No pets waiting for a visit.` when the queue became empty again.

7. Displayed recent visit history and confirmed `- ID: 101 | Name: Kati` appeared.

8. Deleted `Losi` (ID `105`) and verified rejection when deleting missing ID `109`.

9. Displayed all remaining pets (`100` through `104`) and sorted them alphabetically by name (`Joy`, `Kati`, `Lolo`, `Meme`, `Mohsen`).

10. Tested invalid menu inputs (`16` and `Hello`) and exited the program safely (`0`).

**Result:** All 23 test cases executed and produced the expected output.

## 4. Notes and Limitations Observed in the Current Code

* The waiting queue supports priorities, but `checkInPet()` calls `enqueue(id)` without passing a priority. Therefore, pets checked in through the menu receive the default priority `0`; different priority levels are not currently demonstrated through the application menu.

* The delete option removes a pet from the Linked List and BST, but it does not remove that pet from the waiting queue or visit history. Deleting a pet that is already waiting may therefore leave an outdated queue entry.

* The current menu does not provide an update-pet option.

## 5. Conclusion

All 23 normal and edge-case tests passed. The executed workflow confirms that registration, input validation, search, check-in, duplicate check-in prevention, visit completion, visit history, deletion, display, sorting, menu validation, and exit operations work as expected.
