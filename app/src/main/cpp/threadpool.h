//
// Created by chick on 8/17/2023.
//

#pragma once
#ifndef PRIMENUMBERS_THREADPOOL_H
#define PRIMENUMBERS_THREADPOOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <queue>

namespace prim_num_api {

class ThreadPool {
private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
    size_t num_threads_;

public:
    ThreadPool(size_t num_threads) :
    stop_ { false },
    num_threads_ { num_threads }
    {
        for (size_t i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

                        if (stop_ && tasks_.empty())
                            return;

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (auto& thread : threads_) {
            thread.join();
        }
    }

    template<class F, class... Args>
    auto enqueue(F&& func, Args&&... args) -> std::future<decltype(func(args...))> {
        using returnType = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<returnType()>> (
                std::bind(std::forward<F>(func), std::forward<Args>(args)...)
                );
        //auto task = std::make_shared<std::packaged_task<returnType()>>([&func, &args...]() { return func(std::forward<Args>(args)...); });

        std::future<returnType> result = task->get_future();

        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (stop_) {
                throw std::runtime_error("ThreadPool is stopped!");
            }

            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return result;
    }

    size_t size() {
        return num_threads_;
    }
};

}
#endif //PRIMENUMBERS_THREADPOOL_H
