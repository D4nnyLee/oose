#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

int config();
void showSales();

class Theater {

public:
	Theater(ifstream &fin) {
		getline(fin.ignore(), Name) >> Seats;
		int numOfDate;
		fin >> numOfDate;
		for (int i = 0; i < numOfDate; i++) {
			string date;
			int numOfMovie, numOfTicket;
			fin >> date >> numOfMovie;
			while (numOfMovie--) {
				MovieList[date].push_back(new Movie(fin, Seats));
			}
			fin >> numOfTicket;
			while (numOfTicket--) {
				TicketList[date].push_back(new Ticket(fin));
			}
		}
	}

	bool sellTickets(int index) {
		string date, movie, time;
		cout << "Date: ";
		getline(cin, date);
		if (MovieList[date].size() == 0) {
			cout << "There is no movie in " << date << '.' << endl;
			MovieList.erase(date);
			return false;
		}
		cout << "Movie: ";
		getline(cin, movie);
		cout << "Time: ";
		getline(cin, time);
		for (auto &i: MovieList[date]) {
			if (i->Name == movie) {
				if (i->Seats[time] == 0) {
					if (i->Seats.find(time) != i->Seats.end()) {
						cout << "No seat remaining" << endl;
					}
					else {
						cout << "No such time." << endl;
					}
					return false;
				}
				std::ofstream fout("ordering_record.txt", ios::app);
				if (!fout.is_open()) {
					cout << "Fail to write ordering_record.txt." << endl;
					exit(1);
				}
				fout << index << '\n' << Name << '\n' << date << '\n' << movie << '\n' << time << '\n';
				int cnt = 0;
				cout << "Tickets:" << endl;
				for (auto &j: TicketList[date]) {
					cout << "\t" << j->Name << ": $" << j->Price << endl;
				}
				cout << "Input the number of each ticket" << endl;
				for (auto &j: TicketList[date]) {
					int num;
					cout << j->Name << ": ";
					cin >> num;
					cnt += num*j->Price;
					i->Sold[j] += num;
					i->Seats[time] -= num;
					fout << num << '\n';
				}
				cout << "Success!\nTotal: $" << cnt << endl;
				fout.close();
				return true;
			}
		}
		cout << "No such movie or time" << endl;
		return false;
	}

	void listMovies() {
		for (auto &i: MovieList) {
			cout << i.first << endl;
			for (Movie *j: i.second) {
				cout << "\t" << j->Name << endl;
			}
		}
	}

	void movieInformations(string &name) {
		for (auto &i: MovieList) {
			bool outputDate = true;
			for (auto &j: i.second) {
				if (j->Name == name) {
					if (outputDate) {
						cout << i.first << endl;
						outputDate = false;
					}
					cout << "\tLength (HH:MM): " << j->Length << endl;
					cout << "\tTime (HH:MM) && Seats: " << endl;
					for (auto &k: j->Seats) {
						cout << "\t\t" << k.first << ": " << k.second << '/' << Seats << endl;
					}
				}
			}
		}
	}

	string getName() {
		return Name;
	}

private:
	struct Ticket {
		Ticket(ifstream &fin) {
			getline(fin.ignore(), Name) >> Price;
		}
		string Name;
		int Price;
	};

	struct Movie {
		Movie(ifstream &fin, int seats) {
			int numOfTime;
			getline(fin.ignore(), Name) >> Length >> numOfTime;
			while (numOfTime--) {
				string time;
				fin >> time;
				Seats[time] = seats;
			}
		}
		string Name;
		string Length;
		map<string, int> Seats; // <time, seats>
		map<Ticket*, int> Sold;
	};

	void modifySeats(ifstream &fin) {
		string date, movie, time, type;
		int numOfType, num;
		fin >> date;
		getline(fin.ignore(), movie) >> time;
		for (auto &m: MovieList[date]) {
			if (m->Name == movie) {
				for (auto &t: TicketList[date]) {
					fin >> num;
					m->Sold[t] += num;
					m->Seats[time] -= num;
				}
				return;
			}
		}
	}

	friend int config();
	friend void showSales();

	string Name;
	int Seats;
	map<string, vector<Movie*> > MovieList; // <date, movies>
	map<string, vector<Ticket*> > TicketList; // <date, tickets>
};

class User {

public:
	User (int index): Index(index) {}

	bool buyTickets(Theater *t) {
		return t->sellTickets(Index);
	}

private:
	int Index;
};

vector<Theater*> TheaterList;

int config() {
	int index = -1; // index of user
	ifstream fin("config.txt", ios::in);
	if (!fin.is_open()) {
		cout << "Fail to read config.txt." << endl;
		exit(1);
	}
	int numOfTheater;
	fin >> numOfTheater;
	while (numOfTheater--) {
		TheaterList.push_back(new Theater(fin));
	}
	fin.close();
	// read record here
	fin.open("ordering_record.txt", ios::in);
	if (!fin.is_open()) {
		cout << "Fail to read ordering_record.txt." << endl;
		exit(1);
	}
	while (fin >> index) {
		string theater;
		getline(fin.ignore(), theater);
		for (auto &i: TheaterList) {
			if (i->getName() == theater) {
				i->modifySeats(fin);
				break;
			}
		}
	}
	fin.close();
	return index + 1;
}

int menu() {
	int choice;
	cout << "+-------------------------------+" << endl;
	cout << "|1. Buy tickets.                |" << endl;
	cout << "|2. List theaters.              |" << endl;
	cout << "|3. List movies.                |" << endl;
	cout << "|4. Movie informations          |" << endl;
	cout << "|5. Show current sales status.  |" << endl;
	cout << "|6. exit.                       |" << endl;
	cout << "+-------------------------------+" << endl;
	cout << "> ";
	cin >> choice;
	return choice;
}

bool buyTickets(User *user) {
	string theater;
	cout << "Theater: ";
	getline(cin.ignore(), theater);
	for (auto &i: TheaterList) {
		if (i->getName() == theater) {
			return user->buyTickets(i);
		}
	}
	cout << "No such theater." << endl;
	return false;
}

void listTheaters() {
	for (Theater *i: TheaterList) {
		cout << i->getName() << endl;
	}
}

void listMovies() {
	cout << "Theater: ";
	string name;
	getline(cin.ignore(), name);
	for (auto &i: TheaterList) {
		if (i->getName() == name) {
			i->listMovies();
			return;
		}
	}
	cout << "No such theater." << endl;
}

void movieInformations() {
	string theater, movie;
	cout << "Theater: ";
	getline(cin.ignore(), theater);
	cout << "Movie: ";
	getline(cin, movie);
	for (auto &i: TheaterList) {
		if (i->getName() == theater) {
			i->movieInformations(movie);
			return;
		}
	}
	cout << "No such theater." << endl;
}

void showSales() {
	int income = 0;
	for (auto &theater: TheaterList) {
		cout << theater->getName() << endl;
		for (auto &i: theater->MovieList) {
			cout << '\t' << i.first << endl;
			for (auto &m: i.second) {
				cout << "\t\t" << m->Name << endl;
				for (auto &t: theater->TicketList[i.first]) {
					cout << "\t\t\t" << t->Name << "($" << t->Price << "): " << m->Sold[t] << endl;
					income += t->Price*m->Sold[t];
				}
			}
		}
	}
	cout << "Total sales: $" << income << endl;
}

int main(int argc, char** argv) {
	int index;
	index = config();
	User *user = new User(index++);
	bool operating = true;
	while (operating) {
		int choice = menu();
		switch (choice) {
			case 1:
				if (buyTickets(user)) {
					user = new User(index++);
				}
				break;
			case 2:
				listTheaters();
				break;
			case 3:
				listMovies();
				break;
			case 4:
				movieInformations();
				break;
			case 5:
				showSales();
				break;
			case 6:
				operating = false;
				break;
			default:
				cout << "No such choice" << endl;
		}
	}
	return 0;
}
