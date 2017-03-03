/* Dawei Wang */
#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
using namespace std;

class Node
{
	friend class LinkedList;
public:
	Node(string &name, int share, double pri)
		:stockname(name), shares(share), price(pri)
	{
		this->last = NULL;
		this->next = NULL;
	}
	~Node();
private:
	int shares;
	double price;
	string stockname;

	Node *next, *last;
};
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	void sortlist();	//sort the list
	int size() const; //can be used as function: is_empty()
	
	void addToStart(Node *);
	void addToEnd(Node *);
	void printList() const;			//print		name	shares	price	shares*price
	bool removeFromStart();
	bool removeFromEnd();
	void removeNodeFromList(double);
	void removeNodeFromList(string);

	double cal_total_portfolio_value() ;	//calculate the total portfolio value
	int stock_shares(string s);				//return the shares of stock s
	void addshares(string , int);
	void subshares(string, int);
	
	void update(unordered_map<string, double> map);		//update price
private:
	Node *myHead;
	Node *myTail;
	int mySize;
	string mydate;
};