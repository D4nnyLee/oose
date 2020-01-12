# Homework 1
Movie ticket ordering system

---
## Configure file
The program will construct the ordering system depending on this file

### Format

+ (Each Theater)
	* Theater Name
	* Size
	* (Each date)
		- Date
		- (Each Movie)
			+ Movie name
			+ Length (HH:MM)
			+ Time (HH:MM)
		- (Each Ticket)
			+ Ticket name
			+ Price

Some types will have an integer before it, which means the number of that type.

---
## Recording file
Recording how much tickets were sold and their price.

### Format

* (Each order)
	+ Index
	+ Theater
	+ Date
	+ Movie
	+ Time
	+ (Each ticket)
		- Number

		
---
## Program

Classes:
+ User
+ Theater
