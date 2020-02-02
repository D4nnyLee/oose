#ifndef _RECORDING_H_
#define _RECORDING_H_

#include <string>
#include <vector>

class Loan;
class RecordingCategory;

class Recording {
	private:
		std::string title;
		std::string aritst;
		std::vector<Loan*> loan;
		RecordingCategory * cateory;

		void addLoan(Loan * l) {
			loan.push_back(l);
		}

		friend class Loan;

	public:
		Recording(std::string, std::string, RecordingCategory*);

		std::string getTitle();
		std::string getArtist();
		RecordingCategory * getCategory();
		Loan * getLoan(int);
		int getLoanLength();
};

#endif
