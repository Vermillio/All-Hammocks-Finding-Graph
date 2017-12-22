#include "T_Graph.h"
#include <string>
#include <xstring>
#include <iostream>
using namespace std;

string getcd()
{
	wchar_t *s = nullptr;
	wstring ws = _wgetcwd(s, _MAX_PATH);
	return string(ws.begin(), ws.end());
}

int main()
{
	string cd = getcd();

	string filename;
	cout << "Enter filename (should be stored here: " << endl << "( " << cd << " )" << endl;
	cin >> filename;

	T_Graph gr;
	gr.fimport(cd + "\\" + filename);
	vector<set<int>> hammocks = gr.findHammocks();
	print(hammocks);
	system("pause");
	return 0;
}