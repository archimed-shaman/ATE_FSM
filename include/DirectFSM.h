#pragma once

#include "AStateMachine.h"
#include "AActor.h"

namespace cle
{
namespace fsm
{

template <class T>
class DirectFSM :
public AStateMachine, public AActor<T>
{
    typedef std::list<T> t_queue;

public:

    DirectFSM(State &InitialState) :
    m_lActive(false),
    m_pCurrentState(&InitialState) { };

    virtual void Send(T entry)
    {
        if (!m_pCurrentState)
            return;
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            if (m_lActive)
            {
                m_Queue.push_back(entry);
                return;
            }

            m_lActive = true;

            m_CurrentValue = entry;
        }

        m_pCurrentState = m_pCurrentState->RunState(this);

        while (true)
        {
            {
                std::lock_guard<std::mutex> lock(m_Mutex);
                if (m_Queue.empty())
                {
                    m_lActive = false;
                    return;
                }
                m_CurrentValue = m_Queue.front();
                m_Queue.pop_front();
            }
            m_pCurrentState = m_pCurrentState->RunState(this);
        }
    }

protected:

    virtual T& getValue()
    {
        return m_CurrentValue;
    }

private:
    t_queue m_Queue;
    bool m_lActive;
    std::mutex m_Mutex;

    State *m_pCurrentState = nullptr;
    T m_CurrentValue;
};

} // namespace fsm
} // namespace cle