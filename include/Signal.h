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

using t_SignalPtr = std::shared_ptr<Signal>;

class Group
{
public:
    virtual ~Group() = default;
};

using t_GroupPtr = std::shared_ptr<Group>;

template<class T>
std::shared_ptr<T> MatchSignal(t_SignalPtr pSignal)
{
    return std::dynamic_pointer_cast<T> (pSignal);
}

template<class T>
std::shared_ptr<T> MatchGroup(Group pGroup)
{
    return std::dynamic_pointer_cast<T> (pGroup);
}

} // namespace fsm
} // namespace cle