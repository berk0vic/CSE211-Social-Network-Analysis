// Person.cpp
#include "Person.h"
#include <utility>
#ifndef PERSON_CPP
#define PERSON_CPP
using namespace std;
Person::Person(int id, string name, int age, string gender, string occupation, vector<int> friends)
        : id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

int Person::Person_Id() const {
    return id;
}

int Person::Person_age() const {
    return age;
}

string Person::person_Name() const {
    return name;
}

string Person::person_Occupation() const {
    return occupation;
}
string Person::person_Gender() const {
    return gender;
}

vector<int> Person::person_Friends() const {
    return friends;
}

void Person::set_person_Friends(std::vector<int> friends) {
    this->friends = std::move(friends);
}
void Person::remove_Friendship(int id) {
    for(int i = 0; i < friends.size(); i++) {
        if (friends[i] == id) {
            friends.erase(friends.begin() + i);
            break;
        }
    }
}
#endif // !PERSON_CPP