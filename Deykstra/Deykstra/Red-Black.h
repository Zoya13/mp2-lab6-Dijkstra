#pragma once
#include "iostream"
#include <algorithm>
using namespace std;


struct Node1
{
	int k;
	pair<int, int>data;//data.first-priority, data.second - Node1's number
	//int data;
	Node1* left;
	Node1* right;
	Node1* parent;
	int  h;
	Node1()
	{
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->k = 1;//красный
		this->h = 1;
	}
};

class RBT
{
private:
	Node1* head;
	int size;
public:
	RBT()
	{
		Node1* ph = new Node1();
		head = ph;
		ph->k = 0;
		size = 0;
	}
	Node1* Root() {
		return head;
	}
	Node1*min(Node1*T) {
		
			Node1* temp = T;
			Node1* _temp = temp;
			while ((temp != NULL)&&(temp->data.first!=-1))
			{
				_temp = temp;//запоминаем родител€ текущего элемента=>искомый элемент
				temp = temp->left;
			}
			return _temp;
		
	}
	int High(Node1* A)
	{
		if ((A->left != NULL) && (A->left->data.first != -1))
			High(A->left);
		if ((A->right != NULL) && (A->right->data.first != -1))
			High(A->right);
		A->h = max(A->left->h, A->right->h) + 1;
		return A->h;

	}
	void Turn_Little_L(Node1*a)
	{
		Node1* t;
		t = a->right;
		a->right = t->left;
		if (a->right != NULL)
			a->right->parent = a;
		t->left = a;
		t->parent = a->parent;
		a->parent = t;
		if (t->parent != NULL)
		{
			if (t->parent->left == a)//левый ребенок
				t->parent->left = t;
			else//правый ребенок
				t->parent->right = t;
		}
		else head = t;
	}
	void Turn_Little_R(Node1*a)
	{
		Node1* t;
		t = a->left;
		a->left = t->right;
		if (a->left != NULL)
			a->left->parent = a;
		t->right = a;
		t->parent = a->parent;
		a->parent = t;
		if (t->parent != NULL) {
			if (t->parent->left == a)//левый ребенок
				t->parent->left = t;
			else//правый ребенок
				t->parent->right = t;
		}
		else head = t;
	}
	void case_3(Node1* N)
	{
		Node1* P;
		Node1* G;
		Node1* U;

		P = N->parent;
		if (P != NULL)
		{
			G = P->parent;
			if (G != NULL)
			{

				if (G->left != P)
					U = G->left;
				else
					U = G->right;
				if ((P->k == 1) && (U->k == 1) && (G->k == 0))
				{
					P->k = 0;
					U->k = 0;
					G->k = 1;
					if (G == head)
						G->k = 0;
					case_3(G);
					case_4_L(G);
					case_4_R(G);
					case_5_L(G);
					case_5_R(G);
				}
			}
		}
	}
	void case_4_L(Node1* N)
	{
		Node1* P;
		Node1* G;
		Node1* U;

		P = N->parent;
		if (P != NULL)
		{
			G = P->parent;
			if (G != NULL)
			{
				U = G->right;
				if ((P->k == 1) && (U->k == 0) && (G->k == 0) && (G->left == P) && (P->right == N))
				{
					Turn_Little_L(P);
					case_5_L(P);
				}
			}
		}
	}
	void case_4_R(Node1* N)
	{
		Node1* P;
		Node1* G;
		Node1* U;
		P = N->parent;
		if (P != NULL)
		{
			G = P->parent;
			if (G != NULL)
			{
				U = G->left;
				if ((P->k == 1) && (U->k == 0) && (G->k == 0) && (G->right == P) && (P->left == N))
				{
					Turn_Little_R(P);
					case_5_R(P);
				}
			}
		}
	}
	void case_5_L(Node1* N)
	{
		Node1* P;
		Node1* G;
		Node1* U;
		P = N->parent;
		if (P != NULL)
		{
			G = P->parent;
			if (G != NULL)
			{
				U = G->right;
				if ((P->k == 1) && (U->k == 0) && (G->k == 0) && (G->left == P) && (P->left == N))
				{
					Turn_Little_R(G);
					P->k = 0;
					G->k = 1;
				}

			}
		}
	}
	void case_5_R(Node1* N)
	{
		Node1* P;
		Node1* G;
		Node1* U;
		P = N->parent;
		if (P != NULL)
		{
			G = P->parent;
			if (G != NULL)
			{
				U = G->left;
				if ((P->k == 1) && (U->k == 0) && (G->k == 0) && (G->right == P) && (P->right == N))
				{
					Turn_Little_L(G);
					P->k = 0;
					G->k = 1;
				}
			}
		}
	}
	void Insert(int priority,int number)//void Insert(int a)
	{
		Node1* temp = head;
		Node1* _temp = head;
		Node1*A = new Node1();
		A->data.first = priority;
		A->data.second = number;
		if (size == 0)//case_1
		{
			A->k = 0;//черный
			head = A;
			Node1*A1 = new Node1();
			Node1*A2 = new Node1();
			A->left = A1; A->right = A2;
			A1->k = 0; A2->k = 0;//черные
			A1->data.first = -1; A2->data.first = -1;
			A1->parent = A; A2->parent = A;
		}
		else
		{
			while ((temp != NULL) && (temp->data.first != -1))
			{
				_temp = temp;//запоминаем родител€ текущего элемента=>искомый элемент, т.е. родитель ј
				if (priority < temp->data.first)
					temp = temp->left;
				else temp = temp->right;
			}
			A->parent = _temp;
			if (priority < _temp->data.first)
				_temp->left = A;

			if (priority > _temp->data.first)
				_temp->right = A;
			Node1*A1 = new Node1();
			Node1*A2 = new Node1();
			A->left = A1; A->right = A2;
			A1->k = 0; A2->k = 0;//черные
			A1->data.first = -1; A2->data.first = -1;
			A1->parent = A; A2->parent = A;
			case_3(A);
			case_4_L(A);
			case_4_R(A);
			case_5_L(A);
			case_5_R(A);
		}
		size++;
	}
	Node1* Search(int a)
	{
		Node1* temp = head;
		Node1* answer = NULL;
		while ((temp != NULL))
		{
			if (a == temp->data.first)
			{
				answer = temp;
				break;
			}
			if (a < temp->data.first)
				temp = temp->left;
			if (a > temp->data.first)
				temp = temp->right;
		}
		return answer;
	}
	void Delete(int a) {
		Node1* elem = Search(a);
		if (elem != NULL) {
			deleteNode1(elem);
			size--;
		}
	}
	void deleteFixup(Node1 *x) {
		while (x != head && x->k == 0) {
			if (x == x->parent->left) {
				Node1 *w = x->parent->right;
				if (w->k == 1) {
					w->k =0;
					x->parent->k = 1;
					Turn_Little_L(x->parent);
					w = x->parent->right;
				}
				if (w->left->k == 0 && w->right->k == 0) {
					w->k = 1;
					x = x->parent;
				}
				else {
					if (w->right->k == 0) {
						w->left->k = 0;
						w->k= 1;
						Turn_Little_R(w);
						w = x->parent->right;
					}
					w->k = x->parent->k;
					x->parent->k = 0;
					w->right->k = 0;
					Turn_Little_L(x->parent);
					x = head;
				}
			}
			else {
				Node1 *w = x->parent->left;
				if (w->k == 1) {
					w->k = 0;
					x->parent->k = 1;
					Turn_Little_R(x->parent);
					w = x->parent->left;
				}
				if (/*w->right!=NULL && w->left!=NULL &&*/ w->right->k == 0 && w->left->k == 0) {
					w->k = 1;
					x = x->parent;
				}
				else {
					if (w->left->k == 0) {
						w->right->k = 0;
						w->k = 1;
						Turn_Little_L(w);
						w = x->parent->left;
					}
					w->k = x->parent->k;
					x->parent->k = 0;
					w->left->k = 0;
					Turn_Little_R(x->parent);
					x = head;
				}
			}
		}
		x->k = 0;
	}
	void deleteNode1(Node1 *z) {
		Node1 *x, *y;

		if (!z || z->data.first == -1) return;


		if (z->left->data.first == -1 || z->right->data.first == -1) {
			/* y has a NIL Node1 as a child */
			y = z;
		}
		else {
			/* find tree successor with a NIL Node1 as a child */
			y = z->right;
			while (y->left->data.first != -1) y = y->left;
		}

		/* x is y's only child */
		if (y->left->data.first != -1)
			x = y->left;
		else
			x = y->right;

		/* remove y from the parent chain */
		x->parent = y->parent;
		if (y->parent)
			if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
		else
			head = x;

		if (y != z) { 
			z->data.first = y->data.first;
			z->data.second = y->data.second;
		}


		if (y->k == 0)
			deleteFixup(x);

		free(y);
		if (head->data.first == -1)
			head = NULL;
	}
};