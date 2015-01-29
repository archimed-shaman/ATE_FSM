#pragma once

#include <functional>

namespace cle
{
namespace fsm
{

class AExecutableMachine;

class IMachineManager
{
public:
    virtual ~IMachineManager() = default;
    virtual void Register(AExecutableMachine *pMachine) = 0;
    virtual void Proceed() = 0;
};

} // namespace fsm
} // namespace cle