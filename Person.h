#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
using namespace std;
class Person {
public:
    Person(int id, string name, int age, string gender, string occupation, vector<int> friends);
    int Person_Id() const;
    int Person_age() const;
    string person_Name() const;
    string person_Gender() const;
    string person_Occupation() const;

    vector<int> person_Friends() const;
    void remove_Friendship(int id);
    void set_person_Friends(vector<int> friends);



private:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string occupation;
    std::vector<int> friends;
};

#endif