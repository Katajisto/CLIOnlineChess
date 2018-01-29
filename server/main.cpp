#include<bits/stdc++.h>
#include<SFML/Network.hpp>
using namespace std;
using namespace sf;
int main()
{
	int port; cout << "PORT: "; cin >> port;
	TcpListener listener;
	listener.listen(port);
	TcpSocket client1; TcpSocket client2;
	listener.accept(client1);
	cout << "PLAYER 1 JOINED" << "\n";
	listener.accept(client2);
	cout << "PLAYER 2 JOINED" << "\n";
	cout << "STARTING GAME" << "\n";
	bool flip = 0;
	while(true)
	{
		Packet siirto; 
		if(flip == 0)
		{
			client1.receive(siirto);
			client2.send(siirto);
			flip = 1;
		}
		else
		{
			client2.receive(siirto);
			client1.send(siirto);
			flip = 0;
		}
		
	}
}
