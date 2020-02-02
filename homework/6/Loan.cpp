#include <string>
#include "Loan.h"
#include "Recording.h"
#include "LibraryPatron.h"

Loan::Loan(LibraryPatron * patron, Recording * recording):
	libraryPatron(patron), collectionItem(recording), 
	borrowedDate(""), dueDate(""), returnedDate("")
{
	recording->addLoan(this);
}

std::string Loan::getBorrowedDate() {
	return borrowedDate;
}

std::string Loan::getDueDate() {
	return dueDate;
}

std::string Loan::getReturnedDate() {
	return returnedDate;
}

void Loan::setBorrowedDate(std::string date) {
	borrowedDate = date;
}

void Loan::setDueDate(std::string date) {
	dueDate = date;
}

void Loan::setReturnedDate(std::string date) {
	returnedDate = date;
}
