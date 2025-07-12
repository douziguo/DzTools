//
// Created by douziguo on 25-7-11.
//

#ifndef DZTOOLS_THREADSAFEDEQUE_H
#define DZTOOLS_THREADSAFEDEQUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <memory>

template<typename T>
class ThreadSafeDeque {
private:
    mutable std::mutex m_mutex;
    std::deque<T> m_deque;
    std::condition_variable m_cond;

public:
    ThreadSafeDeque() = default;

    // 保证队列唯一
    ThreadSafeDeque(const ThreadSafeDeque&) = delete;
    ThreadSafeDeque& operator=(const ThreadSafeDeque&) = delete;

    // 下标访问（只读，返回副本）
    T operator[](size_t index) const {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (index >= m_deque.size()) {
            throw std::out_of_range("ThreadSafeDeque: index out of range");
        }
        return m_deque[index]; // 直接使用 std::deque 的下标访问
    }

    // 获取队首元素
    T front() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_deque.empty()) {
            throw std::out_of_range("ThreadSafeDeque: front() called on empty queue");
        }
        return m_deque.front();
    }

    // 移除队首元素
    void pop_front() {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_deque.empty()) {
            m_deque.pop_front();
        }
    }

    // 入队
    void push(T&& value) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_deque.push_back(std::forward<T>(value));
        }
        m_cond.notify_one(); // 通知等待线程
    }

    // 非阻塞式出队
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_deque.empty()) return false;

        value = std::move(m_deque.front());
        m_deque.pop_front();
        return true;
    }

    // 阻塞式出队
    template<typename Rep, typename Period>
    bool wait_and_pop(T& value,
                      const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(!m_cond.wait_for(lock, timeout,
                            [this]{ return !m_deque.empty(); })) {
            return false;
        }
        value = std::move(m_deque.front());
        m_deque.pop_front();
        return true;
    }

    // 智能指针版本出队
    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]{ return !m_deque.empty(); });

        auto result = std::make_shared<T>(std::move(m_deque.front()));
        m_deque.pop_front();
        return result;
    }

    // 队列判空
    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_deque.empty();
    }

    // 获取队列大小
    size_t size() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_deque.size();
    }
};

#endif //DZTOOLS_THREADSAFEDEQUE_H
