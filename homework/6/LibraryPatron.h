#ifndef _LIBRARYPATRON_H_
#define _LIBRARYPATRON_H_

#include <vector>

class Loan;
class Recording;

class LibraryPatron {
	private:
		std::vector<Loan*> loan;

	public:
		LibraryPatron();

		Loan * getLoan(int);
		int getLoanLength();

		void borrowItem(Recording*);
		void ReturnItem(Loan*);
};

#endif
