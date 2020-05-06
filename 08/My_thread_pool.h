#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H


#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <functional>

class My_thread_pool
{
    private:
        size_t poolSize_;
        bool work;
        std::mutex mut;
        std::vector<std::thread> threads;
        std::queue <std::function<void ()>> func_queue;
        std::condition_variable condition;

    public:
        explicit My_thread_pool(size_t poolSize);
        ~My_thread_pool();

        template <typename Func, typename... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
        {
            auto task =  std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
            {
                std::unique_lock<std::mutex> lock(mut);
                if(!work) throw std::runtime_error("ThreadPool was stopped, can't enque");

                func_queue.emplace(
                    [task]()
                    {
                        (*task)(); 
                    });
            }
            condition.notify_one();
            return task->get_future();;
        }
};



#endif
