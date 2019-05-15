#pragma once
#include "iostream"
#include "AVL.h"
#include"D-heap.h"
#include"Red-Black.h"
#include <vector>
#include <cstdlib> // ��� ������� rand() � srand()
#include <ctime> // ��� ������� time()
#include<algorithm>
using namespace std;

#define  INF  1000000000


class Algorithm {
private:
	int s;
	int n;
	vector < pair <int, vector <pair<int, int>>>> v;// ��������� � ������ ��� ����� �������-��� ������ �����
	vector<int> p;//������ �������
	void dfs(int t, vector <bool>& used, vector<int> &comp) {
		used[t] = true;
		comp.push_back(t);
		for (size_t i = 0; i < v[t].second.size(); ++i) {
			int to = v[t].second[i].first;
			if (!used[to])
				dfs(to, used, comp);
		}
	}
	bool connect(vector < pair <int, vector <pair<int, int>>>> & _v, int flag)
		//false-�� �������������//flag=1 => ����� ������� ������� ����, 0 - ������ ��������
	{

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < _v[i].second.size(); j++)
				if (_v[i].second[j].second <= 0)
					return false;
		}
		int count_comp = 0;//����� ��������� ���������
		vector <bool> used(n);
		vector<int> comp;
		for (int i = 0; i<n; ++i)
			used[i] = false;
		for (int i = 0; i<n; ++i)
			if (!used[i]) {
				int l;
				comp.clear();
				dfs(i, used, comp);
				count_comp++;
				if ((count_comp > 1) && (flag == 1)) {
					int w = rand() % 100;
					_v[i].second.push_back(make_pair(l, w));
					_v[l].second.push_back(make_pair(i, w));
				}
				l = i;
			}
		if ((count_comp > 1) && (flag == 0))
			return false;
		return true;



	}
public:
	void Generate(int _n, int _s) {
		bool flag;
		srand(15);
		vector < pair <int, vector <pair<int, int>>>> v1(_n);
		v = v1;
		vector<int>p1(_n);
		p = p1;
		for (int i = 0; i < _n; i++) {//���� �� ������� ������
			v[i].first = INF;
			int m = rand() % (_n - 1);
			/*vector <pair<int, int>> v2(m);
			v[i].second = v2;*/
			int l = v[i].second.size();
			for (int j = 0; j<m - l; j++) {//������� ����� ��� i �������
				int a = rand() % (_n - 1);
				flag = false;
				while (!flag) {
					flag = true;
					if (a == i) {
						a = rand() % (_n - 1);
						flag = false;
					}
					for (int k = 0; k < j + l; k++) {//���������, ��� ����� ������� ��� �� ���� �������������
						if (a == v[i].second[k].first) {
							a = rand() % (_n - 1);
							flag = false;
						}
					}
				}
				int weight = rand() % 100;
				v[i].second.push_back(make_pair(a, weight));
				/*v[i].second[j].first = a;
				v[i].second[j].second = weight;*/
				pair<int, int>t;
				t.first = i;
				t.second = weight;
				v[a].second.push_back(t);
			}
		}
		/*v[1].second[0].first = 4;
		v[1].second[0].second = 42;
		v[4].second[0].first = 1;
		v[4].second[0].second = 42;
		v[3].second.pop_back();
		v[3].second.pop_back();*/
		n = _n;
		s = _s;
		bool con = connect(v, 1);
	}
	Algorithm() {
		s = 0;
		n = 0;
	}
	/*Algorithm() {
	n = 3;
	s = 0;
	vector < pair <int, vector <pair<int, int>>>> v1(n);
	v = v1;
	vector<int>p1(n);
	p = p1;
	vector <pair<int, int>>v2(n);
	vector <pair<int, int>>v3(n);
	vector <pair<int, int>>v4(n);
	v[0].second = v2;
	v[1].second = v3;
	v[2].second = v4;
	v[0].second[0].first = 1;
	v[0].second[0].second = 2;
	v[0].second[1].first = 2;
	v[0].second[1].second = 3;

	v[1].second[0].first = 0;
	v[1].second[0].second = 2;
	v[1].second[1].first = 2;
	v[1].second[1].second = 4;

	v[2].second[0].first = 0;
	v[2].second[0].second = 3;
	v[2].second[1].first = 1;
	v[2].second[1].second = 4;

	}*/
	void Form(int _n, int _s) {

		int y = -1, weight, number = -1;
		int a;
		bool flag = true;
		//int l;
		n = _n;
		s = _s;
		vector < pair <int, vector <pair<int, int>>>> v1(_n);
		v = v1;
		vector<int>p1(_n);
		p = p1;
		for (int i = 0; i < _n; i++)
			v[i].first = INF;
		for (int i = 0; i < _n; i++) {
			/*cout << endl << "If you want to input a new node choose 1, else choose 2";
			cin >> l;*/

			number = -1;
			cout << endl << "A start node of edge: " << i;
			while ((number < 0) || (number > _n - 1)) {
				cout << endl << "Input a number of nodes to connect: ";
				cin >> number;
			}

			for (int j = 0; j < number; j++) {
				/*	while ((x < 0) || (x >= _n)) {
				cout << endl << "Input a start node of edge:";
				cin >> x;
				}*/
				y = -1;
				while ((y < 0) || (y >= _n)) {
					cout << endl << "Input a finish node of edge:";
					cin >> y;
				}
				cout << endl << "Input a weight of edge:";
				cin >> weight;
				flag = true;
				for (int k = 0; k <v[i].second.size(); k++) {//���������, ��� ����� ������� ��� �� ���� �������������
					if (y == v[i].second[k].first)
						flag = false;
				}
				if ((y != i) && flag) {
					v[i].second.push_back(make_pair(y, weight));
					v[y].second.push_back(make_pair(i, weight));
				}
			}
		}
	}
	bool Check(int k) {//false-�� �������������
		if (k == 1) return true;
		return connect(v, 0);
	}
	void RB() {
		for (int i = 0; i <n; i++)
			v[i].first = INF;
		v[s].first = 0;
		RBT q;
		q.Insert(v[s].first, s);
		while ((q.Root() != NULL) && (q.Root()->data.first != -1)) {
			int t = q.min(q.Root())->data.second;
			q.Delete(q.min(q.Root())->data.first);

			for (int j = 0; j<v[t].second.size(); ++j) {
				int to = v[t].second[j].first,
					len = v[t].second[j].second;
				if (v[t].first + len < v[to].first) {
					q.Delete(v[to].first);
					v[to].first = v[t].first + len;
					p[to] = t;
					q.Insert(v[to].first, to);
				}
			}
		}
	}
	void AVL() {
		for (int i = 0; i <n; i++)
			v[i].first = INF;
		v[s].first = 0;
		AVLT q;
		q.Insert(v[s].first, s);
		while (q.Root() != NULL) {
			int t = q.min(q.Root())->data.second;
			q.Delete(q.min(q.Root())->data.first);

			for (int j = 0; j<v[t].second.size(); ++j) {
				int to = v[t].second[j].first,
					len = v[t].second[j].second;
				if (v[t].first + len < v[to].first) {
					q.Delete(v[to].first);
					v[to].first = v[t].first + len;
					p[to] = t;
					q.Insert(v[to].first, to);
				}
			}
		}
	}
	void HEAP() {
		for (int i = 0; i <n; i++)
			v[i].first = INF;
		v[s].first = 0;
		Heap<int, 2> q;
		q.Insert(v[s].first, s);
		while (!q.Empty()) {
			int t = q.Root().second;
			q.Delete(q.Root().first);

			for (int j = 0; j<v[t].second.size(); ++j) {
				int to = v[t].second[j].first,
					len = v[t].second[j].second;
				if (v[t].first + len < v[to].first) {
					q.Delete(v[to].first);
					v[to].first = v[t].first + len;
					p[to] = t;
					q.Insert(v[to].first, to);
				}
			}
		}
	}
	void Way_Cost(int a) {
		vector<int> path;
		for (int k = a; k != s; k = p[k])
			path.push_back(k);
		path.push_back(s);
		reverse(path.begin(), path.end());
		for (int i = 0; i < path.size(); i++)
			cout << path[i] << ' ';
		cout << endl;
		cout << "The cost of node = " << v[a].first << endl;
	}
	void Print() {

		for (int i = 0; i < n; i++) {
			cout << "The node " << i << " connected with nodes ";
			for (int j = 0; j < v[i].second.size(); j++)
				cout << v[i].second[j].first << ' ';
			cout << endl;
		}
	}

};