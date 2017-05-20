//Simple Banking System Program created using Binary I/O//
//Submitted by Sabin Sapkota//
//Main File//

#include<iostream> 
#include<fstream>    
#include<cctype>      
#include<iomanip> 
#include "Account.h"
using namespace std; 
//This is Bank Account Management Program where the user can make new account, check balance,//
//do financial transaction, or delete the account and the account is updated//
 
void write_acc();    //function to write record in binary file
void display_sp(int);    //function to display account details given by user
void modify_acc(int);    //function to modify record of file
void delete_acc(int);    //function to delete record of file
void dep_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();    //introductory screen function
void thankyou();//thankyou screen//

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");   //Clear The Screen
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		//main menu//
		cout << "\t\t\t\t\t\t\t"<<setw(9)<<"MENU" << endl;
		cout << "\t\t\t\t\t\t-----------------------------" << endl;
		cout <<  "\t\t\t\t\t\t01. NEW ACCOUNT" << endl;
		cout <<  "\t\t\t\t\t\t02. DEPOSIT" << endl;
		cout <<  "\t\t\t\t\t\t03. WITHDRAW" << endl;
		cout <<  "\t\t\t\t\t\t04. ACCOUNT AND BALANCE ENQUIRY"<<endl;
		cout <<  "\t\t\t\t\t\t05. CLOSE AN ACCOUNT"<<endl;
		cout <<  "\t\t\t\t\t\t06. MODIFY AN ACCOUNT"<<endl;
		cout << "\t\t\t\t\t\t07. EXIT"<<endl;
		cout << endl;
		cout << endl;
		cout <<  "\t\t\t\t\t\tChoose your option by entering the number: ";
		cin >> ch;
		system("cls");   //Clear The Screen
		switch (ch)
		{
			//different output according to the user input from the menu//
		case '1':
			write_acc();
			break;
		case '2':
			cout << endl;
			cout << endl;
			cout << endl;
            cout << "\t\t\tEnter The Account Number : "; cin >> num;
			dep_withdraw(num, 1);
			break;
		case '3':
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tEnter The Account Number : "; cin >> num;
			dep_withdraw(num, 2);
			break;
		case '4':
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tEnter The Account Number : "; cin >> num;
			display_sp(num);
			break;
		
		case '5':
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tEnter The Account Number : "; cin >> num;
			delete_acc(num);
			break;
		case '6':
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tEnter The Account Number : "; cin >> num;
			modify_acc(num);
			break;
		case '7':
			cout << endl;
			cout << endl;
			cout << endl;
			thankyou();
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '7');
	return 0;
}

// Function To write the account data to .dat file
void write_acc()
{
	Account ac;//creating ac object class//
	ofstream x;
	x.open("info.dat", ios::binary | ios::app);//opening a binary file//
	ac.create_acc();
	x.write(reinterpret_cast<char *> (&ac), sizeof(Account));//performs binary copy//
	x.close();
}


void display_sp(int n)      //function to retrive a record from file stored
{
	Account ac;
	bool flag = false;
	ifstream x;
	x.open("info.dat", ios::binary);
	if (!x)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\tFile could not be opened!! Press any Key to exit...";
		return;
	}
	
	cout << endl;
	cout << "\t\t\tACCOUNT AND BALANCE DETAILS\n";
	cout << "\t\t\t-----------------------------\n";

	while (x.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if (ac.return_id() == n)
		{
			ac.acc_info();
			flag = true;
		}
	}
	x.close();
	if (flag == false)
		cout << "n\n\t\t\tAccount number does not exist";
}//function to modify record of an account which is stored in file
void modify_acc(int n)
{
	bool found = false;
	Account ac;
	fstream x;
	x.open("info.dat", ios::binary | ios::in | ios::out);
	if (!x)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\tFile could not be open !! Press any Key...";
		return;
	}
	while (!x.eof() && found == false)
	{
		x.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if (ac.return_id() == n)
		{
			ac.acc_info();
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1)*static_cast<int>(sizeof(Account));
			x.seekp(pos, ios::cur);
			x.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\t Record Updated";
			found = true;
		}
	}
	x.close();
	if (found == false)
		cout << "\n\n\t\t\t Record Not Found ";
}//function to delete a record from file
void delete_acc(int n)
{
	Account ac;
	ifstream x;
	ofstream y;
	x.open("info.dat", ios::binary);
	if (!x)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\tFile could not be open !! Press any Key...";
		return;
	}
	y.open("Temp.dat", ios::binary);
	x.seekg(0, ios::beg);
	while (x.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if (ac.return_id() != n)
		{
			y.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
	x.close();
	y.close();
	remove("info.dat");
	rename("Temp.dat", "info.dat");
	cout << "\n\n\tRecord Deleted ..";
}// function to display account details from the stored file

void dep_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	Account ac;
	fstream x;
	x.open("info.dat", ios::binary | ios::in | ios::out);
	if (!x)
	{
		cout << "\n\n\t\t\tFile could not be open !! Press any Key...";
		return;
	}
	while (!x.eof() && found == false)
	{
		x.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if (ac.return_id() == n)
		{
			ac.acc_info();
			if (option == 1)
			{
				cout << endl;
				cout << endl;
				cout << endl;
				cout << "\t\t\tTO DEPOSITE AMOUNT ";
				cout << endl;
				cout << "\t\t\tEnter The amount to be deposited:  ";
				cin >> amt;
				ac.deposit(amt);
			}
			if (option == 2)
			{
				cout << "\t\t\tTO WITHDRAW AMOUNT ";
				cout << endl;
				cout << "\t\t\tEnter The amount to be withdraw:  ";
				cin >> amt;
				int bal = ac.return_bal() - amt;
				//Condition makes sure that there is requied minimum balance in account//
				if ((bal<50 && ac.acctype() == 'S') || (bal<80 && ac.acctype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.withdraw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			x.seekp(pos, ios::cur);//moves the file pointer to the required position//
			x.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	x.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}
void intro()//Function for Welcome Screen//
{   
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << setw(80) << "***************************************" << endl;
	cout << setw(80) << "*    Welcome To Pirate Bank, Spokane  *" << endl;
	cout << setw(80) << "*                                     *" << endl;
	cout << setw(80) << "*      Thank you for choosing us      *" << endl;
	cout << setw(80) << "*      Press Enter To Continue        *" << endl;
	cout << setw(80) << "***************************************" << endl;
	cin.get();
}

void thankyou()//Thank you function displayed at the end//
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << setw(80) << "******************************************" << endl;
	cout << setw(80) << "*        Thankyou for Banking with us    *" << endl;
	cout << setw(80) << "*  As always happy to be at your service *" << endl;
	cout << setw(80) << "*                                        *" << endl;
	cout << setw(80) << "*      Press Enter To Exit the system    *" << endl;
	cout << setw(80) << "******************************************" << endl;
}
