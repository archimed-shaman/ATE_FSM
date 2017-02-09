#pragma once

#include <list>
#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

#include "AExecutableMachine.h"
#include "AStateMachine.h"
#include "AActor.h"
#include "State.h"

namespace cle
{
namespace fsm
{

class IMachineManager;

template <class T>
class FSM :
public AExecutableMachine, public AStateMachine, public AActor<std::shared_ptr<T>>
{
    using t_ptr = std::shared_ptr<T>;
    using t_queue = std::list<t_ptr>;

    public:

    FSM(std::shared_ptr<IMachineManager> pMgr, State & InitialState) :
            AExecutableMachine(pMgr),
            m_lActive(false),
            m_pCurrentState(&InitialState) { };

    public:

    virtual void Proceed() override
    {
        if (!m_pCurrentState)
            return;

        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            if (m_lActive || m_Queue.empty())
                return;
            m_lActive = true;

            m_CurrentValue = std::move(m_Queue.front());
            m_Queue.pop_front();
        }

        m_pCurrentState = m_pCurrentState->RunState(this);
        m_CurrentValue.reset();

        m_lActive = false;
        Schedule();
    }

    virtual State & getCurrentState() override
    {
        return *m_pCurrentState;
    }

    virtual void Send(const t_ptr & entry) override
    {
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_Queue.push_back(entry);
        }
        Schedule();
    }

    protected:

    virtual void setState(State & state) override
    {
        m_pCurrentState = &state;
    };

    void Schedule()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (m_lActive)
            return;
        if (m_Queue.empty())
            return;
        Register();
    }

    virtual t_ptr & getValue() override
    {
        return m_CurrentValue;
    }

    private:
    t_queue m_Queue;
    bool m_lActive;
    std::mutex m_Mutex;
    State *m_pCurrentState = nullptr;
    t_ptr m_CurrentValue;
};

} // namespace fsm
} // namespace cle