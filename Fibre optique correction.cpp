#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

const int MAX_PC = 100000;
list<int> connections[MAX_PC];
int values[MAX_PC];
bool connections_checks[MAX_PC];

// calculer les connections
void calc_vulue(int root)
{
	connections_checks[root] = true;
	for (int branch : connections[root])
	{
		if (!connections_checks[branch])
		{
			calc_vulue(branch);
			values[root] += values[branch];
		}
	}
}

// trouver la place pour brancher la fibre
int root = 0;
int min_connections = 100000;
void find_root(int node)
{
	int next_check = 0;
	int max_connections = 0;
	for (int branch : connections[node])
	{
		if (values[branch] > max_connections)
		{
			max_connections = values[branch];
			next_check = branch;
		}
	}
	if (min_connections > max_connections)
	{
		min_connections = max_connections;
		values[root] -= values[next_check];
		values[next_check] += values[root];
		root = next_check;
		find_root(next_check);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int nb_pc;
	cin >> nb_pc;
	
	// faire les liens entre les PC
	for (int connection = 0; connection < (nb_pc - 1); connection++)
	{
		int pc1, pc2;
		cin >> pc1 >> pc2;
		connections[pc1].push_back(pc2);
		connections[pc2].push_back(pc1);
	}

	// calculer combien de PC sont attaches a chaque PC
	for (int value = 0; value < MAX_PC; value++)
		values[value] = 1;
	calc_vulue(0);

	// trouver ou brancher la fibre
	find_root(0);

	// donnes la reponse
	cout << min_connections << '\n';
	return 0;
}
