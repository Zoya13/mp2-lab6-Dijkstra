
#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;

template<class ValType, int T>
class Heap
{
private:
	vector<pair<ValType,int>> data;//data.first-priority, data.second - Node1's number
	vector<pair<ValType, int>> temp;//записываем все удаленные элементы
	int d;
	void Swap(int x1, int x2)
	{
		pair<ValType, int> temp;
		temp = data[x1];
		data[x1] = data[x2];
		data[x2] = temp;
	}
	
	int MinChild(int i)
	{
		int m = i * d + 1;
		ValType min = data[i*d + 1].first;
		for (int k = i * d + 1; (k <= i * d + d) && (k < data.size()); k++)
		{
			if (data[k].first < min)
			{
				min = data[k].first;
				m = k;
			}
		}
		return m;

	}
	void SiftUp(int i)
	{
		ValType parent = data[(i - 1) / d].first;
		if (data[i].first < parent)
		{
			Swap(i, (i - 1) / d);
			SiftUp((i - 1) / d);
		}
	}
	void SiftDown(int i)
	{
		if (i*d + 1 < data.size())//если есть дети
		{
			int min = MinChild(i);
			if (data[i].first > data[min].first)
			{
				Swap(i, min);
				SiftDown(min);
			}
		}
	}
public:
	Heap()
	{
		vector<pair<ValType, int>> data;//data.first-priority, data.second - Node1's number
		d = T;
	}
	~Heap()
	{

	}
	Heap(vector<pair<ValType, int>>a, int D)
	{
		d = D;
		data = a;
		for (int i = data.size() / d; i >= 0; i--)
			SiftDown(i);
	}
	bool Empty() {
		return data.empty();
	}
	pair<ValType, int> Root() {
		return data[0];
	}
	void Insert(int priority, int number)//void Insert(ValType a)
	{
		data.push_back(make_pair(priority,number));
		SiftUp(data.size() - 1);
	}
	void DeleteRoot()
	{
		temp.push_back(data.front());
		data[0] = data[data.size() - 1];
		data.pop_back();
		SiftDown(0);
	}
	void Delete(int a) {
		int k=-1;
		for (int i = 0; i < data.size(); i++)
			if (data[i].first == a) {
				k = i;
				break;
			}
		if (k >= 0) {
			data[k].first = data[0].first - 1;
			SiftUp(k);
			DeleteRoot();
		}
	}
	void Print()
	{
		for (int i = 0; i < temp.size(); i++)
			cout << temp[i].first<<' '<< temp[i].second << endl;
	}
};









