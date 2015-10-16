#include "processmanager.h"

// constructor
dtn::ProcessManager::ProcessManager()
{
	m_paused = false;
}

// attachProcess
/*
	Attach a process to the manager and call the onAttach function of the process.
*/
void dtn::ProcessManager::attachProcess(std::shared_ptr<dtn::Process> process)
{
	process->onAttach();
	m_processes.push_back(process);
}

// pause
void dtn::ProcessManager::pause()
{
	m_paused = true;
}

// play
void dtn::ProcessManager::play()
{
	m_paused = false;
}

// update
/*
	Called once per loop iteration with a delta time to update each process.
	If any processes die, their children are attached to the manager and fired.
*/
void dtn::ProcessManager::update(float dt)
{
	if (!m_paused)
	{
		size_t loopCount = 0;
		for (std::vector<std::shared_ptr<dtn::Process>>::iterator it = m_processes.begin();
			it != m_processes.end();)
		{
			if ((*it)->update(dt))
			{
				if ((*it)->m_child != NULL)
				{
					attachProcess((*it)->m_child);
					it = m_processes.begin() + loopCount;
				}
				(*it)->onDeath();
				it = m_processes.erase(it);
			}
			else
			{
				++it;
			}
			loopCount++;
		}
	}
}