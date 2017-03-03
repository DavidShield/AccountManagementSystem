/* Dawei Wang */
#pragma warning(disable : 4996)
#include "BankAccount.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


BankAccount::BankAccount()
{

}

BankAccount::~BankAccount()
{

}

void BankAccount::deposit_money(double deposit)
{
	if (deposit <= 0) {
		cout << "Fail, you should deposit more than 0 dollars" << endl;
	}
	else {
		addbalance(deposit);
		//balance = balance + deposit;
		cout << "Success ";
		print_balance();
	}

	ofstream fffile("bank_transaction_history.txt", ofstream::app | ofstream::out);
	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);

	fffile << left << setw(12) << "Deposit" << '$' << setw(11) << deposit << setw(2) << setfill('0') << 1+timeinfo->tm_mon << '/' << setw(2) << setfill('0') << timeinfo->tm_mday << '/' << setw(8) << 1900+timeinfo->tm_year << '$' << balanceof() << endl;
	//fffile << "total_portfolio_value " << calculate_portfolio_value() + balanceof() << endl;

	fffile.close();
}

void BankAccount::withdraw_money(double withdraw)
{
	if (withdraw <= 0) {
		cout << "Fail, you should withdraw more than 0 dollars" << endl;
	}
	else if (balanceof() < withdraw) {
		cout << "Fail, not enough money in the account" << endl;
	}
	else {
		subbalance(withdraw);
		cout << "Success " ;
		print_balance();
	}

	ofstream fffile("bank_transaction_history.txt", ofstream::app | ofstream::out);
	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);

	fffile << left << setw(12) << "Withdrawal" << '$' << setw(11) << withdraw << setw(2) << setfill('0') << timeinfo->tm_mon << '/' << setw(2) << setfill('0') << timeinfo->tm_mday << '/' << setw(8) << timeinfo->tm_year << '$' << balanceof() << endl;
	//fffile << "total_portfolio_value " << calculate_portfolio_value() + balanceof() << endl;

	fffile.close();
}



void BankAccount::print_balance() const
{	
	cout << "The balance is: " << balanceof() << endl;
}

void BankAccount::printbankhistory()
{	
	ifstream file("bank_transaction_history.txt");
	string s;
	cout << left << setw(12) << "Event" << setw(12) << "Amount" << setw(13) << "Date" << "Balance" << endl;
	while (getline(file, s)) {
		cout << s << endl;
	}
	file.close();
}