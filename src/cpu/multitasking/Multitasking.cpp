/**
 * @file Multitasking.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <cpu/multitasking/Multitasking.hpp>

TaskManager* TaskManager::activeTaskManager = nullptr;

Task::Task(GlobalDescriptorTable *gdt, void entrypoint()) {
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
}

Task::~Task() {
    // Stubbed
}
        
TaskManager::TaskManager() {
    // Set the active task manager if necessary
    if (activeTaskManager == nullptr) {
        activeTaskManager = this;
    }
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager() {
    // Stubbed
}

bool TaskManager::addTask(Task* task) {
    kprint("[TASK MANAGER] Adding task...\n");
    if(numTasks >= 256) {
        kprint("[TASK MANAGER] Too many current tasks to add new one.\n");
        return false;
    }
    tasks[numTasks++] = task;
    kprint("[TASK MANAGER] Added task successfully.\n");
    return true;
}

CPUState* TaskManager::schedule(CPUState* cpustate) {
    if (numTasks <= 0) {
        return cpustate;
    }
    
    if (currentTask >= 0) {
        tasks[currentTask]->cpustate = cpustate;
    }

    if (++currentTask >= numTasks) {
        currentTask %= numTasks;
    }

    return tasks[currentTask]->cpustate;
}