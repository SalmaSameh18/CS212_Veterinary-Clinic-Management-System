# Veterinary Clinic Management System -- Test Cases

**Project:** Veterinary Clinic Management System\
**Language:** C++\
**Test file purpose:** Record normal and edge-case tests for the
project.

## 1. Test Environment

-   Compiler: g++
-   Standard: C++11
-   Source: complete project code provided by the team
-   Build command:

``` bash
g++ main.cpp -std=c++11 -o clinic
```

-   Run:
    -   Windows: `clinic.exe`
    -   Linux/macOS: `./clinic`

The submitted source was successfully compiled with `g++ -std=c++11`.

## 2. Test Cases

| Test ID | Feature | Test input / action | Expected result | Actual result | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| TC-01 | Register pet | Register ID `1`, Name `Joy`, Species `Dog`, Age `1`, Owner `Jake`, Phone `01000787878`, Gender `Male`, and valid remaining details | Pet is added to the Linked List and BST; success message appears | Pet registered successfully! | PASS |
| TC-02 | Register another pet | Register ID `2`, Name `Kati`, Species `Cat`, Age `2`, Owner `Lina`, and valid remaining details | Second pet is registered successfully | Pet registered successfully! | PASS |
| TC-03 | Register third pet | Register ID `3`, Name `Meme`, Species `Dog`, Age `2`, Owner `Jessy`, and valid remaining details | Third pet is registered successfully | Pet registered successfully! | PASS |
| TC-04 | Search existing pet | Select `2`, enter ID `1` | The pet's stored information is displayed | Pet Found!; Joy's ID, name, species, age, and owner were displayed | PASS |
| TC-05 | Search missing pet | Select `2`, enter an ID that does not exist, e.g. `999` | `Pet not found.` is displayed | Not executed yet | PENDING |
| TC-06 | Duplicate ID | Try to register another pet using ID `1` | Registration is rejected and duplicate-ID message appears | Not executed yet | PENDING |
| TC-07 | Invalid ID | Try registering a pet with ID `0` or a negative ID | Registration is rejected because the ID must be positive | Not executed yet | PENDING |
| TC-08 | Invalid age | Try registering a pet with a negative age | Registration is rejected with `Invalid age.` | Not executed yet | PENDING |
| TC-09 | Empty pet name | Try registering a pet with an empty name | Registration is rejected with `Pet name cannot be empty.` | Not executed yet | PENDING |
| TC-10 | Check in existing pet | Select `5`, enter ID `3` | Pet is added to the waiting queue | Pet checked in successfully! | PASS |
| TC-11 | Check in same pet twice | Check in ID `3` again before completing its visit | Duplicate queue entry is rejected | Not executed yet | PENDING |
| TC-12 | Check in missing pet | Select `5`, enter ID `999` | `Pet not found.` is displayed and queue remains unchanged | Not executed yet | PENDING |
| TC-13 | Complete visit | Select `6` while ID `3` is waiting | Pet is removed from the queue and a visit record is pushed onto the Stack | Visit completed successfully!; Meme (ID 3) was shown | PASS |
| TC-14 | Display visit history | Select `7` after completing TC-13 | The latest completed visit is displayed first | `ID: 3 | Name: Meme` was displayed | PASS |
| TC-15 | Sort pets by name | Register Joy and Meme, then select `8` | Pets are displayed alphabetically by name | Joy (1) appeared before Meme (3) | PASS |
| TC-16 | Delete existing pet | Select `3`, enter ID `2` | Pet is deleted from the Linked List and BST | Pet deleted successfully. | PASS |
| TC-17 | Delete missing pet | Select `3`, enter an ID that does not exist | `Pet not found.` is displayed | Not executed yet | PENDING |
| TC-18 | Display all pets | Select `4` after deleting ID `2` | Only remaining pet records are displayed | Joy (1) and Meme (3) were displayed; Kati (2) was absent | PASS |
| TC-19 | Empty waiting queue | Select `6` when no pets are waiting | `No pets waiting for a visit.` is displayed | Not executed yet | PENDING |
| TC-20 | Empty visit history | Select `7` before completing any visit | `No completed visits yet.` is displayed | Not executed yet | PENDING |
| TC-21 | Invalid menu choice | Enter a menu number that is not listed, e.g. `9` | Invalid-choice message appears and menu is shown again | Not executed yet | PENDING |
| TC-22 | Non-numeric menu input | Enter text instead of a menu number | Invalid-input message appears; program continues | Not executed yet | PENDING |
| TC-23 | Exit | Select `0` | Program exits safely and displays a thank-you message | `Thank you for using the system!` | PASS |

## 3. Executed End-to-End Test

The following workflow was executed successfully:

1.  Registered Joy with ID `1`.
2.  Registered Kati with ID `2`.
3.  Registered Meme with ID `3`.
4.  Searched for Joy using ID `1`.
5.  Checked Meme into the waiting queue using ID `3`.
6.  Completed Meme's visit.
7.  Displayed the visit history and confirmed Meme appeared.
8.  Deleted Kati using ID `2`.
9.  Displayed all pets and confirmed Joy and Meme remained while Kati was absent.
10. Sorted the registered pets by name and confirmed Joy appeared before Meme.
11. Exited the program safely.

**Result:** All steps in this executed workflow produced the expected
output.

## 4. Notes and Limitations Observed in the Current Code

-   The waiting queue supports priorities, but `checkInPet()` calls
    `enqueue(id)` without passing a priority. Therefore, pets checked in
    through the menu receive the default priority `0`; different
    priority levels are not currently demonstrated through the
    application menu.
-   The delete option removes a pet from the Linked List and BST, but it
    does not remove that pet from the waiting queue or visit history.
    Deleting a pet that is already waiting may therefore leave an
    outdated queue entry.
-   The current menu does not provide an update-pet option.
-   The test cases marked **PENDING** must be run manually before the
    final submission. Fill in their Actual result and change the Status
    after checking the output.

## 5. Conclusion

The executed end-to-end workflow confirms that the main registration,
search, check-in, visit completion, visit history, deletion, display,
sorting, and exit operations work for the tested data. Additional
pending edge-case tests should be completed and recorded before
submission.
