#include "yut.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

////////////////// This function is not modifiable!//////////////////////
int Yut::throwOneYut() {
    int res = rand() % 100;
    if (res < prob * 100) {
        return 1; // front
    } else {
        return 0; // back
    }
}
/////////////////////////////////////////////////////////////////////////
/*
- Using the throwOneYut function to get a yut result
- Yut result should be obtained based on the results from the front and back
result of each yut stick.
- One of the yut sticks is marked, so we need to consider the back-do.
- Output
    - yut result (back-do, do, gae, geol, yut, and mo)
*/
string Yut::throwFourYuts() {

    //////////////////IMPLEMENT HERE//////////////////////////////////////
    int sum = 0;
    bool isMarkedYutFlipped = false;

    for (int i = 0; i < 4; ++i) {
        int result = throwOneYut();
        sum += result;

        // 첫 번째 윷(마킹된 윷)이 뒤집어졌는지 확인
        if (i == 0 && result == 0) {
            isMarkedYutFlipped = true;
        }
    }
    if (isMarkedYutFlipped && sum == 1) {
        return "back-do";
    }
    switch (sum) {
        case 0:
            return "mo";
        case 1:
            return "do";
        case 2:
            return "gae";
        case 3:
            return "geol";
        case 4:
            return "yut";
    }
    //////////////////////////////////////////////////////////////////////
}
