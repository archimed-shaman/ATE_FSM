#include <memory>

namespace cle
{
namespace fsm
{

class MachineManager;

class ThreadExecutor
{
public:
    ThreadExecutor(std::shared_ptr<MachineManager> pMgr);

public:
    void operator()();
    void Stop();

private:
    std::shared_ptr<MachineManager> m_pMgr;
    std::shared_ptr<bool> m_lStop;
};

} // namespace fsm
} // namespace cle