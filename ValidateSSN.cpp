/**
* Description: Program that checks if a Social Security Number belongs to a man or a woman.
* File: ValidateSSN.cpp
* Version: 1.0
* Author: Sebastiano Bäcklund <sl222sw@student.lnu.se>
*/

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX_SIZE = 20;
const int GENDER_SIZE = 6;

void start();
void getSSN(char (&person)[MAX_SIZE]);
bool validateSSN(const char (&person)[MAX_SIZE]);
bool leapYear(int y);
int daysInMonth(int y, int m);
void hasGender(const char (&person)[MAX_SIZE], char (&gender)[GENDER_SIZE]);
void print(const char (&person)[MAX_SIZE], const char (&gender)[GENDER_SIZE]);

int main() {
    bool running = true;
    char answer = 'Y';

    cout<<"SSN Gender"<<endl;
    cout<<"=========="<<endl<<endl;

    do {
        if (toupper(answer) == 'Y') {
            start();

            cout<<"Want to check another Social Security Number? (Y/N): ";
            cin.get(answer);
            cout<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (toupper(answer) == 'N') {
            // loop will run until 'N' is given as input
            running = false;
        } else {
            // if input is something other than 'Y' or 'N'
            cout<<"Input not accepted. One more time? (Y/N): ";
            cin.get(answer);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (running);

    return 0;
}

void start() {
    char person[MAX_SIZE] = {'\0'};
    char gender[GENDER_SIZE] = {'\0'};

    getSSN(person);
    hasGender(person, gender);
    print(person, gender);
}

void getSSN(char (&person)[MAX_SIZE]) {
    cout<<"Please enter a Social Security Number: ";
    cin.getline(person, MAX_SIZE);

    while (strlen(person) != 10 && strlen(person) != 11 || !validateSSN(person)) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout<<"Invalid date or format, please enter the number in format: YYMMDD-XXXX: ";
        cin.getline(person, MAX_SIZE);
    }
}

bool validateSSN(const char (&person)[MAX_SIZE]) {
    char temp[4] = {'\0'};
    int year = 0, month = 0, day = 0, sum = 0, len = strlen(person);

    for(int i = 0; i<len; i++) {
        if(len == 10 && !isdigit(person[i])) {
            // if the length of SSN is 10 then every character has to be a digit
            return false;
        } else if (len == 11 && i != 6 && !isdigit(person[i])) {
            // if SSN length is 11, check if index 'i' is not a digit, except for index 6
            return false;
        } else if (len == 11 && i == 6 && person[6] != '-') {
            // check if a hyphen can be found on index 6, but only if the length is 11
            return false;
        }
    }

    // assign first two bytes to 'temp'
    memmove(temp, person + 0, 2);
    year = atoi(temp);
    // assign second two bytes to 'temp'
    memmove(temp, person + 2, 2);
    month = atoi(temp);
    // assign third pair of two bytes to 'temp'
    memmove(temp, person + 4, 2);
    day = atoi(temp);
    
    // check if the day exists in given month
    if (!(month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth(year, month))) {
        return false;
    } else {
        return true;
    }
}

bool leapYear(int y) {
    // will only be valid 1901-2099
    if (y % 4 == 0) {
        // if the year is evenly divisible by 4
        return true;
    } else {
        // not a leap year
        return false;
    }
}

int daysInMonth(int y, int m) {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        // if the month has 31 days
        return 31;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        // if the month has 30 days
        return 30;
    } else {
        if (leapYear(y)) {
            // if the month is february and the year is a leap year
            return 29;
        } else {
            // if the month is february and the year isn't a leap year
            return 28;
        }
    }
}

void hasGender(const char (&person)[MAX_SIZE], char (&gender)[GENDER_SIZE]) {
    if (strlen(person) == 10) {
        if ((person[8] - 48) % 2 == 0) {
            // subtract 48 from index 8 in 'person', as 48 is the starting point of digit symbols in ASCII
            // if the number is even, the gender is 'woman'
            memmove(gender, "woman", sizeof("woman"));
        } else {
            // if the number is odd, the gender is 'man'
            memmove(gender, "man", sizeof("man"));
        }
    } else if (strlen(person) == 11) {
        if ((person[9] - 48) % 2 == 0) {
            memmove(gender, "woman", sizeof("woman"));
        } else {
            memmove(gender, "man", sizeof("man"));
        }
    }
}

void print(const char (&person)[MAX_SIZE], const char (&gender)[GENDER_SIZE]) {
    cout<<"The SSN "<<person<<" belongs to a "<<gender<<endl;
}