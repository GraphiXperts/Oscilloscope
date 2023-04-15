#include <algorithm>
#include <controllers/thread.hpp>

namespace th {

void ThreadConfig() {
    ec::ThreadContainerManager* container_manager =
        ec::ThreadContainerManager::getInstance();

    container_manager->setTaskTypeNumber(ProcessType::Count);
    uint32_t thread_count = std::thread::hardware_concurrency();

    {
        size_t render     = 1;
        size_t idle       = (thread_count - 1) / 3;
        size_t processing = thread_count - render - idle;
        container_manager->addConfiguration(
            {{render, ProcessType::Render},
             {std::max(idle, 1UL), ProcessType::Idle},
             {std::max(processing, 1UL), ProcessType::Processing}});
    }

    {
        size_t render     = 1;
        size_t idle       = 1;
        size_t processing = thread_count - render - idle;

        container_manager->addConfiguration(
            {{render, ProcessType::Render},
             {idle, ProcessType::Idle},
             {std::max(processing, 1UL), ProcessType::Processing}});
    }

    ec::ThreadPool::getInstance()->setConfig(ThreadConfigs::Ordinary);
}

}  // namespace th