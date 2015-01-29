#include "MachineManager.h"
#include "AExecutableMachine.h"
#include "ThreadExecutor.h"

namespace cle
{
namespace fsm
{

//==============================================================================

ThreadExecutor::ThreadExecutor(std::shared_ptr< MachineManager > pMgr) :
m_pMgr(pMgr),
m_lStop(new bool(false)) { }

//==============================================================================

void ThreadExecutor::operator()()
{
    while (!(*m_lStop))
    {
        std::mutex &Mutex = m_pMgr->getMutex();
        std::condition_variable &CV = m_pMgr->getConditionalVariable();
        AExecutableMachine *Machine = nullptr;

        {
            std::unique_lock<std::mutex> lock(Mutex);
            MachineManager::t_Machine_queue &Machines = m_pMgr->getMachines();

            CV.wait(lock, [&]
            {
                return !Machines.empty() || *m_lStop;
            });

            if (*m_lStop)
                return;

            if (Machines.empty())
                continue;

            Machine = Machines.front();
            Machines.pop_front();
        }

        if (Machine)
            Machine->Proceed();
    }
}

//==============================================================================

void ThreadExecutor::Stop()
{
    *m_lStop = true;
    m_pMgr->getConditionalVariable().notify_all();
}

//==============================================================================

} // namespace fsm
} // namespace cle