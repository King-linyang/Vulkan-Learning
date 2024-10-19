//
// Created by wangly on 2024/10/19.
// 内存池管理

#pragma once

#include <iostream>
#include <boost/pool/pool.hpp>
#include <boost/thread/mutex.hpp>

// 宏定义用于不同类型内存的申请
//申请小内存
#define ALLOCATE_SMALL_MEMORY(size) MyMemoryPoolManager::getInstance().allocate(MemoryType::SMALL, size)
//申请中内存
#define ALLOCATE_MEDIUM_MEMORY(size) MyMemoryPoolManager::getInstance().allocate(MemoryType::MEDIUM, size)
//申请大内存
#define ALLOCATE_LARGE_MEMORY(size) MyMemoryPoolManager::getInstance().allocate(MemoryType::LARGE, size)
//释放内存
#define DEALLOCATE_MEMORY(type, ptr) MyMemoryPoolManager::getInstance().deallocate(type, ptr)

// 定义不同类型内存的标识
enum class MemoryType {
    SMALL,
    MEDIUM,
    LARGE
};

class MyMemoryPoolManager {
public:
    // 单例模式获取实例
    static MyMemoryPoolManager &getInstance() {
        static MyMemoryPoolManager instance;
        return instance;
    }

    // 从对应类型的内存池中分配内存
    void *allocate(MemoryType type, size_t size) {
        boost::mutex::scoped_lock lock(mutex_);
        boost::pool<> *pool = nullptr;
        switch (type) {
            case MemoryType::SMALL:
                if (smallPool_ == nullptr || smallPool_->get_requested_size() < size) {
                    smallPool_ = new boost::pool<>(size);
                }
                pool = smallPool_;
                break;
            case MemoryType::MEDIUM:
                if (mediumPool_ == nullptr || mediumPool_->get_requested_size() < size) {
                    mediumPool_ = new boost::pool<>(size);
                }
                pool = mediumPool_;
                break;
            case MemoryType::LARGE:
                if (largePool_ == nullptr || largePool_->get_requested_size() < size) {
                    largePool_ = new boost::pool<>(size);
                }
                pool = largePool_;
                break;
        }
        return pool->malloc();
    }

    // 释放内存回对应类型的内存池
    void deallocate(MemoryType type, void *ptr) {
        boost::mutex::scoped_lock lock(mutex_);
        boost::pool<> *pool = nullptr;
        switch (type) {
            case MemoryType::SMALL:
                pool = smallPool_;
                break;
            case MemoryType::MEDIUM:
                pool = mediumPool_;
                break;
            case MemoryType::LARGE:
                pool = largePool_;
                break;
        }
        if (pool != nullptr) {
            pool->free(ptr);
        }
    }

private:
    MyMemoryPoolManager() : smallPool_(nullptr), mediumPool_(nullptr), largePool_(nullptr) {}

    ~MyMemoryPoolManager() {
        delete smallPool_;
        delete mediumPool_;
        delete largePool_;
    }

    boost::pool<> *smallPool_;
    boost::pool<> *mediumPool_;
    boost::pool<> *largePool_;
    boost::mutex mutex_;
};
