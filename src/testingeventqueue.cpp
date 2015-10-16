//#include<iostream>
//#include "eventmanager.h"
//
//dtn::EventManager manager;
//
//class Test
//{
//public :
//	Test()
//	{
//		m_eventRunestoneMoveID = manager.attachListener(dtn::Event::EventType::RUNESTONE_MOVE,
//			std::bind(&Test::onRunestoneMove, this, std::placeholders::_1));
//		m_eventRunestoneAttackID = manager.attachListener(dtn::Event::EventType::RUNESTONE_ATTACK,
//			std::bind(&Test::onRunestoneAttack, this, std::placeholders::_1));
//	}
//	~Test()
//	{
//		manager.removeListener(m_eventRunestoneMoveID);
//		manager.removeListener(m_eventRunestoneAttackID);
//	}
//private :
//	void onRunestoneMove(std::shared_ptr<dtn::Event> e)
//	{
//		dtn::EventRunestoneMove* cast = dynamic_cast<dtn::EventRunestoneMove*>(e.get());
//		std::cout << cast->toString();
//	}
//	void onRunestoneAttack(std::shared_ptr<dtn::Event> e)
//	{
//		std::cout << e->toString();
//	}
//	int m_eventRunestoneMoveID;
//	int m_eventRunestoneAttackID;
//};
//
//int main()
//{
//	Test* t = new Test();
//	manager.pushEvent(std::shared_ptr<dtn::Event>(new dtn::EventRunestoneAttack(sf::Vector2i(12, 12), sf::Vector2i(0, 3))));
//	manager.pushEvent(std::shared_ptr<dtn::Event>(new dtn::EventRunestoneMove(sf::Vector2i(12, 12), sf::Vector2i(0, 3))));
//	manager.update();
//	delete t;
//}