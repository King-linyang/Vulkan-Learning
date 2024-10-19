//
// Created by wangly on 2024/10/19.
// 类实现了具体的内存池逻辑，包括内存分配、释放和自动收缩

#pragma once

#include "MyIMemoryPool.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <mutex>
#include <vector>
#include <boost/align/aligned_allocator.hpp>
#include <chrono>

// 具体内存池实现
template<typename T, size_t BlockSize = 4096, size_t Alignment = alignof(std::max_align_t)>
class MyMemoryPool : public MyIMemoryPool {
public:
    MyMemoryPool() : allocatedCount_(0), lastShrinkTime_(std::chrono::steady_clock::now()),
                     shrinkIntervalSeconds_(60) {}

    // 分配内存
    void *allocate() override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (freeList_.empty()) {
            allocateBlock();  // 如果没有空闲对象，分配新的内存块
        }

        T *result = freeList_.back();
        freeList_.pop_back();
        allocatedCount_++;
        return result;
    }

    // 释放内存
    void deallocate(void *p) override {
        std::lock_guard<std::mutex> lock(mutex_);
        freeList_.push_back(static_cast<T *>(p));
        allocatedCount_--;

        // 检查是否需要收缩内存
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastShrinkTime_).count() > shrinkIntervalSeconds_) {
            shrinkMemory();
            lastShrinkTime_ = now;
        }
    }

    // 获取已分配对象数量
    size_t getAllocatedCount() const override { return allocatedCount_; }

    // 获取总容量
    size_t getTotalCapacity() const override { return blocks_.size() * BlockSize; }

    // 获取空闲对象数量
    size_t getFreeCount() const override { return freeList_.size(); }

    // 收缩未使用的内存
    void shrinkMemory() override {
        size_t totalCapacity = getTotalCapacity();
        size_t usedCapacity = allocatedCount_;
        size_t freeCapacity = totalCapacity - usedCapacity;

        // 如果空闲容量超过总容量的一半，则开始收缩
        if (freeCapacity > totalCapacity / 2) {
            size_t blocksToRemove = freeCapacity / BlockSize / 2;

            for (size_t i = 0; i < blocksToRemove && !blocks_.empty(); ++i) {
                // 从 freeList_ 中移除属于最后一个块的指针
                freeList_.erase(
                        std::remove_if(freeList_.begin(), freeList_.end(),
                                       [this](T *ptr) {
                                           return ptr >= &blocks_.back().front() && ptr <= &blocks_.back().back();
                                       }),
                        freeList_.end()
                );
                blocks_.pop_back();  // 移除最后一个块
            }
        }
    }

private:
    // 分配新的内存块
    void allocateBlock() {
        using AlignedAllocator = boost::alignment::aligned_allocator<T, Alignment>;
        std::vector<T, AlignedAllocator> newBlock(BlockSize);

        for (auto &item: newBlock) {
            freeList_.push_back(&item);
        }

        blocks_.push_back(std::move(newBlock));
    }

    std::vector<std::vector<T, boost::alignment::aligned_allocator<T, Alignment>>>
            blocks_;  // 存储内存块的容器
    std::vector<T *> freeList_;  // 空闲对象列表
    std::mutex mutex_;  // 用于线程安全的互斥锁
    size_t allocatedCount_;  // 已分配的对象数量
    std::chrono::steady_clock::time_point lastShrinkTime_;  // 上次收缩内存的时间
    int shrinkIntervalSeconds_;  // 收缩内存的时间间隔（秒）
};
