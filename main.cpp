#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

#define BOOK_BORROW_LENGTH 10
#define REFERENCE_BORROW_LENGTH 5
#define MAGAZINE_BORROW_LENGTH 2

#define BOOK_EXTENDING_TIMES 2
#define MAGAZINE_EXTENDING_TIMES 0


#define EMPTY ""

#define number_of_book_can_borrowed_by_professor 5
#define number_of_book_can_borrowed_by_studen



class Book
{
	public:

		book(string _title, int _copies);
		bool isAvailable();
		string getTitle();
		void borrow(int currentTime);
		int return_document();
		int extend();
		bool canBeExtended(int currentTime);

	private:
		string title;
		//int copies;
		bool isBorrowed;
		int borrowStartTime;
		int dueTime;
		int extendedTimes;

	protected:
		int borrowLength;
		int calcPenalty(int currentTime);
		void setDueTime(int currentTime);


};

Book::book(string _title, int _copies)
{
	title = _title;
	copies = _copies;
	isBorrowed =false;
	extendedTimes = 0;
	borrowedCopies = 0;
	//setBorrowLength();
}

string Book::getTitle()
{
	return title;
}

bool Book::isAvailable()
{
	return !isBorrowed;
}

bool Book::canBeExtended(int currentTime)
{
	return currentTime < dueTime;
}

void Book::borrow(int currentTime)
{
	dueTime = setDueTime();
}

int return_document(int currentTime)
{
	isBorrowed = false;
	return calcPenalty(currentTime);
}


class Reference : public Book
{

};

Reference::Reference(string _title, int copies):Book(_title, _copies)
{
	borrowLength = REFERENCE_BORROW_LENGTH;
}


class Magazine : public Book
{
	public:
		Magazine(int year, int number);
	private:
		int year;
		int number;

};

Magazine::Magazine(string _title, int copies, int year, int number):Book(_title,_copies)
{
	borrowLength = MAGAZINE_BORROW_LENGTH;
}






class User
{
public:
	User(string name_);

	virtual void addBook(Book* book) = 0;

	void deleteBook(string bookName);

	void increasetotalPenalty(int penalty);

protected:
	string name;

	vector <Book*> borrowedBooks;

	int totalPenalty;

};

User::User(string name_)
{
	if (name_ != EMPTY)
	{
		name = name_;
		totalPenalty = 0;
	}
	//else 
		//throw runtime_error("name could not be empty");
}

void User::deleteBook(string bookName)
{
	for (int i = 0; i < borrowedBooks.size(); i++)
	{
		if (borrowedBooks[i]->getName() == bookName)
			borrowedBooks.erase(borrowedBooks.begin() + i);
	}
}

void User::increasetotalPenalty(int penalty)
{
	totalPenalty += penalty;
}








class Professor : public User
{
public:
	Professor(string name);

	virtual void addBook(Book* book);

private:

	int numberOfBookCanBorrowed = number_of_book_can_borrowed_by_professor;

};

Professor::Professor(string name)
					:User(name)
{

}

void Professor::addBook(Book* book)
{
	if (borrowedBooks.size() < numberOfBookCanBorrowed)
		borrowedBooks.push_back(book);
	//else
		//throw runtime_error("professor can not borrow more than 5 books");
}









class Student : public User
{
public:
	Student(string student_id, string student_name);

	virtual void addBook(Book* book);

private:
	string id;

	int numberOfBookCanBorrowed = number_of_book_can_borrowed_by_student;

};

Student::Student(string student_id, string student_name)
				:User(student_name)
{
	if (student_id != EMPTY)
		id = student_id;
	//else
		//throw runtime_error("student_id is not valid")
}

void Student::addBook(Book* book)
{
	if (borrowedBooks.size() < numberOfBookCanBorrowed)
		borrowedBooks.push_back(book);
	//else
		//throw runtime_error("students can not borrow more than 5 books");
}





class Library // class asli bara handling
{
public :
	void add_student_member(string student_id, string student_name);

	void add_prof_member(string prof_name);

	void add_book(string book_title, int copies);

	void add_magazine(string magazine_title, int year, int number, int copies);

	void add_reference(string reference_title, int copies);

	void borrow(string member_name, string document_title);

	void extend(string member_name, string document_title);

	void return_document(string member_name, string document_title);

	int get_total_penalty(string member_name);

	int time_pass(int days);

	vector<string> available_titles();

private:

	vector <Book*> books;
	vector <User*> users;

};

void Library::add_student_member(string student_id, string student_name)
{
	Student* student = new Student(student_id, student_name);
	users.push_back(student);
}

void Library::add_prof_member(string prof_name)
{
	Professor* professor = new Professor(prof_name);
	users.push_back(professor);
}

void Library::add_book(string book_title, int copies)
{
	Book* book = new Book(book_title, copies);
	books.push_back(book);
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	Magazine* magazine = new Magazine(magazine_title, year, number, copies);
	books.push_back(magazine);
}

void Library::add_reference(string reference_title, int copies)
{
	Reference* reference = new Reference(reference_title, copies);
	books.push_back(reference);
}


int main()
{

}