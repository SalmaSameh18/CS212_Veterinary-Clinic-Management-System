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

  -----------------------------------------------------------------------------------------------------------------------------
  Test ID     Feature       Test input /  Expected result                  Actual result                            Status
                            action                                                                                  
  ----------- ------------- ------------- -------------------------------- ---------------------------------------- -----------
  TC-01       Register pet  Register ID   Pet is added to the Linked List  Pet registered successfully!             PASS
                            `1`, Name and BST; success message appears                                          
                            `Joy`,                                                                                  
                            Species `Dog`,
                            Age  `1`,
                            Owner  `Jake`, 
                            Phone  `01000787878`,                                                                          
                            Gender `Male`,                                                                          
                            and valid 
                            remaining                                                                               
                            details                                                                                 

  TC-02       Register      Register ID   Second pet is registered         Pet registered successfully!             PASS
              another pet   `2`, Name     successfully                                                              
                            `Kati`,                                                                                 
                            Species `Cat`, 
                            Age `2`,
                            Owner `Lina`
                            , and                                                                             
                            valid                                                                                   
                            remaining                                                                               
                            details                                                                                 

  TC-03       Register      Register ID   Third pet is registered          Pet registered successfully!             PASS
              third pet     `3`, 
                            Name `Meme`,                                  successfully                                             
                            Species `Dog`
                            , Age `2`,
                            Owner  `Jessy`,
                            and                                                                            
                            valid                                                                                   
                            remaining                                                                               
                            details                                                                                 

  TC-04       Search        Select `2`,   The pet's stored information is  Pet Found!; Joy's ID, name, species,     PASS
              existing pet  enter ID      displayed                        age, and owner were displayed            
                            `1`                                                                                     

  TC-05       Search        Select `2`,   `Pet not found.` is displayed    Not executed yet                         PENDING
              missing pet   enter an ID                                                                             
                            that does not                                                                           
                            exist,                                                                                  
                            e.g. `999`                                                                              

  TC-06       Duplicate ID  Try to        Registration is rejected and     Not executed yet                         PENDING
                            register      duplicate-ID message appears                                              
                            another pet                                                                             
                            using ID                                                                                
                            `1`                                                                                     

  TC-07       Invalid ID    Try           Registration is rejected because Not executed yet                         PENDING
                            registering a the ID must be positive                                                   
                            pet with ID                                                                             
                            `0` or a                                                                                
                            negative ID                                                                             

  TC-08       Invalid age   Try           Registration is rejected with    Not executed yet                         PENDING
                            registering a `Invalid age.`                                                            
                            pet with a                                                                              
                            negative age                                                                            

  TC-09       Empty pet     Try           Registration is rejected with    Not executed yet                         PENDING
              name          registering a `Pet name cannot be empty.`                                               
                            pet with an                                                                             
                            empty name                                                                              

  TC-10       Check in      Select `5`,   Pet is added to the waiting      Pet checked in successfully!             PASS
              existing pet  enter ID      queue                                                                     
                            `3`                                                                                     

  TC-11       Check in same Check in ID   Duplicate queue entry is         Not executed yet                         PENDING
              pet twice     `3` again     rejected                                                                  
                            before                                                                                  
                            completing                                                                              
                            its visit                                                                               

  TC-12       Check in      Select `5`,   `Pet not found.` is displayed    Not executed yet                         PENDING
              missing pet   enter ID      and queue remains unchanged                                               
                            `999`                                                                                   

  TC-13       Complete      Select `6`    Pet is removed from the queue    Visit completed successfully!; Meme (ID  PASS
              visit         while ID      and a visit record is pushed     3) was shown                             
                            `3` is        onto the Stack                                                            
                            waiting                                                                                 

  TC-14       Display visit Select `7`    The latest completed visit is    `ID: 3 | Name: Meme` was displayed       PASS
              history       after         displayed first                                                           
                            completing                                                                              
                            TC-13                                                                                   

  TC-15       Sort pets by  Register Joy  Pets are displayed               Joy (1) appeared before Meme (3)         PASS
              name          and Meme,     alphabetically by name                                                    
                            then select                                                                             
                            `8`                                                                                     

  TC-16       Delete        Select `3`,   Pet is deleted from the Linked   Pet deleted successfully.                  PASS
              existing pet  enter ID      List and BST                                                              
                            `2`                                                                                     

  TC-17       Delete        Select `3`,   `Pet not found.` is displayed    Not executed yet                         PENDING
              missing pet   enter an ID                                                                             
                            that does not                                                                           
                            exist                                                                                   

  TC-18       Display all   Select `4`    Only remaining pet records are   Joy (1) and Meme (3) were displayed;     PASS
              pets          after         displayed                        Kati (2) was absent                      
                            deleting ID                                                                             
                            `2`                                                                                     

  TC-19       Empty waiting Select `6`    `No pets waiting for a visit.`   Not executed yet                         PENDING
              queue         when no pets  is displayed                                                              
                            are waiting                                                                             

  TC-20       Empty visit   Select `7`    `No completed visits yet.` is    Not executed yet                         PENDING
              history       before        displayed                                                                 
                            completing                                                                              
                            any visit                                                                               

  TC-21       Invalid menu  Enter a menu  Invalid-choice message appears   Not executed yet                         PENDING
              choice        number that   and menu is shown again                                                   
                            is not                                                                                  
                            listed,                                                                                 
                            e.g. `9`                                                                                

  TC-22       Non-numeric   Enter text    Invalid-input message appears;   Not executed yet                         PENDING
              menu input    instead of a  program continues                                                         
                            menu number                                                                             

  TC-23       Exit          Select `0`    Program exits safely and         `Thank you for using the system!`        PASS
                                          displays a thank-you message                                              
  -----------------------------------------------------------------------------------------------------------------------------

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
