/**
 * Programmer: Argin Aslanian
 * Purpose: This program is a login/logout system for users to use computers in computer labs.
 *
 * MEMBER FUNCTIONS
 *    void showStatus() -> This function displays the status of all computers in all computer labs.
 *    void showMenu()   -> This function displays the menu to the user.
 *    void login()      -> This function logs the user into the computer that the user chose.
 *    void logout()     -> This function logs the user out.
 *    void search()     -> This function searches all the computers in the computer labs to find the
 *                         the one user that was searched for.
 */

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

//Declare function that will be used to verify the user's input.
int getUserValidatedInput(int x, int y);

class LoginSystem {
    // 2D array holding Lab#s and corresponding Computer#s.
    string** labs;

public:

    LoginSystem() {
        //Dynamic allocation
        labs = new string*[4];
        for(int row = 0; row < 4; row++) {
            labs[row] = new string[10];
        }

        //Initializing the table and make all computers "empty".
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 10; col++) {
                labs[row][col] = "empty";
            }
        }

    }

    ~LoginSystem() {
        for(int row = 0; row < 4; row++) {
            delete [] labs[row];
        }
        delete labs;
    }

    void showStatus(){
        cout << "STATUS" << endl;
        cout << "LAB#" << setw(15) << "Computers" << endl;

        //First Row.
        cout << "1" << setw(10);
        for (int i = 0; i < 10; i++) {
            cout << i+1 << ": " << labs[0][i] << " ";
        }
        cout << endl;

        //Second Row.
        cout << "2" << setw(10);
        for (int i = 0; i < 10; i++) {
            cout << i+1 << ": " << labs[1][i] << " ";
        }
        cout << endl;

        //Third Row.
        cout << "3" << setw(10);
        for (int i = 0; i < 10; i++) {
            cout << i+1 << ": " << labs[2][i] << " ";
        }
        cout << endl;

        //Fourth Row.
        cout << "4" << setw(10);
        for (int i = 0; i < 10; i++) {
            cout << i+1 << ": " << labs[3][i] << " ";
        }
        cout << endl << endl;
    }

    //Display the menu to the user.
    void showMenu() {
        cout << "SELECTION MENU" << endl;
        cout << "1. LOGIN" << endl;
        cout << "2. LOGOUT" << endl;
        cout << "3. SEARCH" << endl;
        cout << "4. QUIT" << endl;
    }

    void login() {
        string userID;

        //Get user's ID.
        do {
            cout << "Enter you 5-character ID to login: " << endl;
            cin >> userID;
        } while (userID.length() != 5 || userID == "empty");

        //Get Lab#
        //Between 1 and 4.
        int labNum;
        cout << "Enter the Lab # (1-4): " << endl;
        labNum = getUserValidatedInput(1,4);

        //Get Computer#
        //Between 1 and 10.
        int computerNum;
        cout << "Enter the Computer # (1-10): " << endl;
        computerNum = getUserValidatedInput(1,10);

        //Check if that computer is already in use.
        //Check if that user is already logged in somewhere else.
        bool loggedInSomewhereElse = false;
        if (labs[labNum-1][computerNum-1] != "empty") {
            cout << "ERROR, " << labs[labNum-1][computerNum-1] << " is already logged into that station." << endl;
        } else {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 10; j++) {
                    if (labs[i][j] == userID) {
                        loggedInSomewhereElse = true;
                        cout << "ERROR: " << userID << " is already logged in. " << userID << " is in Lab# " << i+1 << " at Computer# " << j+1 << "."<< endl;
                        break;
                    }
                }
                if (loggedInSomewhereElse) break;
            }

            //If the user is not logged in somewhere else,
            //AND that computer is not already in use,
            //Log the user in.
            if (!loggedInSomewhereElse) {
                labs[labNum-1][computerNum-1] = userID;
            }

        }

    }

    void logout() {
        //Get the logoutID.
        string logoutID;
        do {
            cout << "Enter your 5-character ID to logout: " << endl;
            cin >> logoutID;
        } while (logoutID.length() != 5 || logoutID == "empty");

        //Go through the computers and see if you can find that ID.
        bool logoutIDFound = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                //If it was found, make that computer "empty", break out of both loops.
                if (labs[i][j] == logoutID) {
                    logoutIDFound = true;
                    labs[i][j] = "empty";
                    cout << "User " << logoutID << " is logged out." << endl;
                    break;
                }
            }
            if (logoutIDFound) break;
        }

        //If that user was NOT found, display the appropriate message.
        if (!logoutIDFound) {
            cout << "That user is NOT logged in." << endl;
        }

    }

    void search() {
        //Get searchID.
        string searchID;
        do {
            cout << "Enter s 5-character ID to search: " << endl;
            cin >> searchID;
        } while (searchID.length() != 5 || searchID == "empty");

        //Go through the computers and see if you can find that user logged in somewhere.
        bool searchIDFound = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                //If the user was found, break out of both loops, display where that user is logged in at.
                if (labs[i][j] == searchID) {
                    cout << "User " << searchID << " is in Lab# " << i+1 << " at Computer# " << j+1 << "." << endl;
                    searchIDFound = true;
                    break;
                }
            }
            if (searchIDFound) break;
        }

        //If that user ID was NOT found, display the appropriate message.
        if (!searchIDFound) {
            cout << "That user is not logged in. " << endl;
        }

    }

};

//Validate user inputs.
//NOTE: RECURSIVE FUNCTION!
int getUserValidatedInput(int x, int y) {
    int retVal = 0;

    //Input has to be int.
    while(!(cin >> retVal)) {
        cout << "Error: Invalid Input. Please try again... ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //Input HAS TO BE between x and y.
    if (retVal < x || retVal > y) {
        cout << "Error: Enter numbers between " << x << " - " << y << endl;
        retVal = getUserValidatedInput(x,y);
    }

    return retVal;
}

int main() {

    LoginSystem login;
    int input = 0;

    do {
        login.showStatus();
        login.showMenu();

        //Get user's input.
        //Between 1 and 4
        input = getUserValidatedInput(1,4);

        //Calls the appropriate function when the program receives an input.
        switch (input) {
            case 1:
                login.login();
                break;
            case 2:
                login.logout();
                break;
            case 3:
                login.search();
                break;
            default:
                break;
        }

    } while (input != 4);

    //When 4 is pressed, the program will QUIT!

    return 0;
}