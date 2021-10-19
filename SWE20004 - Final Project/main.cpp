#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define VOTER_FILENAME          "voterTable.csv"
#define VOTER_NEW_FILENAME      "voterNewTable.csv"
#define CANDIDATE_FILENAME      "candidateTable.csv"
#define CANDIDATE_NEW_FILENAME  "candidateNewTable.csv"

//options for displaying candidate information
enum {
    ALL,
    LOW,
    HIGH
};

void pause(string prompt) {
    // displays a prompt and waits for the user to press enter before proceeding
    cout << endl << prompt;
    cin.ignore();
    cin.get();
}

bool file_isValid(ifstream &file) {
    // check if file can be open
    if (file.fail()) {
        pause("Voter table failed to open, please ask for assistance.\nPress enter to return to main menu ");
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

// convert from string to number
int str2int(string str) {
    if (str == "") return 0;
    for (char c : str) {
        if (!isdigit(c)) {return 0;}
    }

    return stoi(str);
}

// update candidate with specified ID
string update_candidate(string candidateID) {
    string record[12];
    bool recordFound = false;
    ifstream fin (CANDIDATE_FILENAME);
    ofstream fout (CANDIDATE_NEW_FILENAME);

    //check if file can be open/empty
    if (!file_isValid(fin)) {
        return "";
    }

    // get the first field on the row of the database until eof
    while (getline(fin, record[0], ',')) {
        
        // get the rest of that row
        for (int i = 1; i < 11; i++) {
            getline(fin, record[i], ',');
        }
        getline(fin, record[11], '\n');

        // if match the voted candidate ID
        if (record[0] == candidateID) {
            // convert vote count to interger and flag found
            int voteCount = str2int(record[11]);
            recordFound = true;

            // increase vote by 1 and print confirmation
            record[11] = to_string(voteCount+1);
            cout << "\nVote updated. Candidate " << record[0] << " - " << record[3] + ' ' + record[4] << " now has " << record[11] << " votes.\n";
        }

        // write to new Candidate table
        for (int i=0; i<11; i++) {
            fout << record[i] << ',';
        }
        fout << record[11] << '\n';
    }

    //close file
    fin.close();
    fout.close();

    // remove the old database
    remove(CANDIDATE_FILENAME);

	// renaming to the new database
	rename(CANDIDATE_NEW_FILENAME, CANDIDATE_FILENAME);

    // prompt no match ID
    if (!recordFound) {
        pause("No matching candidate ID found. Press enter to return to menu and (P) to see the list of candidates.");
        return "";
    } 

    //return the symbol of the candidate
    return record[10];
}

void display_candidate_information(int option) {
    ifstream file (CANDIDATE_FILENAME);

     //check if file can be open/empty
    if (!file_isValid(file)) {
        return void();
    }

    string record[12];
    int voteMinMax = 0;

    // set min max base on option chose
    if (option == LOW) voteMinMax == 10000;
    
    // search for candidates with highest/lowest votes
    if (option != ALL) {
        file.ignore(10000,'\n');
        while (getline(file, record[0], ',')) {
        
            for (int i=1; i<11; i++) {
                getline(file, record[i], ',');
            }
            getline(file, record[11], '\n');

            int votes = str2int(record[11]);

            // find the min/max vote
            if (option == LOW) {
                if (votes <= voteMinMax) voteMinMax = votes;
            }
            else {
                if (votes >= voteMinMax) voteMinMax = votes;
            }
        }
    }
    
    // add an output line if is printing all candidates
    else {
        cout << "\nRunning Candidates\n";
    }

    // display all or just candidates with highest/lowest votes
    //clear and move cursor to the top
    file.clear();
    file.seekg(ios::beg);
    file.ignore(10000, '\n'); // skip the first line


    cout << '\t' << left << setw(15) << "Candidate ID" << setw(15) << "Course" << setw(15) << "First name" << setw(15) << "Last name" << setw(15) << "Symbol" << setw(15) << "Vote count" << endl;
    while (getline(file, record[0], ',')) {
        // until eof is reached, read column values temporarily into an array and print relevant info to screen in a table-like format
        for (int i = 1; i <= 10; i++) {
            getline(file, record[i], ',');
        }
        getline(file, record[11], '\n');
        
        // print all record with
        if (option == ALL || str2int(record[11]) == voteMinMax) {
            cout << '\t' << left << setw(15) << record[0] << setw(15) << record[2] << setw(15) << record[3] << setw(15) << record[4] << setw(15) << record[10] << setw(15) << record[11] << endl;
        }

    }

    file.close();
    pause("Press enter to return to main menu ");
}

void add_votes() {
    //pause("add_votes() placeholder, press enter to return to main menu\n");
    bool record_found = false;
    string voterID, record[11];

    ifstream fin (VOTER_FILENAME);
    ofstream fout (VOTER_NEW_FILENAME);

    //check if file can be open/empty
    if (!file_isValid(fin)) {
        return void();
    }
    
    cout << "Please enter your student ID: ";
    cin >> voterID;

    while (getline(fin, record[0], ',')) {
        // copy row data to an array
        for (int i = 1; i < 10; i++) {
            getline(fin, record[i], ',');
        }
        getline(fin, record[10], '\n');

        //if a match is found
        if (record[0] == voterID) {
            bool vote_confirmed = false;
            record_found = true;

            cout << "\nName: " << record[2] + " " + record[3] << endl 
                 << "Student ID: " << record[0] << endl
                 << "Surburb: " << record[5] << endl;
            if (record[9] == "Yes") {
                pause("Already voted. Please ask for assistance. ");
            } 
            else {
                while (!vote_confirmed) {
                    string selection, candidateID;
                    cout << "Please enter the candidate's ID you would like to vote for: ";
                    cin >> candidateID;
                    cout << "Are you sure you want to vote for this candidate? (Y)es/(N)o/(M)enu ";
                    cin >> selection;
                    if (selection == "Y" || selection == "y") {
                        vote_confirmed = true;
                        record[9] = "Yes";
                        record[10] = update_candidate(candidateID);
                    } 
                    else if (selection == "X" || selection == "x") {
                        break;
                    }
                }
            }
        }

        // write to new Candidate table
        for (int i=0; i<10; i++) {
            fout << record[i] << ',';
        }
        fout << record[10] << '\n';
    }

    fin.close();
    fout.close();

    //remove and replace the old database 
    remove(VOTER_FILENAME);
	rename(VOTER_NEW_FILENAME, VOTER_FILENAME);
}

void menu() {
    bool exit = false;
    string selection;

    while (exit == false) {
        cout << "\n\nSelect an option to get started\n";
        cout << "\t(P) Print all candidate information\n";
        cout << "\t(A) Add votes to a candidate\n";
        cout << "\t(S) Display candidate with smaller number of votes\n";
        cout << "\t(L) Display candidate with largest number of votes\n";
        cout << "\t(Q) Quit\n";
        cin >> selection;

        if (selection == "p" || selection == "P") {
            display_candidate_information(ALL);
        }
        else if (selection == "a" || selection == "A") {
            add_votes();
        }
        else if (selection == "s" || selection == "S") {
            display_candidate_information(LOW);
        }
        else if (selection == "l" || selection == "L") {
            display_candidate_information(HIGH);
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
