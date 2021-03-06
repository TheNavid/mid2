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
#define REFERENCE_EXTENDING_TIMES 2


#define EMPTY ""

#define number_of_book_can_borrowed_by_professor 5
#define number_of_book_can_borrowed_by_student 2



class Book
{
	public:

		Book(string _title);
		bool is_available();
		string get_title();
		void borrow(int current_time);
		int return_document(int current_time);
		bool extend(int current_time);
		virtual int calc_penalty(int current_time);

		

	private:
		string title;
		bool is_borrowed;
		int extended_times;
		bool can_be_extended(int current_time);
		

	protected:
		int borrow_length;
		int extending_limit;
		int due_time;

};

Book::Book(string _title)
{
	title = _title;
	is_borrowed =false;
	extended_times = 0;
	borrow_length = BOOK_BORROW_LENGTH;
	extending_limit = BOOK_EXTENDING_TIMES;
}

string Book::get_title()
{
	return title;
}

bool Book::is_available()
{
	return !is_borrowed;
}

bool Book::can_be_extended(int current_time)
{
	return current_time < due_time && extended_times < extending_limit;
}

void Book::borrow(int current_time)
{
	due_time = current_time + borrow_length;
	is_borrowed = true;
}

int Book::return_document(int current_time)
{
	is_borrowed = false;
	return calc_penalty(current_time);
}

bool Book::extend(int current_time)
{
	if (can_be_extended(current_time))
	{
		due_time += borrow_length;
	}
	else
	{
		throw runtime_error("Can not extend the book");
	}
}

int Book::calc_penalty(int current_time)
{
	int penalty = 0;
	int delay = current_time - due_time;
	if(delay <=0)
	{
		return 0;
	}
	else
	{
		if(delay <=7)
		{
			penalty += delay * 2000;
		}
		if(delay > 7)
		{
			if(delay <= 21)
			{
				penalty += (delay-7) * 3000;
			}
			else
			{
				penalty += 14 * 3000;
			}
		}
		if(delay > 21)
		{
			penalty += (delay-21) *3000;
		}
	}
	return penalty;
}





class Reference : public Book
{
	public:
		Reference(string _title);
		virtual int calc_penalty(int current_time);
};

Reference::Reference(string _title): Book(_title)
{
	borrow_length = REFERENCE_BORROW_LENGTH;
	extending_limit = REFERENCE_EXTENDING_TIMES;
}

int Reference::calc_penalty(int current_time)
{
	int penalty = 0;
	int delay = current_time - due_time;
	if(delay <=0)
	{
		return 0;
	}
	else
	{
		if(delay <=3)
		{
			penalty += delay * 5000;
		}
		if(delay > 3)
		{
			penalty += (delay-3) * 7000;
		}
	}
	return penalty;
}






class Magazine : public Book
{
	public:
		Magazine(string _title, int year, int number);
		virtual int calc_penalty(int current_time);
	private:
		int year;
		int number;

};

Magazine::Magazine(string _title, int _year, int _number):Book(_title)
{
	if (_year > 0 && _number >= 0)
	{
		year =_year;
		number = _number;
		borrow_length = MAGAZINE_BORROW_LENGTH;
		extending_limit = MAGAZINE_EXTENDING_TIMES;
	}
	else if (_year <= 0)
		throw runtime_error("invalid year");
	else if (_number < 0)
		throw runtime_error("invalid magazine number");	
}

int Magazine::calc_penalty(int current_time)
{
	int penalty = 0;
	int delay = current_time - due_time;
	if(delay <=0)
	{
		return 0;
	}
	else
	{
		if(year < 1390)
		{
			penalty += delay * 2000;
		}
		else
		{
			penalty += delay * 3000;
		}
	}
	return penalty;
}




class User
{
public:
	User(string name_);

	virtual void add_book(Book* book) = 0;

	void delete_book(string book_name);

	void increase_total_penalty(int penalty);

	string get_name();

	int get_penalty();

protected:
	string name;

	vector <Book*> borrowed_books;

	int total_penalty;

};

User::User(string name_)
{
	if (name_ != EMPTY)
	{
		name = name_;
		total_penalty = 0;
	}
	else 
		throw runtime_error("name could not be empty");
}

void User::delete_book(string book_name)
{
	for (int i = 0; i < borrowed_books.size(); i++)
	{
		if (borrowed_books[i]->get_title() == book_name)
			borrowed_books.erase(borrowed_books.begin() + i);
	}
}

void User::increase_total_penalty(int penalty)
{
	total_penalty += penalty;
}

string User::get_name()
{
	return name;
}

int User::get_penalty()
{
	return total_penalty;
}








class Professor : public User
{
public:
	Professor(string name);

	virtual void add_book(Book* book);

private:

	int number_of_book_can_borrowed = number_of_book_can_borrowed_by_professor;

};

Professor::Professor(string name)
					:User(name)
{

}

void Professor::add_book(Book* book)
{
	if (borrowed_books.size() < number_of_book_can_borrowed)
		borrowed_books.push_back(book);
	else
		throw runtime_error("professor can not borrow more than 5 books");
}






class Student : public User
{
public:
	Student(string student_id, string student_name);

	virtual void add_book(Book* book);

private:
	string id;

	int number_of_book_can_borrowed = number_of_book_can_borrowed_by_student;

};

Student::Student(string student_id, string student_name)
				:User(student_name)
{
	if (student_id != EMPTY)
		id = student_id;
	else
		throw runtime_error("student_id is not valid");
}

void Student::add_book(Book* book)
{
	if (borrowed_books.size() < number_of_book_can_borrowed)
		borrowed_books.push_back(book);
	else
		throw runtime_error("students can not borrow more than 2 books");
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

	void time_pass(int days);

	vector<string> available_titles();

private:

	bool is_user_exists(string name);

	bool is_book_exists(string name);

	bool added_before(vector <string> names, string name);

	User* find_user(string member_name);

	Book* find_book(string book_name);

	vector <string> available_books;

	vector <Book*> books;
	vector <User*> users;
	int time;

};


bool Library::added_before(vector <string> names, string name)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == name)
			return true;
	}
	return false;
}

vector<string> Library::available_titles()
{
	vector <string> available_titles;
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i]->is_available() && !added_before(available_titles, books[i]->get_title()))
			available_titles.push_back(books[i]->get_title());
	}
	return available_titles;
}

User* Library::find_user(string member_name)
{
	for(int i=0;i<users.size();i++)
	{
		if(users[i]->get_name() == member_name)
		{
			return users[i];
		}
	}
	return NULL;
}

Book* Library::find_book(string book_name)
{
	for(int i=0;i<books.size();i++)
	{
		if(books[i]->get_title() == book_name)
		{
			return books[i];
		}
	}
	return NULL;
}





void Library::time_pass(int days)
{
	if (days >= 0)
		time += days;
	else 
		throw runtime_error("invalid day");
}

bool Library::is_user_exists(string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_name() == name)
			return true;
	}
	return false;
}

bool Library::is_book_exists(string name)
{
	for (int i = 0; i < available_books.size(); i++)
	{
		if (available_books[i] == name)
			return true;
	}
	return false;	
}


void Library::add_student_member(string student_id, string student_name)
{
	//must be test
	try
	{
		if (!is_user_exists(student_name))
		{
			Student* student = new Student(student_id, student_name);
			users.push_back(student);
		}
		else
			throw runtime_error("Student has already joined");
	}catch(runtime_error &ex)
	{
			cerr << ex.what() << endl;
	}
}

void Library::add_prof_member(string prof_name)
{
	try
	{
		if (!is_user_exists(prof_name))
		{
			Professor* professor = new Professor(prof_name);
			users.push_back(professor);
		}
		else
			throw runtime_error("Professor has already joined");
	}catch(runtime_error &ex)
	{
			cerr << ex.what() << endl;
	}
}

void Library::add_book(string book_title, int copies)
{
	//Exists book
	try
	{
		if (!is_book_exists(book_title))
		{
			for (int i = 0; i < copies; i++)
			{
				Book* book = new Book(book_title);
				books.push_back(book);
			}
			available_books.push_back(book_title);
		}
		else
			throw runtime_error("Book has already added");
	}catch(runtime_error &ex)
	{
		cerr << ex.what() << endl;
	}
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	//Exists book
	try
	{
		if (!is_book_exists(magazine_title))
		{
			for (int i = 0; i < copies; i++)
			{
				Magazine* magazine = new Magazine(magazine_title, year, number);
				books.push_back(magazine);
			}
			available_books.push_back(magazine_title);
		}
		else 
			throw runtime_error("Magazine has already added");
	}catch(runtime_error &ex)
	{
		cerr << ex.what() << endl;
	}
}

void Library::add_reference(string reference_title, int copies)
{
	//Exists book
	try
	{
		if (!is_book_exists(reference_title))
		{	
			for (int i = 0; i < copies; i++)
			{
				Reference* reference = new Reference(reference_title);
				books.push_back(reference);
			}
			available_books.push_back(reference_title);
		}
		else
			throw runtime_error("Reference has already added");
	}catch(runtime_error &ex)
		{
			cerr << ex.what() << endl;
		}
}

int Library::get_total_penalty(string member_name)
{

	try
		{
			if (!is_user_exists(member_name))
			{
				throw runtime_error("Student has already joined");
			}
			else
			{
				User* user = find_user(member_name);
				return user->get_penalty();
			}
				
		}catch(runtime_error &ex)
		{
				cerr << ex.what() << endl;
		}
	return 0;
}




int main()
{

}