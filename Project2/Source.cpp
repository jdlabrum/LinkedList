#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

struct studenttype
{
	int id;
	string first, last, degree;
	int crhrs;
	double gpa;
	studenttype *link;
};

void createem(studenttype *&head, studenttype *&tail)
{
	head = new studenttype;
	tail = new studenttype;

	head->id = -1;
	head->first = "Luke";
	head->last = "Skywalker";
	head->degree = "Jedi";
	head->crhrs = -1;
	head->gpa = 5.0;
	head->link = tail;
	tail->id = -2;
	tail->first = "Darth";
	tail->last = "Vader";
	tail->degree = "Sith";
	tail->crhrs = -2;
	tail->gpa = 6.0;
	tail->link = NULL;
}

bool emptylist(studenttype *&head, studenttype *&tail)
{
	return head->link == tail;
}

void printheader(ofstream &outf)
{
	outf << endl << setw(29) << "Peterson College" << endl << setw(37) << "Advisees of Professor Pete Peters"
		<< endl << setw(33) << "Fall 2013 to Spring 2014" << endl << endl << left << setw(5) << "ID" << setw(18)
		<< "Student Name" << setw(8) << "Degree" << setw(7) << "CrHrs" << " GPA" << endl;
	for (int i = 0; i<42; i++)	outf << '-';
	outf << endl;
}

void traversalprint(studenttype *&head, studenttype *&tail, ofstream &outf)
{
	studenttype *current;
	string dummy;	
	current = head->link;

	printheader(outf);
	if (!emptylist(head, tail))
	{
		while (current != tail)
		{
			dummy = current->last + ", " + current->first;
			outf << left << setw(5) << current->id << setw(18) << dummy << setw(8) <<current->degree << right 
				<< setw(5)<< current->crhrs << showpoint << setprecision(3) <<setw(6)<< current->gpa<< endl;
			current = current->link;
		}
	}
	else outf << "\n\nThe list is empty.";
}

void initializeknew(studenttype *&knew)
{
	knew->id = -007;
	knew->first = "James";
	knew->last = "Bond";
	knew->degree = "Classified";
	knew->crhrs = -5;
	knew->gpa = 7.00;
	knew->link = NULL;
}

void insertlist(studenttype *&head, studenttype *&tail, ifstream &inf)
{
	studenttype *knew, *prior, *next;
	knew = new studenttype;
	initializeknew(knew);
	prior = head;
	next = head->link;

		inf >> knew->id >> knew->first >> knew->last >> knew->degree >> knew->crhrs >> knew->gpa;
		while (next != tail&&next->id < knew->id)
		{
			prior = next;
			next = next->link;
		}

		prior->link = knew;
		knew->link = next;
}

void readdata(studenttype *&head, studenttype *&tail)
{
	ifstream inf("Assign2.dat");
	while (!inf.eof())
	{
		insertlist(head, tail, inf);
	}
}

void deleteem(studenttype *&head, studenttype *&tail, int id)
{
	studenttype *current, *prior, *next;

	prior = head;
	current = head->link;

	while (current != tail&&current->id < id)
	{
		prior = current;
		current = current->link;
	}
	if (current->id == id)
	{
		next = current->link;
		prior->link = next;
		delete current;
		cout <<"Student "<< id << " has been deleted.";
	}
	else
		cout << "\nID not found.\n";
}

void hardadd(studenttype *&head, studenttype *&tail, int number, string fname, string lname, string deg, int creds, double GPA)
{
	studenttype *knew, *prior, *next;
	knew = new studenttype;

	initializeknew(knew);

	prior = head;
	next = head->link;

	knew->id = number;
	knew->first = fname;
	knew->last = lname;
	knew->degree = deg;
	knew->crhrs = creds;
	knew->gpa = GPA;

	while (next != tail&&next->id < knew->id)
	{
		prior = next;
		next = next->link;
	}
	prior->link = knew;
	knew->link = next;
}

void traversingcalc(studenttype *&head, studenttype *&tail, ofstream &outf)
{
	studenttype *current;
	int counter=0;
	double creditcalc=0;
	double gpacalc=0;

	current = head->link;
	
	if (!emptylist(head, tail))
	{
		while (current != tail)
		{
			gpacalc = gpacalc+current->gpa;
			creditcalc = creditcalc+current->crhrs;
			current = current->link;
			counter++;
		}
		outf << endl << right << setw(36) << "Average GPA: " << setw(6) << gpacalc / counter;
		outf << endl << right << setw(36) << "Average nubmber of credit hours: " << setw(6) << creditcalc / counter;
	}
	else outf << "\nThe list is empty.";
}

void main()
{
	ofstream outf("Assign2.out");
	studenttype *head, *tail;

	createem(head, tail);
	readdata(head, tail);
	traversalprint(head, tail, outf);
	deleteem(head, tail, 3966);
	hardadd(head, tail, 6000, "Jimmy", "Fallon", "BA", 15, 2.1);
	traversalprint(head, tail, outf);
	traversingcalc(head, tail, outf);
}

