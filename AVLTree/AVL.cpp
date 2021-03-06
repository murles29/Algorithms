// Project4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVLTree.h"
using namespace std;

int main () {

	BinarySearchTree MyBST;

	while (true)
	{
		cout << "(1) to insert node to tree." << endl;
		cout << "(2) to search for node in tree." << endl;
		cout << "(3) to delete node in tree." << endl;
		cout << "(-999) to exit." << endl;
		cout << "Your selection: ";
		int Input;
		cin >> Input;

		cout << "=====" << endl;

		if (Input == -999) {
			break;
		}
		switch (Input) {
			case 1: {//Insert a node into the tree.
				int key;
				string value;
				cout << "Please enter a value: ";
				cin >> key;
				MyBST.BInsert (key);

				cout <<  endl;
				MyBST.printTree (MyBST.getRoot ());
				cout << endl << endl;
				cout << "=====" << endl;
				break;
			}
			case 2: {//Search for a node in the tree.
				int key;
				cout << "Please enter value to search for: ";
				cin >> key;
				Node* v = MyBST.ToSearch (key, MyBST.getRoot ());
				if (v->IsInternal ()) {
					cout << "Node found." << endl;
					cout << "=====" << endl;
				}
				else {
					cout << "Node not found." << endl;
					cout << "=====" << endl;
				}
				break;
			}
			case 3: { //Delete a node`
				int key;
				cout << "Please enter value to delete: ";
				cin >> key;
				MyBST.ToDelete(key);
				cout << endl;
				MyBST.printTree (MyBST.getRoot ());
				cout << endl << endl;
				cout << "=====" << endl;
			}
		}
	}

	return 0;
}