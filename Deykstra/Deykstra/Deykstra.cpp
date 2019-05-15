// Deykstra.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Algorithm.h"
#include"AVL.h"
#include <iostream>
#include <cstdlib> // для функций rand() и srand()

#include<string>
int main()
{
	srand(15);
	/*Algorithm A;
	A.RB();
	A.Way_Cost(1);
	*/
	int k = 1, l = 1;
	do {
		cout << '\n' << "Choose one of the items:" << '\n';
		string d[3] = { "1. To generate a graph","2. To input a graph","3. Exit" };
		for (int i = 0; i < 3; i++)
			cout << d[i] << '\n';
		cout << endl << "Input a menu number:";
		cin >> k;
		if ((k != 1) && (k != 2)) break;
		else {
			int number, start, _node = -1;
			cout << endl << "Input a number of nodes: ";
			cin >> number;
			cout << endl << "Input a start node: ";
			cin >> start;
			Algorithm A;
			if (k == 1)
				A.Generate(number, start);
			else
				A.Form(number, start);
			if (A.Check(k)) {
				do {
					cout << '\n' << "Choose one of the items:" << '\n';
					string c[2] = { "1. A new node","2. A new algorithm" };
					for (int i = 0; i < 2; i++)
						cout << c[i] << '\n';
					cout << "Input a menu number:";
					cin >> l;
					if (l != 1) break;
					else {
						_node = -1;
						while ((_node < 0) || (_node >= number)) {
							cout << endl << "Input a node (0<=node<number): ";
							cin >> _node;
						}
						A.Print();
						A.AVL();
						A.Way_Cost(_node);
						A.RB();
						A.Way_Cost(_node);
						A.HEAP();
						A.Way_Cost(_node);


					}
				} while (l == 1);
			}
			else
				cout << endl << "It isn't a simply connected graph";
		}
		/*while (flag) {
		Algorithm A(20, 2);
		if (A.Check()) {
		A.Print();
		A.AVL();
		A.Way_Cost(5);
		A.RB();
		A.Way_Cost(5);
		A.HEAP();
		A.Way_Cost(5);
		}
		cout << endl<<"Input k: ";
		cin >> k;
		cout<< endl;
		}
		*/
	} while ((k == 1) || (k == 2));
	system("pause");
}