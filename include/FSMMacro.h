#pragma once


#define STATE(ClassName, StateName) \
    friend class St_##StateName; \
    cle::fsm::State& StateName(); \
    class St_##StateName : public cle::fsm::State \
    { \
        public: \
        virtual cle::fsm::State* RunState(AStateMachine *pStateMachine){return &(static_cast<ClassName *>(pStateMachine))->StateName();}; \
    } state_##StateName

#define STATE_BODY(ClassName, StateName) cle::fsm::State& ClassName::StateName()


#define IF_GROUP(Type, Var) \
    if(auto Var = std::move(MatchGroup<Type>(getValue())))

#define ELIF_GROUP(Type, Var) \
    else if(auto Var = std::move(MatchGroup<Type>(getValue())))

#define IF_SIGNAL(Type, Var) \
    if(auto Var = std::move(cle::fsm::MatchSignal<Type>(getValue())))

#define ELIF_SIGNAL(Type, Var) \
    else if(auto Var = std::move(cle::fsm::MatchSignal<Type>(getValue()))) 

#define ELSE else
