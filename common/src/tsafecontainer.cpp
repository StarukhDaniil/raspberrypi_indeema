#include <queue>
#include <string>

#include "tsafecontainer.hpp"

template <typename T>
const std::shared_ptr<T>& TSafeContainer<T>::container() const {
    return m_conteiner_ptr;
}

template <typename T>
const std::shared_ptr<std::condition_variable_any> TSafeContainer<T>::cv() const {
    return m_cv_ptr;
}

template <typename T>
const std::shared_ptr<std::shared_mutex> TSafeContainer<T>::mtx() const {
    return m_mtx_ptr;
}

template <typename T>
const std::function<bool(void)>& TSafeContainer<T>::cv_check_func() const {
    return m_cv_check_func;
}

template <typename T>
std::shared_ptr<T>& TSafeContainer<T>::container() {
    return m_conteiner_ptr;
}

template <typename T>
std::shared_ptr<std::condition_variable_any>& TSafeContainer<T>::cv() {
    return m_cv_ptr;
}

template <typename T>
std::shared_ptr<std::shared_mutex>& TSafeContainer<T>::mtx() {
    return m_mtx_ptr;
}

template <typename T>
std::function<bool(void)>& TSafeContainer<T>::cv_check_func() {
    return m_cv_check_func;
}

template <typename T>
TSafeContainer<T>::TSafeContainer(const std::shared_ptr<T>& container,
                   const std::shared_ptr<std::condition_variable_any>& cv,
                   const std::shared_ptr<std::shared_mutex>& mtx,
                   const std::function<bool(void)> cv_check) 
    : m_conteiner_ptr(container)
    , m_cv_ptr(cv)
    , m_mtx_ptr(mtx)
    , m_cv_check_func(cv_check) {
}

template class TSafeContainer<std::queue<std::string>>;