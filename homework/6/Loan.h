#ifndef _LOAN_H_
#define _LOAN_H_

#include <string>

class LibraryPatron;
class Recording;

class Loan {
	private:
		std::string borrowedDate;
		std::string dueDate;
		std::string returnedDate;

		LibraryPatron * libraryPatron;
		Recording * collectionItem;

	public:
		Loan(LibraryPatron*, Recording*);

		std::string getBorrowedDate();
		std::string getDueDate();
		std::string getReturnedDate();

		void setBorrowedDate(std::string);
		void setDueDate(std::string);
		void setReturnedDate(std::string);
};

#endif
