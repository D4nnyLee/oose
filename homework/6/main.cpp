#include <iostream>
#include "RecordingCategory.h"
#include "Recording.h"
#include "LibraryPatron.h"
#include "Loan.h"

using namespace std;

int mainMenu() {
	int choice = 0;
	cout << "+---------------------------------\n";
	cout << "|0. Exit\n";
	cout << "|1. Borrow.\n";
	cout << "|2. Return.\n";
	cout << "|3. Show loans of collection item.\n";
	cout << "|4. Show loans of library patron.\n";
	cout << "|5. Get item by category.\n";
	cout << "+---------------------------------\n";
	cout << "Choice: ";
	cin >> choice;
	return choice;
}

int categoryMenu() {
	int choice;
	cout << "+---------------------------\n";
	cout << "|0. Cancel.\n";
	cout << "|1. Show subcategory.\n";
	cout << "|2. Show items.\n";
	cout << "|3. Choose subcategory.\n";
	cout << "|4. Choose item.\n";
	cout << "+---------------------------\n";
	cout << "Choice: ";
	cin >> choice;
	return choice;
}

void showItemInfo(Recording * item) {
	string title = item->getTitle(), artist = item->getArtist(), border(max(title.size(), artist.size()), '-');
	cout << '+' << border << '\n';
	cout << '|' << title << '\n';
	cout << '|' << artist << '\n';
	cout << '+' << border << '\n';
}

void borrowItem(LibraryPatron * patron, Recording * item) {
	if (!item) {
		cout << "Please get an item first!" << endl;
		return;
	}
	patron->borrowItem(item);
}

void showLoan(Recording * item) {
	if (!item) {
		cout << "Please get an item first!" << endl;
		return;
	}
	cout << "Item information:\n";
	showItemInfo(item);
	int len = item->getLoanLength();
	for (int i = 0; i < len; i++) {
		Loan * tmp = item->getLoan(i);
		cout << i << ":\n";
		cout << "\tBorrowed date: " << tmp->getBorrowedDate() << '\n';
		cout << "\tDue date: " << tmp->getDueDate() << '\n';
		cout << "\tReturned date: " << tmp->getReturnedDate() << '\n';
	}
}

void showLoan(LibraryPatron * patron) {
	int len = patron->getLoanLength();
	for (int i = 0; i < len; i++) {
		Loan * tmp = patron->getLoan(i);
		cout << i << ":\n";
		cout << "\tBorrowed date: " << tmp->getBorrowedDate() << '\n';
		cout << "\tDue date: " << tmp->getDueDate() << '\n';
		cout << "\tReturned date: " << tmp->getReturnedDate() << '\n';
	}
}

void showSubcategory(RecordingCategory * category) {
	int len = category->getSubcategoryLength();
	for (int i = 0; i < len; i++) 
		cout << i << ": " << category->getSubcategory(i)->getLabel() << '\n';
}

void showItem(RecordingCategory * category) {
	int len = category->getRecordingLength();
	for (int i = 0; i < len; i++) {
		cout << i << ":\n";
		showItemInfo(category->getRecording(i));
	}
}

Recording * getItem(RecordingCategory * category) {
	int index;
	bool loop = true;
	Recording * item = NULL;
	while (loop) {
		int choice = categoryMenu();
		system("clear");
		switch (choice) {
			case 1:
				showSubcategory(category);
				break;

			case 2:
				showItem(category);
				break;

			case 3:
				cout << "Input index: ";
				cin >> index;
				return getItem(category->getSubcategory(index));

			case 4:
				cout << "Input index: ";
				cin >> index;
				return category->getRecording(index);

			default:
				loop = false;
		}
	}
	return item;
}

int main() {
	LibraryPatron * user = new LibraryPatron();
	RecordingCategory * topCategory = new RecordingCategory("audio");
	RecordingCategory * classical = topCategory->addSubcategory("classical");
	classical->addRecording("9th Symphony", "Beethoven");
	Recording * item = NULL;
	bool loop = true;
	while (loop) {
		int choice = mainMenu();
		system("clear");
		switch (choice) {
			case 1:
				borrowItem(user, item);
				item = NULL;
				break;

			case 2:
				break;
				
			case 3:
				showLoan(item);
				break;

			case 4:
				showLoan(user);
				break;

			case 5:
				item = getItem(topCategory);
				break;

			default:
				loop = false;
		}
	}
	return 0;
}
