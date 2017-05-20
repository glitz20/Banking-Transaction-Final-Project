//Simple Banking System Program created using Binary I/O//
//Submitted by Sabin Sapkota//
//Class Implementation File//

#include <iostream>
#include "Account.h"
#include <iomanip>
using namespace std;

void Account::create_acc()
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "\t\t\tEnter The Account ID :";
	cin >> ID;
	cout << endl;
	cout << "\t\t\tEnter the Name of The Account Holder : ";
	cin.ignore();//helps to ignore the /n character, when the user hits enter button//
	cin.getline(name, 100);
	cout << endl;
	cout << "\t\t\tEnter Type of Account(C for Current/S for Savings) : ";//to determine the withdrawal limit//
	cin >> type;
	cout << endl;
	//defines the limits of account types//
	cout << "\t\t\tEnter The Initial deposit amount(Minimum of $50 for Savings and $80 for current) : ";
	cin >> dep;
	cout << endl;
	cout << "\t\t\tCongratulations. New Account has been created in the name of " << name << endl;
}

void Account::acc_info() const
{

	cout << endl;
	cout << "\t\t\tAccount ID : " << ID << endl;
	cout << "\t\t\tAccount Holder Name : ";
	cout << name << endl;
	cout << "\t\t\tType of Account : " << type << endl;
	cout << "\t\t\tBalance amount : " << dep << endl;
}


void Account::modify()
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "\t\t\tAccount Number : " << ID;
	cout << "\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 100);
	cout << "\t\t\tModify Type of Account : ";
	cin >> type;

}

void Account::deposit(int x)
{
	dep += x;
}

void Account::withdraw(int x)
{
	dep -= x;
}

void Account::report() const
{
	cout << ID << setw(10) << " " << name << setw(10) << " " << type << setw(6) << dep << endl;
}

int Account::return_id() const
{
	return ID;
}

int Account::return_bal() const
{
	return dep;
}

char Account::acctype() const
{
	return type;
}
