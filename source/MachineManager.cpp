#include "AExecutableMachine.h"
#include "MachineManager.h"

namespace cle
{
namespace fsm
{

//==============================================================================

std::shared_ptr<MachineManager> MachineManager::Make()
{
    return std::shared_ptr<MachineManager>(new MachineManager);
}

//==============================================================================

void MachineManager::Proceed()
{
    AExecutableMachine *pMachine = nullptr;
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        if (m_Machines.empty())
            return;
        pMachine = m_Machines.front();
        m_Machines.pop_front();
    }

    if (pMachine)
        pMachine->Proceed();
}

//==============================================================================

void MachineManager::Register(AExecutableMachine* pMachine)
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Machines.push_back(pMachine);
    m_ConditionalVariable.notify_all();
}

//==============================================================================

MachineManager::t_Machine_queue& MachineManager::getMachines()
{
    return m_Machines;
}

//==============================================================================

std::condition_variable& MachineManager::getConditionalVariable()
{
    return m_ConditionalVariable;
}

//==============================================================================

std::mutex& MachineManager::getMutex()
{
    return m_Mutex;
}

//==============================================================================

} // namespace fsm
} // namespace cle