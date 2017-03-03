Account Management System
The project contains three parts: the account, list and main.

The class Account have define a static variable "balance", which connects the StockAccount and BankAccount. The contructor read the "balance" from "data.txt".

BankAccount only change the "balance", and write the transaction history in "bank_transaction_history.txt".

StockAccount change both the "balance" and "portfolio", and it will write the transaction history in "stock_transaction_history.txt". The StockAccount also needs to change the LinkedList including buy_stock, sell_stock and calculate_portfolio_value. The destructor rewrite the "balance" and "total_portfolio_value" in "data.txt". It also write the new "balance",  "total portfolio" along with "time" at the end of "portfolio_history.txt" which is used to graph in matlab.

This part use the Decorator Design Pattern. The stockaccount inherit from account and produce an object of the linkedlist. It assembles both fucntions from account and linkedlist together. In this way, it reduces the times of inheritance, as the it can also be realized by 
	class Account:public Linkedlist
	class StockAccount:public Account

It also use the Adapter Design Pattern. There some functions in linkedlist like addshares() and printlist(). These functions cannot be directly used by main function, so I add some judgements and functions to make the class StockAccount be a wrapper.

The list part is a doubly-linked list. It contains many nodes which represent the stocks including name, shares and price. The list have many functions which can change the number of nodes and change a specific node's variables, price and shares. It also can sort the list by using bubble sort according to the multiplication of price and shares. The constructor read the last portfolio data from "portfolio.txt" and add them in linkedlist. The destructor write the portfolio history in "portfolio.txt" and destroy all nodes.

The main function display the necessary words and ask user their options. According to the options, do some simple judgement and recall the functions. The graph part is also included in the main function, recall the "engine.h" and transfer data to matlab.