/**********************************************************/
/*	Dawei Wang 

use the Adapter Design Pattern
There some functions in aacount like subbalance().
With no judgement, it can be a negative value, 
but the bankaccount make some constrains and make it can be used by main()
*/
/**********************************************************/
#pragma once
#include "Account.h"
#include<time.h>
class BankAccount :
	public Account
{
public:
	BankAccount();
	~BankAccount();
	void deposit_money(double );	//deposit money, recall account function.  write "deposit" action into .txt

	void withdraw_money(double);	//write "withdram" action into .txt
	
	void print_balance() const;		//recall father class function

	void printbankhistory();		//print bank history
};

