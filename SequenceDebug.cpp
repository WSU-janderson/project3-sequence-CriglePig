/**
 * SequenceDebug.cpp
 * Project 3
 * CS 3100
 *
 * In this file, you will write your tests as you implement Sequence. If you are using CLion, you need to select
 * SequenceDebug from the drop-down menu next to the Build (hammer icon) if it is on SequenceTestHarness
 */
#include <iostream>
#include <string>
#include "Sequence.h"

using namespace std;

int main() {
    cout << "Your project is ready to go!" << endl;

    Sequence s1(2);
    s1[0] = "Hello";
    s1[1] = "world!";
    cout << s1 << endl;

    s1.insert(1, "there");
    cout << s1 << endl;

    s1.pop_back();
    cout << s1 << endl;

    s1.push_back("partner!");
    cout << s1 << endl;

    s1.erase(1);
    cout << s1 << endl;

    s1.insert(1, "there");
    cout << s1 << endl;

    s1.erase(1, 2);
    cout << s1 << endl;

    Sequence s2(2);
    s2[0] = "Hello";
    s2[1] = "world!";
    cout << s2 << endl;

    s1 = s2;
    cout << s1 << endl;

    return 0;
}