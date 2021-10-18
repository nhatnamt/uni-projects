#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define VOTER_FILENAME          "voterTable.csv"
#define CANDIDATE_FILENAME      "candidateTable.csv"

void pause(string prompt) {
    // displays a prompt and waits for the user to press enter before proceeding
    cout << endl << prompt;
    cin.ignore();
    cin.get();
}

bool file_isValid(fstream &file) {
    // check if file can be open
    if (file.fail()) {
        pause("Voter table failed to open, please find the nearest staff for support.\nPress enter to exit ");
        return 0;
    }
    // check if csv file (database) is empty
    if (file.get(), file.eof()) {
        pause("The database is empty, press enter to return to main menu ");
        return 0;
    }
    // default return to 1, or file is okay
    return 1;
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

void add_votes(fstream &file) {
    //pause("add_votes() placeholder, press enter to return to main menu\n");
    bool record_found = false;
    string voterID;
    string record[12];

    // clear file error
    //file.clear();
    //file.seekg(ios::beg);
    // check if file can be open/empty
    if (!file_isValid(file)) {
        return void();
    }
    
    cout << "Please enter your student ID: ";
    cin >> voterID;

    while (getline(file, record[0], ',') && record_found == false  ) {
        if (record[0] == voterID) {
            record_found = true;
            bool vote_confirmed = false;
            for (int i = 1; i <= 10; i++) {
                    getline(file, record[i], ',');
            }
            cout << '\t' << "Name: " << record[2] + " " + record[3] << endl 
                 << '\t' << "Student ID: " << record[0] << endl
                 << '\t' << "Surburb: " << record[5] << endl;
            while (!vote_confirmed) {
                string selection;
                cout << "Please enter the candidate's ID you would like to vote for: ";
                cin >> selection;
                if (selection == "Y" || selection == "y") {
                    vote_confirmed = true;
                    cout << "Placeholder";
                } 
                else if (selection == "X" || selection == "x") {
                    break;
                }
            }
        }   
        else {
            file.ignore(500,'\n');
        }
    }

//                 // until eof is reached, read column values temporarily into an array and print relevant info to screen in a table-like format
//                 for (int i = 0; i <= 10; i++) {
//                     getline(file, record[i], ',');
//                 }
//                 getline(file, record[11], '\n');

//                 cout << '\t' << left << setw(15) << record[0] << setw(15) << record[2] << setw(15) << record[3] << setw(15) << record[4] << setw(15) << record[10] << setw(15) << record[11] << endl;
//             }
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

    //ifstream candidateFile (CANDIDATE_FILE); //open as output fui
    fstream voterFile (VOTER_FILENAME, ios::in | ios::out);

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
            add_votes(voterFile);
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
