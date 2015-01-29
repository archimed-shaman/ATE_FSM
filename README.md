# ATE_FSM
Abstract Telephony Equipment - Final State Machines

Simple Actor-FSM library

Example:

```c++
#include <iostream>
#include <thread>
#include <random>
#include <cmath>

#include "FSM.h"
#include "DirectFSM.h"
#include "AStateMachine.h"
#include "MachineManager.h"
#include "ThreadExecutor.h"
#include "State.h"
#include "FSMMacro.h"
#include "Signal.h"

#include <unistd.h>

using namespace cle::fsm;

typedef std::shared_ptr<Signal> tSignal_ptr;
typedef FSM<tSignal_ptr> ActorFSM;

class Listener;

//==============================================================================

class CallbackSignal : public Signal
{
public:

    CallbackSignal(int nValue, Listener* pSource) :
    m_nValue(nValue), m_pSource(pSource) { }
    virtual ~CallbackSignal() = default;
    int m_nValue;
    Listener* m_pSource;
};

//==============================================================================

class StopSignal : public Signal
{
public:
    StopSignal() { }
    virtual ~StopSignal() = default;
};

//==============================================================================

class Listener : public ActorFSM
{
public:

    Listener(std::shared_ptr<MachineManager>& pMgr, const char* sName);
    STATE(Listener, ONE);
    STATE(Listener, TWO);

    const std::string& getName() const;

private:
    int m_nCounter = 0;
    std::string m_sName;
};

Listener::Listener(std::shared_ptr<MachineManager>& pMgr, const char* sName) :
ActorFSM(pMgr, state_ONE), m_sName(sName) { }

const std::string& Listener::getName() const
{
    return m_sName;
}

STATE_BODY(Listener, ONE)
{

    IF_SIGNAL(StopSignal, S)
    {
        std::cout << getName() << " -> TWO" << std::endl;
        return state_TWO;
    }

    ELIF_SIGNAL(CallbackSignal, Signal)
    {
        std::cout << getName() << " received from " << Signal->m_pSource->getName() << ": " << Signal->m_nValue << std::endl;
        
        m_nCounter += Signal->m_nValue;
        if (m_nCounter > 10)
        {
            std::cout << getName() << " -> TWO" << std::endl;
            Signal->m_pSource->Send(tSignal_ptr(new StopSignal()));
            return state_TWO;
        }

        Signal->m_pSource->Send(tSignal_ptr(new CallbackSignal(m_nCounter, this)));
        std::cout << getName() << " -> ONE" << std::endl;
        return state_ONE;
    }
}

STATE_BODY(Listener, TWO)
{
    return state_TWO;
}

//==============================================================================

int main()
{
    auto mgr = MachineManager::Make();

    ThreadExecutor E1(mgr);
    ThreadExecutor E2(mgr);
    ThreadExecutor E3(mgr);
    ThreadExecutor E4(mgr);
    std::thread executor1(E1);
    std::thread executor2(E2);
    std::thread executor3(E3);
    std::thread executor4(E4);

    Listener F1(mgr, "F");
    Listener F2(mgr, "S");

    F1.Send(tSignal_ptr(new CallbackSignal(1, &F2)));


    usleep(1000000);
    std::cout << "Stopping: " << std::endl;

    E1.Stop();
    E2.Stop();
    E3.Stop();
    E4.Stop();

    executor1.join();
    executor2.join();
    executor3.join();
    executor4.join();

    return 0;
}
```

Output:

```
$ ./a.out 
F received from S: 1
F -> ONE
S received from F: 1
S -> ONE
F received from S: 1
F -> ONE
S received from F: 2
S -> ONE
F received from S: 3
F -> ONE
S received from F: 5
S -> ONE
F received from S: 8
F -> TWO
S -> TWO
Stopping:
```
