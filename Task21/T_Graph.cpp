#include "T_Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <iterator>


using namespace std;

void				T_Graph::ErrorMessage				(string _error)
{
	cout << "Error : " << _error << ". " << endl;
}


vector<set<int>>	T_Graph::getDominatorsForeachVertex	(vector<list<int>> gp, int end)
{
	vector<set<int>> dp;

	dp.resize(gp.size());

	for (int i = 0; i < gp.size(); ++i)
		for (int j = 0; j < gp.size(); ++j)
			dp[i].insert(j);

	dp[end].clear();
	dp[end].insert(end);

	bool change;

	vector<bool> changed(gp.size());

	for (int i = 0; i < gp.size(); ++i)
		changed[i] = false;

	changed[end] = true;

	do
	{
		change = false;

		for (int i = 0; i < gp.size(); i++)
		{
			int oldSize = dp[i].size();

			for (int next : gp[i])
			{
				if (changed[next])
				{
					set<int> tmp;
					set_intersection(dp[i].begin(), dp[i].end(), dp[next].begin(), dp[next].end(), std::inserter(tmp, tmp.begin()));
					dp[i].clear();
					dp[i] = tmp;
					tmp.clear();
				}
			}

			dp[i].insert(i);

			if (i != end)
				changed[i] = (oldSize != dp[i].size());

			if (oldSize != dp[i].size())
				change = true;
		}
	} while (change);

	return dp;
}

vector<list<int>>	T_Graph::transpose					()
{
	int size = graph.size();
	vector<list<int>> transp(size);

	for (int i = 0; i < size; ++i)
	{
		for (auto j = graph[i].begin(); j != graph[i].end(); ++j)
			transp[*j].push_back(i);
	}
	return transp;
};

void				T_Graph::fimport					(string _filename)
{
	ifstream fin(_filename);

	if (!fin.is_open())
	{
		ErrorMessage("Couldn't open file.");
		return;
	}
	char buff[20];
	int i = 0, num;
	start = i;
	while (!fin.eof()) 
	{
		fin >> buff;
		if (isdigit(buff[0]))
		{
			num = atoi(buff);
			if (graph.size() <= num)
				graph.resize(num + 1);
			graph[i].push_back(num);
		}
		else {
			++i;
			if (graph.size() < i)
				graph.resize(i);
		}
	}
	end = i-1;
	fin.close();
}

vector<set<int>>	T_Graph::findHammocks				()
{
	auto g_t = transpose();
	vector<set<int>> dp = getDominatorsForeachVertex(graph, end);
	vector<set<int>> dpt = getDominatorsForeachVertex(g_t, start);

	for (int i = 0; i < graph.size(); i++)
	{
		dp[i].erase(i);

		set<int> newSet;

		for (int v : dp[i])
			if (dpt[v].find(i) != dpt[v].end())
				newSet.insert(v);

		dp[i] = newSet;
	}

	for (int v = 0; v < dp.size(); v++)
	{
		auto u = dp[v].begin();
		while (u != dp[v].end())
		{
			if (IsNotMinimalHammock(dp, v, *u))
				dp[v].erase(u++);
			else u++;
		}
	}
	hammocks = dp;
	return dp;
}

bool				T_Graph::IsNotMinimalHammock		(vector<set<int>> hammocks, int start, int end)
{
	set<int> used;
	queue<int> q;

	q.push(start);
	used.insert(start);

	while (q.size() > 0)
	{
		int cur = q.front();
		q.pop();

		if (cur == end)
			return true;

		for (int next : hammocks[cur])
		{
			if (used.find(next) == used.end() )
			{
				if (cur == start && next == end)
					continue;

				q.push(next);
				used.insert(next);
			}
		}
	}
	return false;
}

void				T_Graph::printGraph					()
{
}

void				T_Graph::fexport					(string _filename)
{
	ofstream fout(_filename);

	if (!fout.is_open())
		ErrorMessage(0);
	for (int i = 0; i<graph.size(); ++i)
	{
		for (auto j = graph[i].begin(); j != graph[i].end(); ++j)
		{
			fout << *j;
			fout << " ";
		}
		fout << "|";
	}
	fout.close();
}

void				print								(set<int> x)
{
	cout << "{ ";
	for (auto i : x)
		cout << i << " ";
	cout << "}" << endl;
}

void				print								(vector<set<int>> x)
{
	for (auto i : x)
		print(i);
}