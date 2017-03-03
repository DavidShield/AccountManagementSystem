/* Dawei Wang */
#pragma warning(disable : 4996)
#include "StockAccount.h"

StockAccount::StockAccount()
{

}

StockAccount::~StockAccount()
{	
	//store date and time
	ofstream ffile("data.txt");  
	ffile << "balance " << balanceof() << endl;
	ffile << "total_portfolio_value " << calculate_portfolio_value() + balanceof() << endl;
	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);
//	ffile << asctime(timeinfo);
	ffile.close();

	ofstream file("portfolio_history.txt", std::ofstream::app);
	file << "balance " << balanceof() << endl;
	file << "total_portfolio_value " << calculate_portfolio_value() + balanceof()<< endl;
	file << "time " <<setw(2)<< setfill('0') << timeinfo->tm_hour << ':' <<setw(2)<< setfill('0') << timeinfo->tm_min << ':' <<setw(2)<< setfill('0') << timeinfo->tm_sec << endl;
	file << "date " << 1+timeinfo->tm_mon << '/' << timeinfo->tm_mday << '/' << 1900+timeinfo->tm_year << endl;
	file.close();
}

void StockAccount::sortlist()
{	
	list.sortlist();
}

void StockAccount::print() const
{
	list.printList();
}

double StockAccount::calculate_portfolio_value()
{
	return list.cal_total_portfolio_value();
}

void StockAccount::sellshares(string s,int shares,double price)
{	
	ofstream fffile("stock_transaction_history.txt", ofstream::app | ofstream::out);

	if (list.stock_shares(s) >= shares) {
		list.subshares(s,shares);
		addbalance(shares*price);
		cout << "success!" << endl;
	}
	else	cout << "Do not own enough stocks of " << s << endl;

	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);
	fffile << left << setw(8) << "sell" << setw(13) << s << setw(10) << shares << '$' << setw(14) << price << '$' << setw(14) << shares*price <<setw(2)<< setfill('0') << timeinfo->tm_hour << ':' <<setw(2)<< setfill('0') << timeinfo->tm_min << ':' <<setw(2)<< setfill('0') << timeinfo->tm_sec << endl;
	//fffile << "total_portfolio_value " << calculate_portfolio_value() + balanceof() << endl;

	fffile.close();
}

void StockAccount::buyshares(string s, int shares, double price)
{	
	ofstream fffile("stock_transaction_history.txt",ofstream::app|ofstream::out);

	if (list.stock_shares(s) == 0) {
		Node *node = new Node(s, shares, price);
		list.addToStart(node);
		subbalance(shares*price);
	}
	else {
		list.addshares(s, shares);
		subbalance(shares*price);
	}
	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);
	fffile << left << setw(8) << "buy" << setw(13) << s << setw(10) << shares << '$' << setw(14) << price << '$' << setw(14) << shares*price << setw(2)<< setfill('0') << timeinfo->tm_hour << ':' <<setw(2)<< setfill('0') << timeinfo->tm_min << ':' <<setw(2)<< setfill('0') << timeinfo->tm_sec << endl;
	//fffile << "total_portfolio_value " << calculate_portfolio_value() + balanceof() << endl;

	fffile.close();
}

void StockAccount::printstockhistory()
{
	ifstream file("stock_transaction_history.txt");
	string s;
	cout << left << setw(8) << "Event" << setw(13) << "CompSymbol" << setw(10) << "Number" << setw(15) << "PricePerShare" << setw(15) << "TotalValue" << "Time" << endl;
	while (getline(file, s)) {
		cout << s << endl;
	}
	file.close();
}

void StockAccount::updateprice(unordered_map<string, double> map)
{
	list.update(map);
}
