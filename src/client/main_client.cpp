#include "gameclient.h"
#include<iostream>

int main()
{
	int pnum;
	std::cout << "ENTER PLAYER NUMBER: ";
	std::cin >> pnum;

	dtn::GameClient client(pnum);
	client.run();
	return 0;
}