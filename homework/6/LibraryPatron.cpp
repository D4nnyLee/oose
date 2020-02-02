#include "Loan.h"
#include "Recording.h"
#include "LibraryPatron.h"

LibraryPatron::LibraryPatron() {}

Loan * LibraryPatron::getLoan(int idx) {
	return loan[idx];
}

int LibraryPatron::getLoanLength() {
	return loan.size();
}

void LibraryPatron::borrowItem(Recording * item) {
	Loan * tmp = new Loan(this, item);
	tmp->setBorrowedDate("");
	tmp->setDueDate("");
	loan.push_back(tmp);
}

void LibraryPatron::ReturnItem(Loan * retLoan) {
	retLoan->setReturnedDate("");
}
