a.out: Recording.o RecordingCategory.o Loan.o LibraryPatron.o main.cpp
	g++ Recording.o RecordingCategory.o Loan.o LibraryPatron.o main.cpp

%.o: %.c %.h
	g++ -c %.c %.h

clean: 
	-@ rm *.o a.out
