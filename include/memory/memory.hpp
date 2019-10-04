/**
 * @file memory.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-10-02
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */

#ifndef PANIX_MEMORY_MANAGER
#define PANIX_MEMORY_MANAGER

#include <common/types.hpp>

struct MemoryChunk {
    MemoryChunk *next;
    MemoryChunk *prev;
    bool allocated;
    size_t size;
};

class MemoryManager {
    protected:
        MemoryChunk* first;

    public:
        static MemoryManager* activeMemoryManager;

        MemoryManager(size_t start, size_t size);
        ~MemoryManager();
        void* malloc(size_t size);
        void free(void* ptr);
};

void* operator new(size_t size);
void* operator new[](size_t size);

// placement new
void* operator new(size_t size, void* ptr);
void* operator new[](size_t size, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);

#endif /* PANIX_MEMORY_MANAGER */