/**********************************************************/
/*	 Dawei Wang 

	use the Decorator Design Pattern. 
	inherit from account and produce an object of the linkedlist
	assemble both fucntions from account and linkedlist together.
	It reduce the times of inheritance, as the it can also be realized by 
	class Account:public Linkedlist
	class StockAccount:public Account
	
	Also use the Adapter Design Pattern
	There some functions in linkedlist like addshares() and printlist().
	These functions cannot be directly used by main function, 
	so add some judgements and functions to make the class StockAccount be a wrapper.
*/
/**********************************************************/
#pragma once
#include "Account.h"
#include"Node.h"
#include<time.h>
#include<iomanip>
#include<unordered_map>
class StockAccount :
	public Account
{
public:
	StockAccount();
	~StockAccount();
	
	void sortlist(); //recall list.sortlist

	void print() const;	//recall list.printlist
	double calculate_portfolio_value();		//calculate the all portfolio value without the balance
	void sellshares(string ,int ,double);	//recall addshares
	void buyshares(string, int, double);	// name, shares, price
	void printstockhistory();

	void updateprice(unordered_map<string, double> map); //when change the result.txt file. The price of the stock need to be changed
private:
	LinkedList list;
};