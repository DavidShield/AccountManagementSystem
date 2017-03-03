/* Dawei Wang */
#include "Node.h"
#include <iomanip>
using std::setw;
using std::left;
using std::endl;
LinkedList::LinkedList()
	:myHead(0), myTail(0), mySize(0), mydate("01/01/2016")
{
	//read the history portfolio values
	ifstream file("portfolio.txt");
	string name;
	int shares;
	double price;
	while (file >> name) {
		file >> shares;
		file >> price;
		Node *node = new Node(name, shares, price);
		addToStart(node);
	}
	file.close();
	//sort, do not really need, waste of time
	//sortlist();
}

LinkedList::~LinkedList()
{
	//store the history portfolio values
	ofstream file("portfolio.txt");
	sortlist();			//sortlist
	Node *temp = myHead;
	while (temp != NULL) {
		file << temp->stockname << ' ' << temp->shares << ' ' << temp->price << endl;
		temp = temp->next;
	}
	file.close();

	//destroy all nodes
	if (size() != 0) {
		cout << "Destroying nodes ...\n";
		Node *current = myHead;
		Node *tempPtr;
		while (current != 0) {
			tempPtr = current;
			cout << tempPtr->stockname << '\n';
			current = current->next;
			delete tempPtr;
		}
	}
	cout << "All nodes destroyed\n\n";
}

int LinkedList::size() const
{
	return mySize;
}

void LinkedList::addToStart(Node *value)
{
	Node *newPtr = new Node(*value);
	if (size() == 0)
		myHead = myTail = newPtr;
	else {
		newPtr->next = myHead;
		myHead->last = newPtr;
		myHead = newPtr;
	}
	mySize++;
	sortlist();
}
void LinkedList::addToEnd(Node *value)
{
	Node *newPtr = new Node(*value);
	if (size() == 0)
		myHead = myTail = newPtr;
	else {
		myTail->next = newPtr;
		newPtr->last = myTail;
		myTail = newPtr;
	}
	mySize++;
}
void LinkedList::printList() const
{
	if (size() == 0) {
		cout << "The list is empty\n";
		return;
	}
	Node *current = myHead;
	//cout << "\nList\n" << "StockName   StockShares" << endl;
	while (current != 0) {
		cout << setw(16) << left << current->stockname << setw(8)<<current->shares <<'$'<<setw(16)<<current->price<<'$'<<current->shares*current->price << endl;
		current = current->next;
	}
}
bool LinkedList::removeFromStart()
{
	if (size() == 0)
		return false;
	else {
		Node *tempPtr = myHead;
		if (myHead == myTail) {
			myHead = myTail = 0;
		}
		else {
			myHead = myHead->next;
			myHead -> last = 0; //myHead->last =NULL;
			delete tempPtr;
			mySize--;
			return true;
		}
	}
}
bool LinkedList::removeFromEnd()
{
	if (size() == 0)
		return false;
	else {
		Node *tempPtr = myTail;
		if (myHead == myTail)
			myHead = myTail = 0;
		else {
			Node *current = myHead;
			while (current->next != myTail) {
				current = current->next;
			}
			myTail = current;
			current->next = 0;
		}
		delete tempPtr;
		mySize--;
		return true;
	}
}
void LinkedList::removeNodeFromList(double num)
{	

	if (size() == 0) {
		cout << "error: no item in the list!" << endl;
	}
	else {
		Node *temPtr = myHead;
		//find item number
		while ((temPtr->shares != num) && (temPtr->next != NULL)) {
			temPtr = temPtr->next;
		}
		//judge whether there exist the number
		if ((temPtr->shares != num) && (temPtr->next == NULL)) {
			cout << "error: no this item number" << endl;
		}
		//if temPtr is the head, there will be no node before temPtr
		else {
			if (temPtr == myHead) {
				myHead = temPtr->next;
				//set last as null
				myHead->last = 0;
				delete temPtr;
				mySize--;
			}
			else if (temPtr == myTail) {
				myHead = temPtr->last;
				myHead->next = 0;
				delete temPtr;
				mySize--;
			}
			//find the second last element of the number
			else {
				Node *current =temPtr->last;
				current->next = temPtr->next;
				delete temPtr;
				mySize--;
			}
		}
	}
}
void LinkedList::removeNodeFromList(string str)
{
	if (size() == 0) {
		cout << "error: no item in the list!" << endl;
	}
	else {
		Node *temPtr = myHead;
		//find item number
		while ((temPtr->stockname != str) && (temPtr->next != NULL)) {
			temPtr = temPtr->next;
		}
		//judge whether there exist the number
		if ((temPtr->stockname != str) && (temPtr->next == NULL)) {
			cout << "error: no this item number" << endl;
		}
		//if temPtr is the head, there will be no node before temPtr
		else {
			if (temPtr == myHead) {
				myHead = temPtr->next;
				//set last as null
				myHead->last = 0;
				delete temPtr;
				mySize--;
			}
			else if (temPtr == myTail) {
				myHead = temPtr->last;
				myHead->next = 0;
				delete temPtr;
				mySize--;
			}
			//find the second last element of the number
			else {
				Node *current = temPtr->last;
				current->next = temPtr->next;
				delete temPtr;
				mySize--;
			}
		}
	}
}
double LinkedList::cal_total_portfolio_value() 
{
	sortlist();
	double value = 0;
	Node *temp = myHead;
	if (temp != NULL) {
		while (temp->next != NULL) {
			value += temp->price*temp->shares;
			temp = temp->next;
		}
		/*if temp is the only node, add its value*/
		value += temp->price*temp->shares;
		return value;
	}
	return 0;
}
int LinkedList::stock_shares(string s)
{
	Node *temp = myHead;
	if (temp == NULL)
		return 0;
	else {
		do {
			if (temp->stockname == s) {
				return temp->shares;
			}
			temp = temp->next;
		} while (temp != NULL);
		return 0;
	}
}
void LinkedList::addshares(string s, int shares)
{	
	Node *temp = myHead;
	while (temp != NULL) {
		if (temp->stockname == s) {
			temp->shares += shares;
			break;
		}
		temp = temp->next;
	}
	sortlist();
}
void LinkedList::subshares(string s , int shares)
{
	Node *temp = myHead;
	while (temp != NULL) {
		if (temp->stockname == s) {
			temp->shares -= shares;
			break;
		}
		temp = temp->next;
	}
	/* add some code to delete the stock whose shares is 0 */
	sortlist();
	
	//if shares equal to 0, delete it
	Node *temp1 = myHead;
	while (temp1 != NULL) {
		if (temp1->stockname == s) {
			if (temp1->shares == 0) {
				removeFromEnd();
				break;		//if not break the temp1->next will go to an unknown area!!!!
			}
		}
		temp1 = temp1->next;
	}
}
void LinkedList::update(unordered_map<string, double> map)
{
	Node *temp = myHead;
	while (temp != NULL) {
		temp->price = map[temp->stockname];		//stock price equal to new price
		temp = temp->next;
	}
	sortlist();
}
//sort function
void LinkedList::sortlist() {

	Node *temp1 = myHead;
	if (temp1 != NULL) {
		Node *temp2 = myHead->next;
		if (temp2 != NULL) {
			for (int i = 0; i < mySize - 1; i++) {

				for (int j = 0; j < mySize - 1 - i; j++) {
						if (temp2 != NULL) {
							if ((temp1->shares*temp1->price) < (temp2->shares*temp2->price)) 
							{
								if (temp1->last == 0) {
									//if temp1 is the head
									Node *current = temp2->next;
									temp1->next = temp2->next;
									temp1->last = temp2;
									temp2->next = temp1;
									temp2->last = 0;
									if (current != NULL) {
										current->last = temp1;
									}
									myHead = temp2;
								}
								else if (temp2->next == 0)
								{//if temp2 is the tail
									Node *current = temp1->last;
									temp2->last = temp1->last;
									temp1->next = 0;
									temp1->last = temp2;
									temp2->next = temp1;
									current->next = temp2;
									myTail = temp1;
								}
								else {
									//if temp1 is not the head and the tail
									Node *inter = temp1;
									Node *current1 = temp1->last;
									Node *current2 = temp2->next;
									temp1->next = temp2->next;
									temp1->last = temp2;
									temp2->next = temp1;
									temp2->last = current1;
									current1->next = temp2;
									current2->last = temp1;
								}	
								//change the temp1 and temp2, temp1 has become the position as temp1->next, so only temp2 need change to temp2->next
								temp2 = temp1->next;
							}
							else 
							{	//nothing changed so move to the next node
								temp1 = temp1->next;
								temp2 = temp2->next;
							}
					}
				}
			}
		}
	}
}
Node::~Node()
{
}
