#include <bits/stdc++.h>

#include <utility>

using namespace std;
using namespace rel_ops;
#define ll long long

enum dir
{
	E = 0, W, S, N, SE, SW, NW, NE
};

class vect
{
public:
	string val;
	ll x {}, y {};
	dir dir;

	vect(string v, ll _x, ll _y, enum dir _dir) : val(std::move(v)), x(_x), y(_y), dir(_dir)
	{};

	explicit vect(string v) : val(std::move(v))
	{ x = 0, y = 0, dir = E; };

	bool operator<(const vect &other) const
	{
		return val < other.val;
	}

	bool operator==(const vect &other) const
	{
		return val == other.val;
	}
};

int main()
{
	//variable init
	ll m, n;
	set<vect> set;
	array<bool, 8> allow {};
	array<string, 8> dir_str {"E", "W", "S", "N", "SE", "SW", "NW", "NE"};

	//get val m, n
	cout << "Dimension: ";
	cin >> m >> n;
	cout << "Enter matrix:\n";

	//vector matrix init
	vector<vector<char>> v;

	//get val matrix
	for (ll i = 0; i < n; i++)
	{
		vector<char> temp;
		for (ll j = 0; j < m; j++)
		{
			char a;
			cin >> a;
			temp.emplace_back(a);
		}
		v.emplace_back(temp);
	}

	//allowed dir (uncomment to enable/unable)
	cout << "Enter allowed dir (E, W, S, N, SE, SW, NW, NE): ";
	for (ll i = 0; i < 8; i++)
	{
		cin >> allow[i];
	}
//	allow = {1, 0, 1, 0, 1, 0, 0, 0};

	//print matrix
	for (const auto &a: v)
	{
		for (auto b: a)
		{
			cout << b << " ";
		}
		cout << "\n";
	}

	//all string permutations
	for (ll i = 0; i < n; i++)
	{
		for (ll j = 0; j < m; j++)
		{
			//string init
			string templ = string(1, v[i][j]);
			string t = templ;

			//→
			if (allow[0])
			{
				t = templ;
				for (ll l = j + 1; l < m; l++)
				{
					t += v[i][l];
					set.insert(vect(t, i, j, E));
				}
			}

			//←
			if (allow[1])
			{
				t = templ;
				for (ll l = j - 1; l >= 0; l--)
				{
					t += v[i][l];
					set.insert(vect(t, i, j, W));
				}
			}

			//↓
			if (allow[2])
			{
				t = templ;
				for (ll l = i + 1; l < n; l++)
				{
					t += v[l][j];
					set.insert(vect(t, i, j, S));
				}
			}

			//↑
			if (allow[3])
			{
				t = templ;
				for (ll l = i - 1; l >= 0; l--)
				{
					t += v[l][j];
					set.insert(vect(t, i, j, N));
				}
			}

			//↘
			if (allow[4])
			{
				t = templ;
				for (ll l = i + 1, k = j + 1; l < n && k < m; l++, k++)
				{
					t += v[l][k];
					set.insert(vect(t, i, j, SE));
				}
			}

			//↙
			if (allow[5])
			{
				t = templ;
				for (ll l = i + 1, k = j - 1; l < n && k >= 0; l++, k--)
				{
					t += v[l][k];
					set.insert(vect(t, i, j, SW));
				}
			}

			//↖
			if (allow[6])
			{
				t = templ;
				for (ll l = i - 1, k = j - 1; l >= 0 && k >= 0; l--, k--)
				{
					t += v[l][k];
					set.insert(vect(t, i, j, NW));
				}
			}

			//↗
			if (allow[7])
			{
				t = templ;
				for (ll l = i + 1, k = j + 1; l < n && k < m; l++, k++)
				{
					t += v[l][k];
					set.insert(vect(t, i, j, NE));
				}
			}
		}
	}

	//print all string permutations
	for (const auto &s: set)
	{
		cout << s.val << endl;
	}

	//search query
	cout << "Enter search term, type '0' to end program:\n";
	string search;
	while (cin >> search)
	{
		if (search == "0")
		{
			break;
		}
		else
		{
			auto itr = set.find(vect(search));
			if (itr != set.end())
			{
				cout << "FOUND!\nPosition: x=" << itr->x + 1 << ", y=" << itr->y + 1 << "\nDirection: "
				     << dir_str[itr->dir] << endl;
			}
			else
			{
				cout << "NOT FOUND!\n";
			}
		}
	}
}