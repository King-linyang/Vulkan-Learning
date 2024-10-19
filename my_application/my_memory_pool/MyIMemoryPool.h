//
// Created by wangly on 2024/10/19.
// 接口定义了内存池的基本操作

#pragma once

// 抽象内存池接口
class MyIMemoryPool {
public:
    virtual ~MyIMemoryPool() = default;

    virtual void *allocate() = 0;                  // 分配内存
    virtual void deallocate(void *p) = 0;          // 释放内存
    virtual size_t getAllocatedCount() const = 0;  // 获取已分配对象数量
    virtual size_t getTotalCapacity() const = 0;   // 获取总容量
    virtual size_t getFreeCount() const = 0;       // 获取空闲对象数量
    virtual void shrinkMemory() = 0;               // 收缩未使用的内存
};
