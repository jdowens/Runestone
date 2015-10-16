//#include "playerview.h"
//#include<iostream>
//#include "event.h"
//#include<vector>
//#include<memory>
//
//int main()
//{
//	dtn::PlayerView view1(1);
//	dtn::PlayerView view2(2);
//	bool over = false;
//	std::vector<std::shared_ptr<dtn::Event>> ret1;
//	std::vector<std::shared_ptr<dtn::Event>> ret2;
//
//	while (!over)
//	{
//		ret1 = view1.Update(ret2);
//		ret2 = view2.Update(ret1);
//		for (std::vector<std::shared_ptr<dtn::Event>>::iterator it = ret1.begin();
//			it != ret1.end(); ++it)
//		{
//			std::cout << (*it)->toString() << '\n';
//			if ((*it)->getType() == dtn::Event::EventType::GAME_QUIT)
//			{
//				over = true;
//			}
//		}
//		for (std::vector<std::shared_ptr<dtn::Event>>::iterator it = ret2.begin();
//			it != ret2.end(); ++it)
//		{
//			std::cout << (*it)->toString() << '\n';
//			if ((*it)->getType() == dtn::Event::EventType::GAME_QUIT)
//			{
//				over = true;
//			}
//		}
//	}
//}