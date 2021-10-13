#include <iostream>
#include <string>

using namespace std;

void print_candidate_information() {
	string temp;
	cout << "print_candidate_information() placeholder, press enter to return to main menu\n";
	cin.ignore();
	temp = cin.get();
}

void add_votes() {
	string temp;
	cout << "add_votes() placeholder, press enter to return to main menu\n";
	cin.ignore();
	temp = cin.get();
}

void display_losing_candidate() {
	string temp;
	cout << "display_losing_candidate() placeholder, press enter to return to main menu\n";
	cin.ignore();
	temp = cin.get();
}

void display_winning_candidate() {
	string temp;
	cout << "display_winning_candidate() placeholder, press enter to return to main menu\n";
	cin.ignore();
	temp = cin.get();
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
			string temp;
			cout << "Invalid selection, press enter to return to main menu\n";
			cin.ignore();
			temp = cin.get();
		}
	}
}

int main()
{
	menu(); // main menu for the program
}

