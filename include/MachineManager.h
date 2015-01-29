#pragma once

#include <list>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "AMachineManager.h"

namespace cle
{
namespace fsm
{

class IMachineManager;
class AExecutableMachine;

class MachineManager : public IMachineManager
{
    typedef std::list<AExecutableMachine *> t_Machine_queue;
    friend class ThreadExecutor;
public:
    static std::shared_ptr<MachineManager> Make();
    virtual ~MachineManager() = default;

protected:
    MachineManager() = default;

public:
    virtual void Proceed();
    virtual void Register(AExecutableMachine *pMachine);

protected:
    t_Machine_queue& getMachines();
    std::condition_variable& getConditionalVariable();
    std::mutex& getMutex();

private:
    t_Machine_queue m_Machines;
    std::condition_variable m_ConditionalVariable;
    std::mutex m_Mutex;
};

} // namespace fsm
} // namespace cle