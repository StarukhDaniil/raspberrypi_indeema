#pragma once

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <functional>
#include <memory>

template <typename T>
class TSafeContainer {
private:
    std::shared_ptr<T> m_conteiner_ptr;
    std::shared_ptr<std::condition_variable_any> m_cv_ptr;
    std::shared_ptr<std::shared_mutex> m_mtx_ptr;
    std::function<bool(void)> m_cv_check_func;
public:
    const std::shared_ptr<T>& container() const;
    const std::shared_ptr<std::condition_variable_any> cv() const;
    const std::shared_ptr<std::shared_mutex> mtx() const;
    const std::function<bool(void)>& cv_check_func() const;

    std::shared_ptr<T>& container();
    std::shared_ptr<std::condition_variable_any>& cv();
    std::shared_ptr<std::shared_mutex>& mtx();
    std::function<bool(void)>& cv_check_func();

    TSafeContainer(const TSafeContainer& other) = default;
    TSafeContainer(const std::shared_ptr<T>& container,
                   const std::shared_ptr<std::condition_variable_any>& cv,
                   const std::shared_ptr<std::shared_mutex>& mtx,
                   const std::function<bool(void)> cv_check);
};