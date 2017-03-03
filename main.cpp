/* written by Dawei, Wang
	netId:dw514
	date: 11/20/2016
*/
/**********************************

An Account Management System

**********************************/

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<iomanip>
#include<cmath>

#include"StockAccount.h"
#include"BankAccount.h"
#include"engine.h"
#include "mex.h" 

#pragma comment( lib, "libmx.lib" )     
#pragma comment( lib, "libmex.lib" )     
#pragma comment( lib, "libeng.lib" )
#pragma comment( lib, "libmat.lib" )
using namespace std;

void read_text(unordered_map<string, double> &);		//read the data from "result1.txt" or other .txt
int graph();											//graph in matlab

void main() {
	int choice = 1, choice_1 = 1, choice_2 = 1;

	unordered_map<string, double> mymap;
	BankAccount bankaccount;
	StockAccount stockaccout;

	cout << "Welcome to the Account Management System" << endl;
	
	read_text(mymap);		
	stockaccout.updateprice(mymap);	//update the stock price	
	
	while (choice != 3) {
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account\n2. Bank Account\n3. Exit\n" << endl;
		cin >> choice;

		choice_1 = 1;//initial it again
		choice_2 = 1;

		switch (choice)
		{
		case 1:		//stockaccount
		{
			cout << "Stock Portfolio Account" << endl;
			while (choice_1 != 7) {
				cout << "Please select an option" << endl;
				cout << "1. Display the price for a stock symbol\n2. Display the current portfolio\n3. Buy shares\n";
				cout << "4. Sell shares\n5. View a graph for the portfolio value\n6. View transaction history\n7. Return to previous menu\n" << endl;
				cin >> choice_1;
				switch (choice_1)
				{
				case 1: {					//Display the price for a stock symbol
					string s;
					cout << "Please enter the stock symbol: " << endl;
					cin >> s;
					//judge whether the stock exist
					if (mymap[s] == NULL)
					{
						cout << "the stock is not available" << endl;
						break;
					}
					cout << left << setw(16) << "Company Symbol" << "Price per share" << endl;
					cout << setw(16) << s << mymap[s] << endl;
					break;
				}
				case 2: {					//Display the cash balance
					cout << "Cash balance = $" << stockaccout.balanceof() << endl;
					cout << left << setw(16) << "Company-Symbol" << setw(8) << "Number" << setw(17) << "Price-per-share" << "Total value" << endl;
					stockaccout.print();
					cout << "Total portfolio value: $" << stockaccout.calculate_portfolio_value() + stockaccout.balanceof()<< endl;
					break;
				}
				case 3: {					//Buy shares
					cout << "Please enter the stock symbol you wish to purchase: ";
					string s;
					cin >> s;
					if (mymap[s] == NULL) 
					{
						cout << "the stock is not available" << endl;
						break;
					}
					cout << "Please enter the number of shares: ";
					int share;
					cin >> share;
					cout << "Please enter the maximum amount you are willing to pay per share: ";
					double priceYouWant;
					cin >> priceYouWant;

					if (priceYouWant >= mymap[s]) {				//willing price need to be larger than the current price

						if (stockaccout.balanceof() >= (mymap[s]*share)) {
							stockaccout.buyshares(s, share, mymap[s]);
							//bankaccount.withdraw_money(share*mymap[s]); //subscribe twice!!!
							cout << "You have purchased " << share << " shares of " << s << " at $" << mymap[s] << " each for a total of $" << share*mymap[s] << endl;
						}
						else {
							cout << "Do not have enough money!" << endl;
						}
					}
					else {
						cout << "Sorry! The price you wish is lower than the transaction value!" << endl;
					}
					break;
				}
				case 4: {		//sell shares
					cout << "Please enter the stock symbol you wish to sell: ";
					string s;
					cin >> s;
					if (mymap[s] == NULL)
					{
						cout << "the stock is not available" << endl;
						break;
					}
					cout << "Please enter the number of shares: ";
					int share;
					cin >> share;
					stockaccout.sellshares(s, share, mymap[s]);
					break;
				}
				case 5: {		//view a graph
					graph();	//recall the graph function
					break;
				}
				case 6:			//view transaction history
					stockaccout.printstockhistory();
					break;
				default:
					break;
				}
			}
			break;
		}
		case 2:			//bankaccount
		{
			cout << "Bank Account" << endl;
			while (choice_2 != 5) {
				cout << "Please select an option" << endl;
				cout << "1. View account balance\n2. Deposit money\n3. Withdraw money\n4. Print out history\n5. Return to privious menu\n" << endl;
				cin >> choice_2;
				switch (choice_2)
				{
				case 1: {
					bankaccount.print_balance();
					break;
				}
				case 2: {
					cout << "Please select the amount you wish to deposit: $";
					double amount;
					cin >> amount;
					cout << "\n";
					bankaccount.deposit_money(amount);
					break;
				}
				case 3: {
					cout << "Please select the amount you wish to withdraw: $";
					double amount;
					cin >> amount;
					cout << "\n";
					bankaccount.withdraw_money(amount);
					break; 
				}
				case 4:
					bankaccount.printbankhistory();
					break;
				default:
					break;
				}
			}
			break;
		}
		default:
			break;
		}
	
	
	}
}

void read_text(unordered_map<string, double> & mymap)
{	
	//choose the value from .txt randomly
	srand(time(NULL));
	int num = rand() % 2;	
	ifstream file1;
	if (num == 1) {
		file1.open("Result_1.txt");
		cout << "open Result_1.txt" << endl;
	}
	else {
		file1.open("Result_2.txt");
		cout << "open Result_2.txt" << endl;
	}
	string s[147];	//49 X 3 = 147 elements
	//or use while(file1>>s[i])
	for (int i = 0; i < 147; i++) {
		file1 >> s[i];	//read by words
						//getline(file1,s[i]);	//read by lines		
		//cout << s[i] << endl;  //display
	}
	//change the string to double and save it in unordered_map
	for (int i = 0; i < 147; i += 3) {
		mymap[s[i]] = atof(s[i + 1].c_str());
	}
	file1.close();
}

int graph() {
	ifstream file;
	file.open("portfolio_history.txt");
	string s;
	vector<double> vecbalance,vecportfolio;

	while (file >> s) {
		if (s == "balance") {
			file >> s;
			vecbalance.push_back(atof(s.c_str()));
		}
		if (s == "total_portfolio_value") {
			file >> s;
			vecportfolio.push_back(atof(s.c_str()));
		}
	}
	int size = vecbalance.size();
	
	if (size == 0) {
		cout << "Sorry! This is your first transaction. No value record, you must restart the project at least once." << endl;
		return 0;
	}

	Engine *ep;
	ep = engOpen(NULL);
/*	if (ep == NULL)
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	} */

	double *pBalance = new double[size];
	double *pPortfolio = new double[size];
	double *pTime = new double[size];

	//int *pLength = &size;

	//initial the array
	for (int i = 0; i < size; i++) {
		pBalance[i] = vecbalance[i];
		pPortfolio[i] = vecportfolio[i];
		pTime[i] = i;
	}
	mxArray *BAL = mxCreateDoubleMatrix(size, 1, mxREAL);
	memcpy((void *)mxGetPr(BAL), (void *)pBalance, sizeof(double) * size);
	engPutVariable(ep, "BAL", BAL);

	mxArray *POR = mxCreateDoubleMatrix(size, 1, mxREAL);
	memcpy((void *)mxGetPr(POR), (void *)pPortfolio, sizeof(double) * size);
	engPutVariable(ep, "POR", POR);

	mxArray *TIME = mxCreateDoubleMatrix(size, 1, mxREAL);
	memcpy((void *)mxGetPr(TIME), (void *)pTime, sizeof(double) * size);
	engPutVariable(ep, "TIME", TIME);

	/*
	mxArray *LENGTH = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)mxGetPr(LENGTH), (void *)pLength, sizeof(double) * 1);
	engPutVariable(ep, "LENGTH", LENGTH);
	*/

	engEvalString(ep, "figure('units','normalized','outerposition',[0 0 1 1]),");
	//engEvalString(ep, "plot(TIME,BAL,'r',TIME,POR,'b'),grid minor,title('Our Matlab Plot'),");
	engEvalString(ep, "plot(TIME,BAL,'r',TIME,POR,'b'),grid minor,title('Our Matlab Plot'),legend('Balance','Total Portfolio'),ylabel('Dollar'),xlabel('Each transaction'),");

	delete pBalance, pPortfolio, pTime;
	/****** plot as individual values ********/
/*	mxArray *dBalance = mxCreateDoubleMatrix(1, 1, mxREAL);
	mxArray *dPortfolio = mxCreateDoubleMatrix(1, 1, mxREAL);
	mxArray *dTime = mxCreateDoubleMatrix(1, 1, mxREAL);

	double *pBalance = mxGetPr(dBalance);
	double *pPortfolio = mxGetPr(dPortfolio);
	double *pTime = mxGetPr(dTime);

	for (int ii = 0; ii < size; ii++) {
		*pBalance = vecbalance[ii];
		*pPortfolio = vecportfolio[ii];
		*pTime = vectime[ii];

		engPutVariable(ep, "dBalance", dBalance);
		engPutVariable(ep, "dPortfolio", dPortfolio);
		engPutVariable(ep, "dTime", dTime);

		engEvalString(ep, "scatter(dTime,dBalance,200,'r','filled'),set(gca,'Price',[0 100000],'time',[0 100]),hold on,");
		engEvalString(ep, "scatter(dTime,dPortfolio,200,'b','filled'),hold off");
	}
*/
/*	const int arraysize = 1000;
	const double degTorad = .0174;	
	double SinArray[arraysize];
	double CosArray[arraysize];
	double Degrees[arraysize];
	for (int iii = 0; iii < arraysize; iii++) 
	{
		Degrees[iii] = iii;
		SinArray[iii] = sin(iii*degTorad);
		CosArray[iii] = cos(iii*degTorad);
	}
	cout << "Example 1 or 2?";	char Sim = '1';	cin >> Sim;
	if (Sim == '1') {
		mxArray *SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
		memcpy((void *)mxGetPr(SIN), (void *)SinArray, sizeof(double) * arraysize);
		engPutVariable(ep, "SinGraph", SIN);

		mxArray *COS = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
		memcpy((void *)mxGetPr(COS), (void *)CosArray, sizeof(double) * arraysize);
		engPutVariable(ep, "CosGraph", COS);

		mxArray *DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
		memcpy((void *)mxGetPr(DEG), (void *)Degrees, sizeof(double) * arraysize);
		engPutVariable(ep, "Degrees", DEG);

		engEvalString(ep, "figure('units','normalized','outerposition',[0 0 1 1]),");
		engEvalString(ep, "plot(Degrees,SinGraph,'r',Degrees,CosGraph,'b'),grid minor,title('Our Matlab Plot'),");
		system("pause");
	}
	*/
	file.close();
	return 1;
}