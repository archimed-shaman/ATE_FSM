#pragma once

#include <memory>
#include <AMachineManager.h>

namespace cle
{
namespace fsm
{

class AExecutableMachine
{
public:

    AExecutableMachine(std::shared_ptr<IMachineManager> pMgr) :
    m_pMgr(pMgr) { };

public:
    virtual void Proceed() = 0;

protected:

    void Register()
    {
        if (m_pMgr)
            m_pMgr->Register(this);
    }

private:
    std::shared_ptr<IMachineManager> m_pMgr;
};

} // namespace fsm
} // namespace cle