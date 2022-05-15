#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <list>
#include <iostream>

template<typename T>
class SimpleSyncQueue {
public:
    SimpleSyncQueue() {}

    void Put(const T &x) {
        std::lock_guard<std::mutex> lock(m_mutex);
        // TODO m_notFull.wait..
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T &x) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_notEmpty.wait(lock, [this]() {
            return !m_queue.empty();
        });
        x = m_queue.front();
        m_queue.pop_front();
    }

    bool Empty() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    size_t Size() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.Size();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
};