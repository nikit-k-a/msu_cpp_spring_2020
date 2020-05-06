#include <iostream>
#include "My_thread_pool.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include <chrono>


My_thread_pool::My_thread_pool(size_t poolSize):
    poolSize_(poolSize),
    work (true)
    {
        for (int i = 0; i < poolSize; i++)
        {
        threads.emplace_back(
            [this]()
            {
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mut);
                        condition.wait(lock,
                        [this]()
                        {
                            return !func_queue.empty() || !work;
                        });

                        if (!work && func_queue.empty() )
                        {
                            return;
                        }
                        task = std::move(func_queue.front());
                        func_queue.pop();
                    }
                    task();
                }
            });
        }
    }

My_thread_pool::~My_thread_pool()
{
    {
        std::unique_lock<std::mutex> lock(mut);
        work = false;
    }
    condition.notify_all();
    for(auto &thread: threads)
        thread.join();
}
