/*******************************************************************************

 Name:          Robert Price
 Filename:      hw4.cpp
 Environment:   Xcode7.3.1 on iMac
 
 if using terminal ->
 Compile & Run: g++ hw4.cpp -o hw4 && ./hw4
********************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <assert.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
using namespace std;

/*******************************************************************************
                            Menu Functions
********************************************************************************/

// Function : Get Character
int mygetch (void) {
    int ch;
    struct termios oldt, newt;
    
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    
    return ch;
}

// Function : User Keyboard Input
void press_any_key (void) {
    
    char ch;
    cout << "\n Press any key to continue... \n\n";
    ch = mygetch();
    if ( ch == 0 ) mygetch();
    
}


/*******************************************************************************
                            Strategy Functions
********************************************************************************/


// Function : Check if Duel Continues
bool at_least_two_alive (bool A_alive = true, bool B_alive = true, bool C_alive = true) {
    
    if ( (A_alive && B_alive) || (B_alive && C_alive) || (C_alive && A_alive) ) {
        return true;
    } else {
        return false;
    }
}


// Function : Aaron's Turn Strategy 1
void Aaron_shoots (bool& B_alive, bool& C_alive) {
   
    // Chance of Hit
    int shot_result = rand()%100;
    
    // Check Input Arguments
    assert(B_alive || C_alive);
    
    // Strategy
    if (C_alive) {
        cout << "\t Aaron is shooting at Charlie... \n";
        if (shot_result < 33) {
            cout << "\t\t Charlie is killed. \n";
            C_alive = false;
        } else {
            cout << "\t\t Aaron missed. \n";
        }
    } else if (B_alive == true) {
        cout << "\t Aaron is shooting at Bob... \n";
        if (shot_result < 33) {
            cout << "\t\t Bob is killed. \n";
            B_alive = false;
        } else {
            cout << "\t\t Aaron missed. \n";
        }
    } else {
        cout << "\t Error Message: Aaron shoots nobody. \n";
    }
}


// Function : Bob's Turn
void Bob_shoots (bool& A_alive, bool& C_alive) {
    
    // Chance of Hit
    int shot_result = rand()%100;
    
    // Check Input Arguments
    assert(A_alive || C_alive);
    
    // Strategy
    if (C_alive) {
        cout << "\t Bob is shooting at Charlie... \n";
        if (shot_result < 50) {
            cout << "\t\t Charlie is killed. \n";
            C_alive = false;
        } else {
            cout << "\t\t Bob missed. \n";
        }
    } else if (A_alive == true) {
        cout << "\t Bob is shooting at Aaron... \n";
        if (shot_result < 50) {
            cout << "\t\t Aaron is killed. \n";
            A_alive = false;
        } else {
            cout << "\t\t Bob missed. \n";
        }
    } else {
        cout << "\t Error Message: Bob shoots nobody. \n";
    }
}

// Function : Charlie's Turn
void Charlie_shoots (bool& A_alive, bool& B_alive) {
    
    // Check Input Arguments
    assert(A_alive || B_alive);
    
    // Strategy
    if (B_alive) {
        cout << "\t Charlie is shooting at Bob... \n";
            cout << "\t\t Bob is killed. \n";
            B_alive = false;
    } else if (A_alive == true) {
        cout << "\t Charlie is shooting at Aaron... \n";
            cout << "\t\t Aaron is killed. \n";
            A_alive = false;
    } else {
        cout << "\t Error Message: Charlie shoots nobody. \n";
    }
}

// Function : Aaron's Turn Strategy 2
void Aaron_shoots2 (bool& B_alive, bool& C_alive) {

    
    // Check Input Arguments
    assert(B_alive || C_alive);
    
    // Strategy
    if (B_alive == true && C_alive == true) {
        cout << "\t Aaron intentionally misses the first shot. \n";
    } else {
        Aaron_shoots(B_alive, C_alive);
    }
}


/*******************************************************************************
                            Unit Testing Functions
********************************************************************************/


// Unit Testing 1 : Function : at_least_two_alive()
void test_at_least_two_alive (void) {
    cout << "\n\n Unit Testing 1: Function - at_least_two_alive() \n";
    
    // Case 1
    cout << "\t Case 1: Aaron alive, Bob alive, Charlie alive \n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\t\t Case passed...\n";

    // Case 2
    cout << "\t Case 2: Aaron dead, Bob alive, Charlie alive \n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\t\t Case passed...\n";
    
    // Case 3
    cout << "\t Case 3: Aaron alive, Bob dead, Charlie alive \n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\t\t Case passed...\n";
    
    // Case 4
    cout << "\t Case 4: Aaron alive, Bob alive, Charlie dead \n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\t\t Case passed...\n";

    // Case 5
    cout << "\t Case 5: Aaron dead, Bob dead, Charlie alive \n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\t\t Case passed...\n";
    
    // Case 6
    cout << "\t Case 6: Aaron dead, Bob alive, Charlie dead \n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\t\t Case passed...\n";
    
    // Case 7
    cout << "\t Case 7: Aaron alive, Bob dead, Charlie dead \n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\t\t Case passed...\n";
    
    // Case 8
    cout << "\t Case 8: Aaron dead, Bob dead, Charlie dead \n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\t\t Case passed...\n";
}


// Unit Testing 2 : Function : Aaron_shoots()
void test_Aaron_shoots(void) {
    cout << "\n\n Unit Testing 2: Function - Aaron_shoots() \n";
    
    // Initialize Variables
    bool B_alive;
    bool C_alive;
    
    // Case 1
    cout << "\t Case 1: Bob alive, Charlie alive \n";
    B_alive = true;
    C_alive = true;
    Aaron_shoots(B_alive, C_alive);
    
    // Case 2
    cout << "\t Case 2: Bob dead, Charlie alive \n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots(B_alive, C_alive);
    
    // Case 3
    cout << "\t Case 3: Bob alive, Charlie dead \n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots(B_alive, C_alive);
}


// Unit Testing 3 : Function : Bob_shoots()
void test_Bob_shoots(void) {
    cout << "\n\n Unit Testing 3: Function - Bob_shoots() \n";
    
    // Initialize Variables
    bool A_alive;
    bool C_alive;
    
    // Case 1
    cout << "\t Case 1: Bob alive, Charlie alive \n";
    A_alive = true;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    
    // Case 2
    cout << "\t Case 2: Bob dead, Charlie alive \n";
    A_alive = false;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    
    // Case 3
    cout << "\t Case 3: Bob alive, Charlie dead \n";
    A_alive = true;
    C_alive = false;
    Bob_shoots(A_alive, C_alive);
}


// Unit Testing 4 : Function : Charlie_shoots()
void test_Charlie_shoots(void) {
    cout << "\n\n Unit Testing 4: Function - Charlie_shoots() \n";
    
    // Initialize Variables
    bool A_alive;
    bool B_alive;
    
    // Case 1
    cout << "\t Case 1: Bob alive, Charlie alive \n";
    A_alive = true;
    B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    
    // Case 2
    cout << "\t Case 2: Bob dead, Charlie alive \n";
    A_alive = false;
    B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    
    // Case 3
    cout << "\t Case 3: Bob alive, Charlie dead \n";
    A_alive = true;
    B_alive = false;
    Charlie_shoots(A_alive, B_alive);
}

// Unit Testing 5 : Function : Aaron_shoots2()
void test_Aaron_shoots2(void) {
    cout << "\n\n Unit Testing 5: Function - Aaron_shoots2() \n";
    
    // Initialize Variables
    bool B_alive;
    bool C_alive;
    
    // Case 1
    cout << "\t Case 1: Bob alive, Charlie alive \n";
    B_alive = true;
    C_alive = true;
    Aaron_shoots(B_alive, C_alive);
    
    // Case 2
    cout << "\t Case 2: Bob dead, Charlie alive \n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots(B_alive, C_alive);
    
    // Case 3
    cout << "\t Case 3: Bob alive, Charlie dead \n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots(B_alive, C_alive);
}


/*******************************************************************************
                                Main Function
********************************************************************************/


int main() {
    
    cout << "\n *** Welcome to Robert Price's Duel Simulator *** \n";
    
    const int MAX_SIMU_NUM = 10000;
    int i;
    int i2;
    
    // Call Unit Testing Functions
    test_at_least_two_alive();
    press_any_key();
    
    test_Aaron_shoots();
    press_any_key();
    
    test_Bob_shoots();
    press_any_key();
    
    test_Charlie_shoots();
    press_any_key();
    
    test_Aaron_shoots2();
    press_any_key();
    
    // Test Strategy 1
    cout << "\n Ready to test strategy 1 (run 10000 times): \n";
    press_any_key();
    
    float A_wins1 = 0;
    float B_wins1 = 0;
    float C_wins1 = 0;
    
    for (i = 0; i < MAX_SIMU_NUM; i++) {
        bool A_alive = true;
        bool B_alive = true;
        bool C_alive = true;
        
        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive) {
                Aaron_shoots(B_alive, C_alive);
            }
            if (B_alive) {
                Bob_shoots(A_alive, C_alive);
            }
            if (C_alive) {
                Charlie_shoots(A_alive, B_alive);
            }
        }
        if (A_alive) {
            A_wins1++;
        }
        if (B_alive) {
            B_wins1++;
        }
        if (C_alive) {
            C_wins1++;
        }
    }
    
    // Results Strategy 1
    cout << "Aaron won " << A_wins1 << " duels or " << setprecision(4) << (A_wins1 / MAX_SIMU_NUM) * 100 << " % \n";
    cout << "Bob won " << B_wins1 << " duels or " << setprecision(4) << (B_wins1 / MAX_SIMU_NUM) * 100 << " % \n";
    cout << "Charlie won " << C_wins1 << " duels or " << setprecision(4) << (C_wins1 / MAX_SIMU_NUM) * 100 << " % \n";
    
    
    // Test Strategy 2
    cout << "\n Ready to test strategy 2 (run 10000 times): \n";
    press_any_key();
    
    float A_wins2 = 0;
    float B_wins2 = 0;
    float C_wins2 = 0;
    
    for (i2 = 0; i2 < MAX_SIMU_NUM; i2++) {
        bool A_alive = true;
        bool B_alive = true;
        bool C_alive = true;
        
        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive) {
                Aaron_shoots2(B_alive, C_alive);
            }
            if (B_alive) {
                Bob_shoots(A_alive, C_alive);
            }
            if (C_alive) {
                Charlie_shoots(A_alive, B_alive);
            }
        }
        if (A_alive) {
            A_wins2++;
        }
        if (B_alive) {
            B_wins2++;
        }
        if (C_alive) {
            C_wins2++;
        }
    }
    
    // Results Strategy 2
    cout << "Aaron won " << A_wins2 << " duels or " << setprecision(4) << (A_wins2 / MAX_SIMU_NUM) * 100 << " % \n";
    cout << "Bob won " << B_wins2 << " duels or " << setprecision(4) << (B_wins2 / MAX_SIMU_NUM) * 100 << " % \n";
    cout << "Charlie won " << C_wins2 << " duels or " << setprecision(4) << (C_wins2 / MAX_SIMU_NUM) * 100 << " % \n";
    
    if (A_wins2 > A_wins1) {
        cout << "\nStrategy 2 is better than strategy 1. \n";
    } else if (A_wins1 > A_wins2) {
        cout << "\nStrategy 1 is better than strategy 2. \n";
    } else {
        cout << "Error \n";
    }
    return 0;
}

