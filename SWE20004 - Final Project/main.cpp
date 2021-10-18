#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void pause(string prompt) {
    // displays a prompt and waits for the user to press enter before proceeding
    string temp;
    cout << endl << prompt;
    cin.ignore();
    temp = cin.get();
}

void print_candidate_information() {
    ifstream file;
    file.open("candidateTable.csv");

    if (file.fail()) {
        pause("Candidate table failed to open, press enter to return to main menu\n");
        return void();
    }
    else {
        string record[12];
        
        if (file.get(), file.eof()) {
            // check if csv file (database) is empty
            pause("The database is empty, press enter to return to main menu\n");
            return void();
        }
        else {
            // if database is not empty
            cout << "\nRunning Candidates\n";
            while (!file.eof()) {
                // until eof is reached, read column values temporarily into an array and print relevant info to screen in a table-like format
                for (int i = 0; i <= 10; i++) {
                    getline(file, record[i], ',');
                }
                getline(file, record[11], '\n');

                cout << '\t' << left << setw(15) << record[1] << setw(15) << record[2] << setw(15) << record[3] << setw(15) << record[4] << setw(15) << record[10] << setw(15) << record[11] << endl;
            }
        }
    }
    file.close();
    pause("Press enter to return to main menu\n");
}

void add_votes() {
    pause("add_votes() placeholder, press enter to return to main menu\n");
}

void display_losing_candidate() {
    pause("display_losing_candidate() function complete, press enter to return to main menu\n");
}

void display_winning_candidate() {
    pause("display_winning_candidate() placeholder, press enter to return to main menu\n");
}

void menu() {
    bool exit = false;
    string selection;

    while (exit == false) {
        cout << "Select an option to get started\n";
        cout << "\t(P) Print candidate information\n";
        cout << "\t(A) Add votes to a candidate\n";
        cout << "\t(S) Display candidate with smaller number of votes\n";
        cout << "\t(L) Display candidate with largest number of votes\n";
        cout << "\t(Q) Quit\n";
        cin >> selection;

        if (selection == "p" || selection == "P") {
            print_candidate_information();
        }
        else if (selection == "a" || selection == "A") {
            add_votes();
        }
        else if (selection == "s" || selection == "S") {
            display_losing_candidate();
        }
        else if (selection == "l" || selection == "L") {
            display_winning_candidate();
        }
        else if (selection == "q" || selection == "Q") {
            cout << "Exiting program\n";
            exit = true;
        }
        else {
            pause("Invalid selection, press enter to return to main menu\n");
        }
    }
}

int main()
{
    menu(); // main menu for the program
}
