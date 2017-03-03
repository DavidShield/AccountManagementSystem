/* Dawei Wang */
#include "Account.h"

double Account::balance = 10000;

Account::Account()
{
	ifstream file("data.txt");
	string ss;
	while (file >> ss) {
		if (ss == "balance") {	//recognize the balance and read the next value;
			file >> ss;
			balance = atof(ss.c_str());	//change string to double
			break;
		}

		if (ss == "time") {
			file >> time_accurate;
			//cout << "the last operation time is: " << time << endl;
		}
		//add some code to read the portfolio data
	}
	file.close();
}


Account::~Account()
{	

}

void Account::addbalance(double change)
{	
	balance += change;
}

void Account::subbalance(double change)
{	
	balance -= change;
}

double Account::balanceof() const
{
	return balance;
}
