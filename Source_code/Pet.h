#ifndef PET_H
#define PET_H

#include <string>

using namespace std;

struct Pet
{
    int id;
    string name;
    string species;
    int age;
    string gender;
    string owner;
    string phone;
    string medicalNote;

    Pet() : id(0), name(""), species(""), age(0),
            gender(""), owner(""), phone(""), medicalNote("") {}
};

#endif // PET_H
