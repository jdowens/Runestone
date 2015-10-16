//#include <iostream>
//#include "gameclient.h"
//#include "gameserver.h"
//
//std::vector<std::shared_ptr<dtn::Event>> p1Ret;
//std::vector<std::shared_ptr<dtn::Event>> p2Ret;
//std::vector<std::shared_ptr<dtn::Event>> serverRet;
//
//int main()
//{
//	dtn::GameServer server;
//	dtn::GameClient p1(1), p2(2);
//	while (true)
//	{
//		serverRet = server.update(p1Ret, p2Ret);
//		p1Ret = p1.update(serverRet);
//		p2Ret = p2.update(serverRet);
//	}
//}