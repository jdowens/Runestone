/*
	processmanager.h
	Manages a queue of currently being executed processes.
*/
#ifndef _PROCESSMANAGER_H
#define _PROCESSMANAGER_H

// c++ includes
#include<memory>
#include<vector>

// dtn includes
#include "process.h"

namespace dtn
{
	class Process;

	class ProcessManager
	{
	public :
		// constructor
		ProcessManager();

		// process functions
		void attachProcess(std::shared_ptr<dtn::Process> process);
		void pause();
		void play();
		void update(float dt);
	private :
		std::vector<std::shared_ptr<dtn::Process>> m_processes;
		bool m_paused;
	};
}

#endif