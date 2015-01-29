#pragma once

namespace cle
{
namespace fsm
{

class Signal
{
public:
    virtual ~Signal() = default;
};

class Group
{
public:
    virtual ~Group() = default;
};

template<class T>
T* MatchSignal(Signal *pSignal)
{
    return dynamic_cast<T*> (pSignal);
}

template<class T>
T* MatchGroup(Group *pGroup)
{
    return dynamic_cast<T*> (pGroup);
}

} // namespace fsm
} // namespace cle