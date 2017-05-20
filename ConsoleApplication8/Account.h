//Simple Banking System Program created using Binary I/O//
//Submitted by Sabin Sapkota//
//Header File//

#ifndef Account_H
#define Account_H

class Account
{
private:
	int ID;
	char name[100];
	int dep;
	char type;
public:
	void create_acc();    //function to create a new account
	void acc_info() const;    //function to show account details
	void modify();    //function to modify account details
	void deposit(int);    //function to accept deposit amount
	void withdraw(int);    //function to subtract withdrawal amount
	void report() const;    //function to show data in tabular format
	int return_id() const;    //For returning account number
	int return_bal() const;    //For returning balance amount
	char acctype() const;    //For returning type of account
};
#endif
