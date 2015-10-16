/*
	process.h
	Base class for a process type. 
*/
#ifndef _PROCESS_H
#define _PROCESS_H

// c++ includes
#include<memory>

// dtn includes
#include "processmanager.h"

namespace dtn
{
	// forward decleration
	class ProcessManager;

	class Process
	{
	public :
		// constructor
		Process();

		// virtual overrides
		virtual bool update(float dt) = 0;
		virtual void onAttach() = 0;
		virtual void onDeath() = 0;

		// to setup process chaining
		void attachChild(std::shared_ptr<dtn::Process> child);
	protected :
		bool m_repeated;
		bool m_dead;
		std::shared_ptr<dtn::Process> m_child;
		friend class dtn::ProcessManager;
	};
}

#endif