#include "gameclient.h"
#include<iostream>
#include<SFGUI/SFGUI.hpp>

int main()
{
	// initialize sfgui
	
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