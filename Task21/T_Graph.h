#ifndef T_GRAPH_H
#define T_GRAPH_H

#include <list>

#include <vector>
#include <list>
#include <set>

using namespace std;



class T_Graph
{

	vector<list<int>>		graph;

	vector<bool>			vizited;

	vector<set<int>>		hammocks;

	set<int>				stack;

	void					ErrorMessage				(string _error);

	vector<set<int>>		getDominatorsForeachVertex	(vector<list<int>> gp, int end);

	bool					IsNotMinimalHammock(vector<set<int>> hammocks, int start, int end);


public:

	int						start, end;

	vector<list<int>>		transpose					();

	void					fexport						(string _filename);

	void					fimport						(string _filename);

	vector<set<int>>		findHammocks				();

	
	void					printGraph					();

	void					printHammocks				();

							T_Graph						(vector<list<int>> gr) 
								: graph(gr) {};

							T_Graph						()	{};
};

	set<int>				intersection				(set<int> A, set<int> B);

	void print(vector<set<int>> x);

	void print(set<int> x);

#endif