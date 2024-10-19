//
// Created by wangly on 2024/10/19.
// 类使用单例模式管理多个不同类型的内存池，提供了一个统一的接口来进行内存操作

#pragma once

#include "MyIMemoryPool.h"
#include "MyMemoryPool.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <mutex>
#include <vector>
#include <boost/align/aligned_allocator.hpp>
#include <chrono>

// 内存池管理器
class MyMemoryPoolManager {
public:
    // 获取单例实例
    static MyMemoryPoolManager &getInstance() {
        static MyMemoryPoolManager instance;
        return instance;
    }

    // 分配指定类型的对象
    template<typename T>
    T *allocate() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto &pool = getPool<T>();
        return static_cast<T *>(pool.allocate());
    }

    // 释放指定类型的对象
    template<typename T>
    void deallocate(T *p) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto &pool = getPool<T>();
        pool.deallocate(p);
    }

    // 获取指定类型的已分配对象数量
    template<typename T>
    size_t getAllocatedCount() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto &pool = getPool<T>();
        return pool.getAllocatedCount();
    }

    // 获取指定类型的总容量
    template<typename T>
    size_t getTotalCapacity() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto &pool = getPool<T>();
        return pool.getTotalCapacity();
    }

    // 获取指定类型的空闲对象数量
    template<typename T>
    size_t getFreeCount() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto &pool = getPool<T>();
        return pool.getFreeCount();
    }

    // 添加以下模板函数
    template<typename T>
    void poolDelete(T *&ptr) {
        if (ptr) {
            ptr->~T();
            MyMemoryPoolManager::getInstance().deallocate(ptr);
            ptr = nullptr;
        }
    }

private:
    MyMemoryPoolManager() = default;

    ~MyMemoryPoolManager() = default;

    MyMemoryPoolManager(const MyMemoryPoolManager &) = delete;

    MyMemoryPoolManager &operator=(const MyMemoryPoolManager &) = delete;

    // 获取或创建指定类型的内存池
    template<typename T>
    MyIMemoryPool &getPool() {
        std::type_index typeId(typeid(T));
        auto it = pools_.find(typeId);
        if (it == pools_.end()) {
            // 如果不存在，创建新的内存池
            auto [inserted_it, success] = pools_.emplace(typeId, std::make_unique<MyMemoryPool<T >>());
            return *inserted_it->second;
        }
        return *it->second;
    }

    std::unordered_map<std::type_index, std::unique_ptr<MyIMemoryPool>> pools_;  // 存储不同类型的内存池
    std::mutex mutex_;  // 用于线程安全的互斥锁
};

// 从内存池中分配内存
#define POOL_ALLOCATE(type) \
    MyMemoryPoolManager::getInstance().allocate<type>()

// 将对象释放回内存池
#define POOL_DEALLOCATE(ptr) \
    do { \
        if (ptr) { \
            MyMemoryPoolManager::getInstance().deallocate(ptr); \
            ptr = nullptr; \
        } \
    } while(0)

// 使用内存池创建对象（调用构造函数）
#define POOL_NEW(type, ...) \
    new (POOL_ALLOCATE(type)) type(__VA_ARGS__)

// 销毁对象并将内存释放回内存池
#define POOL_DELETE(ptr) \
    MyMemoryPoolManager::getInstance().poolDelete(ptr)
