#pragma once

namespace cle
{
namespace fsm
{


#define STATE(ClassName, StateName) \
    friend class St_##StateName; \
    State& StateName(); \
    class St_##StateName : public State \
    { \
        public: \
        virtual State* RunState(AStateMachine *pStateMachine){return &(static_cast<ClassName *>(pStateMachine))->StateName();}; \
    } state_##StateName

#define STATE_BODY(ClassName, StateName) State& ClassName::StateName()


#define IF_GROUP(Type, Var) \
    if(Type *Var = MatchGroup<Type>(getValue().get())) 

#define ELIF_GROUP(Type, Var) \
    else if(Type *Var = MatchGroup<Type>(getValue().get())) 

#define IF_SIGNAL(Type, Var) \
    if(Type *Var = MatchSignal<Type>(getValue().get())) 

#define ELIF_SIGNAL(Type, Var) \
    else if(Type *Var = MatchSignal<Type>(getValue().get())) 

#define ELSE else


} // namespace fsm
} // namespace cle