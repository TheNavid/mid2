#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;



class book
{

}

class Reference : public book
{

}

class Magazine : public book
{

}








class User
{
public:

protected:
	string name;
	vector <Book*>

}

User::User(string name_)
{
	name = name_;
}

class Professor : public User
{

}

class Student : public User
{

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

}

void Library::add_student_member(string student_id, string student_name)
{
	Student* student = new Student(student_id, student_name);
	User.push_back(student);
}

void Library::add_prof_member(string prof_name)
{
	Professor* professor = new Professor(prof_name);
	User.push_back(professor);
}

void Library::add_book(string book_title, int copiese)
{
	Book* book = new Book(book_title, copiese);
	Book.push_back(book);
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	Magazine* magazine = new Magazine(magazine_title, year, number, copiese);
	Book.push_back(magazine);
}

void Library::add_reference(string reference_title, int copiess)
{
	Reference* reference = new Reference(reference_title, copiese);
	Book.push_back(reference);
}


int main()
{

}