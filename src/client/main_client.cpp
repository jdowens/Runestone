#include "gameclient.h"
#include<iostream>

int main()
{
	int pnum;
	std::cout << "ENTER PLAYER NUMBER: ";
	std::cin >> pnum;
	std::string ip;
	std::cout << "ENTER SERVER IP: ";
	std::cin >> ip;

	dtn::GameClient client(pnum, ip);
	client.run();
	return 0;
}