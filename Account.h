/* Dawei Wang */
#pragma once
#include<iostream>
#include"Node.h"
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

class Account
{

public:
	Account();
	~Account();
	void addbalance(double);		//add variable: balance
	void subbalance(double);
	//void print_balance() const;
	double balanceof() const;		//return the number of balance
	
private:
	static double balance;			//make it static so the two class share the same value	
	//this variables do not used
	string time_date, time_accurate;

};

