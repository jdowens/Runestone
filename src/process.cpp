#include "process.h"

// constructor
dtn::Process::Process()
{
	m_child = NULL;
}

// attachChild
/*
	Attach a child process to the process. (Will be executed upon the termination (m_dead) of the parent process).
*/
void dtn::Process::attachChild(std::shared_ptr<dtn::Process> child)
{
	m_child = child;
}