#pragma once
#include "iostream"
#include <algorithm>
using namespace std;

struct Node
{
	pair<int, int>data;//data.first-priority, data.second - Node1's number
	//double data;
	int h;
	Node* left;
	Node* right;
	Node* parent;
};

class AVLT
{
private:
	Node  *head;
	int size;
public:
	AVLT()
	{
		Node* ph = new Node();
		head = ph;
		head->left = NULL;
		head->right = NULL;
		head->parent = NULL;
		head->h = 0;
		size = 0;
	}
	Node* Root() {
		return head;
	}
	int D(Node*temp)
	{
		if (temp == NULL)
			return 0;
		int res;
		if ((temp->left == NULL) && (temp->right == NULL))
		{
			return 0;//если это лист
		}
		if ((temp->left != NULL) && (temp->right != NULL))
		{
			res = temp->left->h - temp->right->h;
		}
		if ((temp->left != NULL) && (temp->right == NULL))
		{
			res = (temp->left->h) + 1;
		}
		if ((temp->left == NULL) && (temp->right != NULL))
		{
			res = -((temp->right->h) + 1);
		}
		return res;
	}//дисбаланс узла
	int High()
	{
		return head->h;
	}//высота всего дерева
	void Turn_Big_L(Node*a)
	{
		Turn_Little_R(a->right);
		Turn_Litlle_L(a);

	}
	void Turn_Big_R(Node*a)
	{
		Turn_Litlle_L(a->left);
		Turn_Little_R(a);
	}
	void Turn_Little_R(Node*a)
	{
		Node* t;
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
		//значение высоты у b
		if ((t->left == NULL) && (t->right == NULL))
			t->h = 0;
		if ((t->left != NULL) && (t->right == NULL))
			t->h = t->left->h + 1;
		if ((t->left == NULL) && (t->right != NULL))
			t->h = t->right->h + 1;
		if ((t->left != NULL) && (t->right != NULL))
			t->h = std::max(t->left->h, t->right->h) + 1;
		//значение высоты у a
		if ((t->right->left == NULL) && (t->right->right == NULL))
			t->right->h = 0;
		if ((t->right->left != NULL) && (t->right->right == NULL))
			t->right->h = t->right->left->h + 1;
		if ((t->right->left == NULL) && (t->right->right != NULL))
			t->right->h = t->right->right->h + 1;
		if ((t->right->left != NULL) && (t->right->right != NULL))
			t->right->h = std::max(t->right->left->h, t->right->right->h) + 1;

	}
	void Turn_Litlle_L(Node*a)
	{
		Node* t;
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
		//значение высоты для b 
		if ((t->left == NULL) && (t->right == NULL))
			t->h = 0;
		if ((t->left != NULL) && (t->right == NULL))
			t->h = t->left->h + 1;
		if ((t->left == NULL) && (t->right != NULL))
			t->h = t->right->h + 1;
		if ((t->left != NULL) && (t->right != NULL))
			t->h = std::max(t->left->h, t->right->h) + 1;
		//
		if ((t->left->left == NULL) && (t->left->right == NULL))
			t->left->h = 0;
		if ((t->left->left != NULL) && (t->left->right == NULL))
			t->left->h = t->left->h + 1;
		if ((t->left->left == NULL) && (t->left->right != NULL))
			t->left->h = t->left->right->h + 1;
		if ((t->left->left != NULL) && (t->left->right != NULL))//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			t->left->h = std::max(t->left->left->h, t->left->right->h) + 1;

	}
	void Balance(Node* temp)
	{
		Node* t;
		int d;
		int d1, d2;
		for (t = temp; t != NULL; t = t->parent)
		{
			if ((t->left == NULL) && (t->right == NULL))
				t->h = 0;
			if ((t->left != NULL) && (t->right == NULL))
				t->h = t->left->h + 1;
			if ((t->left == NULL) && (t->right != NULL))
				t->h = t->right->h + 1;
			if ((t->left != NULL) && (t->right != NULL))
				t->h = std::max(t->left->h, t->right->h) + 1;//значение высоты 
			d = D(t);//дисбаланс
			d1 = D(t->left);
			d2 = D(t->right);
			if (d == -2)
			{
				if (d2 == 1)//большой поворот левого
				{
					Turn_Big_L(t);
				}
				if (d2 <= 0)//малый поворот левого
				{
					Turn_Litlle_L(t);
				}
			}
			if (d == 2)
			{
				if (d1 == -1)//большой поворот правого
				{
					Turn_Big_R(t);
				}
				if (d1 >= 0)//малый поворот правого
				{
					Turn_Little_R(t);
				}
			}

		}
	}
	void Insert(int priority, int number)//void Insert(double a)
	{
		Node* temp = head;
		Node* _temp = head;
		Node* temp1;
		Node*A = new Node();
		A->left = NULL;
		A->right = NULL;
		A->data.first = priority;
		A->data.second = number;
		A->h = 0;
		if (size != 0)
		{
			while (temp != NULL)
			{
				_temp = temp;//запоминаем родителя A
				if (priority < temp->data.first)
					temp = temp->left;
				else temp = temp->right;
			}
			A->parent = _temp;
			if (priority < _temp->data.first)
				_temp->left = A;

			if (priority > _temp->data.first)
				_temp->right = A;
		}
		else
		{
			A->parent = NULL;
			this->head = A;
		}
		this->size += 1;
		//нормализация
		for (temp1 =A; temp1 != NULL; temp1 = temp1->parent)
			Balance(temp1);
		//Balance(A->parent);
	}
	Node* Search(int a)
	{
		Node* temp = head;
		Node* answer = NULL;
		while (temp != NULL)
		{
			if (a == temp->data.first)
			{
				answer = temp;
				break;
			}
			if (a < temp->data.first)
				temp = temp->left;
			/*if (a > temp->data.first)*/
			else
				temp = temp->right;
		}
		return answer;
	}
	Node* max(Node* T)
	{
		Node* temp = T;
	 //Node* temp = T->left;
		Node* _temp = temp;
		while (temp != NULL)
		{
			_temp = temp;//запоминаем родителя текущего элемента=>искомый элемент
			temp = temp->right;
		}
		return _temp;
	}
	Node*min(Node*T) {
		Node* temp = T;
		Node* _temp = temp;
		while (temp != NULL)
		{
			_temp = temp;//запоминаем родителя текущего элемента=>искомый элемент
			temp = temp->left;
		}
		return _temp;
	}
	void Delete(int a) {
		Node*temp = Search(a);
		Node*temp1;
		if (temp != NULL) {
			if ((temp->left == NULL) && (temp->right == NULL)&&(temp!=head)) {
				if (temp->parent->left == temp)
					temp->parent->left = NULL;
				else
					temp->parent->right = NULL;

				for (temp1=temp->parent;temp1!=NULL;temp1=temp1->parent)
					Balance(temp1);
				//Balance(temp->parent);
			}
			if ((temp->left == NULL) && (temp->right == NULL) && (temp == head)) {
				head = NULL;
				Balance(head);
			}
			if ((temp->left == NULL) && (temp->right != NULL) && (temp != head)) {
				if (temp->parent->left == temp) {
					temp->parent->left = temp->right;
					temp->right->parent = temp->parent;
				}
				else {
					temp->parent->right = temp->right;
					temp->right->parent = temp->parent;
				}
				for (temp1 = temp->parent; temp1 != NULL; temp1 = temp1->parent)
					Balance(temp1);
				//Balance(temp->parent);
			}
			if ((temp->left == NULL) && (temp->right != NULL) && (temp == head)) {
				head = temp->right;
				temp->right->parent = NULL;
				Balance(head);
			}
			if ((temp->left != NULL) && (temp->right == NULL)&&(temp!=head)) {
				if (temp->parent->left == temp) {
					temp->parent->left = temp->left;
					temp->left->parent = temp->parent;
				}
				else {
					temp->parent->right = temp->left;
					temp->left->parent = temp->parent;
				}
				for (temp1 = temp->parent; temp1 != NULL; temp1 = temp1->parent)
					Balance(temp1);
				//Balance(temp->parent);
			}
			if ((temp->left != NULL) && (temp->right == NULL) && (temp == head)) {
				head = temp->left;
				temp->left->parent = NULL;
				Balance(head);
			}
			if ((temp->left != NULL) && (temp->right != NULL)) {
				Node*Max = max(temp->left);
				temp->data.first = Max->data.first;
				temp->data.second = Max->data.second;
				if (Max->left!=NULL)
					Max->left->parent = Max->parent;
				if (Max->parent->left==Max)
					Max->parent->left = Max->left;
				else
					Max->parent->right = Max->left;
				for (temp1 = Max->parent; temp1 != NULL; temp1 = temp1->parent)
					Balance(temp1);
				//Balance(Max);
				/*Balance(Max->parent);
				Balance(temp);*/

			}
			size--;
		}
		
	}
};