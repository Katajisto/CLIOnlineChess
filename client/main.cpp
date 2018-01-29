#include<bits/stdc++.h>
#include<SFML/Network.hpp>
using namespace sf;
using namespace std;
int lauta[8][8];
vector<int> rivi = {2,3,4,5,6,4,3,2};
vector<string> nimet_m = {" ","\u2659","T", "R", "L", "K", "Q"};
vector<string> nimet_v = {" ","\u265F","\u265C","\u265E","\u265D", "\u265A", "\u265B", "\u2659", "\u2656", "\u2658", "\u2657","\u2654","\u2655"};
vector<int> w_eat;
vector<int> b_eat;
bool checksiirto(string a, string b)
{
	bool is_correct = true;
	int movnum = lauta[a[0]-'A'][a[1]-'0'-1];
	int tomovnum = lauta[b[0]-'A'][b[1]-'0'-1];
	/*
	if(movnum == 1)
	{
		if(b[0] < a[0]) return false;
		if(b[1] != a[1] || abs(b[1] - a[1]) == 1 && tomovnum == 0) return false;
		if(abs(b[0] - a[0]) != 1 || abs(b[0] - a[0]) != 2 && a[0] != 'B' || a[0] != 'G'); 
	}
	*/
	if(lauta[a[0]-'A'][a[1]-'0'-1] == 0) return false;
	if(lauta[b[0]-'A'][b[1]-'0'-1] == 0) goto skip;
	if(lauta[a[0]-'A'][a[1]-'0'-1] - 6 < 1 && lauta[b[0]-'A'][b[1]-'0'-1] - 6 < 1) return false;
	if(lauta[a[0]-'A'][a[1]-'0'-1] - 6 > 0 && lauta[b[0]-'A'][b[1]-'0'-1] - 6 > 0) return false;
	skip:
	if(a[0] < 'A' || a[0] > 'H') is_correct = false;
	if(a[1] < '1' || a[1] > '8') is_correct = false;
	if(b[0] < 'A' || a[0] > 'H') is_correct = false;
	if(b[1] < '1' || b[1] > '8') is_correct = false;
	return is_correct;
}
void print()
{
	cout << "  ";
	for(int i = 1; i <= 8; i++)
	{
		cout << i << " ";
	}
	cout << "\n";
	for(int i = 0; i < 8; i++)
	{
		char rivi = i + 'A';
	        cout << rivi << " ";	
		for(int i2 = 0; i2 < 8; i2++)
		{
			cout << nimet_v[lauta[i][i2]] << " ";
		}
		cout << "\n";
	}
	cout << "Valkoinen: ";
	for(int i : w_eat) {cout << nimet_v[i] << " ";}
	cout << "\n";
	cout << "Musta: ";
	for(int i : b_eat) {cout << nimet_v[i] << " ";}
	cout << "\n";
}
void init_lauta()
{
	for(int i = 0; i < 8; i++)
	{
		for(int i2 = 0; i2 < 8; i2++)
		{
			if(i == 1)
			{
				lauta[i][i2] = 1;
				continue;
			}
			if(i == 6)
			{
				lauta[i][i2] = 7;
				continue;
			}
			if(i == 0)

			{
				lauta[i][i2] = rivi[i2];
				continue;
			}
			if(i == 7)
			{
				lauta[i][i2] = rivi[i2] + 6;
				continue;
			}
		}
	}
}
int main()
{
	system("clear");
	string ip;
	int port;
	cout << "IP: "; cin >> ip;
	cout << "PORT: "; cin >> port;
	TcpSocket socket;
	socket.connect(ip, port);
	init_lauta();
	print();
	bool first;
	cout << "WILL YOU GO FIRST?: "; cin >> first;
	while(true)
	{
		check_siirto:
		string siirto1, siirto2;
		if(first)
		{
			cout << "SIIRTO: ";
			cin >> siirto1; cin >> siirto2;
			if(checksiirto(siirto1, siirto2) == false) {cout << "INVALID MOVE\n"; goto check_siirto;}
			Packet siirto; 
			siirto << siirto1 << siirto2;
			socket.send(siirto);
		}
		else
		{
			Packet siirto; 
			socket.receive(siirto);
//			cout << "RECEIVED" << "\n";
			siirto >> siirto1; siirto >> siirto2;
//			cout << siirto1 << " :: " << siirto2 << "\n";
		}
		int siirrettava = lauta[siirto1[0]-'A'][siirto1[1]-'0'-1];
		lauta[siirto1[0]-'A'][siirto1[1]-'0'-1] = 0;
		if(lauta[siirto2[0] - 'A'][siirto2[1]-'0'-1] != 0)
		{
			int syotava = lauta[siirto2[0]-'A'][siirto2[1]-'0'-1];
			if(syotava - 6 > 0) {w_eat.push_back(syotava);}
			else {b_eat.push_back(syotava);}
		}
		lauta[siirto2[0]-'A'][siirto2[1]-'0'-1] = siirrettava;
		system("clear");
		print();
		first = !first;
	}
}
