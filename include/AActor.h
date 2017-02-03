#pragma once

namespace cle
{
namespace fsm
{

template <class T>
class AActor
{
public:
    virtual void Send(const T& entry) = 0;

protected:
    virtual T& getValue() = 0;
};

} // namespace fsm
} // namespace cle
