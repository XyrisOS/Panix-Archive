/**
 * @file Multitasking.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief Cooperative kernel multitasking manager that allows for
 * parameterless functions to be setup and run as separate processes.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */

#ifndef PANIX_CPU_MULTITASKING
#define PANIX_CPU_MULTITASKING

#include <common/types.hpp>
#include <cpu/gdt/GlobalDescriptorTable.hpp>

// Details on cooperative multitasking available at https://wiki.osdev.org/Kernel_Multitasking
struct CPUState {
    // CPU register values to be saved
    uint32_t eax;   // Accumulator register
    uint32_t ebx;   // Base register
    uint32_t ecx;   // Counter register
    uint32_t edx;   // Data register

    uint32_t esi;   // Source index register
    uint32_t edi;   // Destination index 
    uint32_t ebp;   // Stack base pointer
    // 
    /*
    uint32_t gs;    // Segment register
    uint32_t fs;    // Segment register
    uint32_t es;    // Destination segment
    uint32_t ds;    // Data segment
    */
    uint32_t error;
    // CPU Stack and various registers to be saved
    uint32_t eip;       // Index pointer
    uint32_t cs;        // Code segment
    uint32_t eflags;    // Register status flag
    uint32_t esp;       // Stack pointer
    uint32_t ss;        // Stack segment
} __attribute__((packed));

class Task {
    friend class TaskManager;
    private:
        uint8_t stack[4096];    // 4 KiB stack for processes
        CPUState* cpustate;     // Current CPU state for a given task (see struct above)
    public:
        /**
         * @brief Construct a new Task object
         * 
         * @param gdt Current global descriptor table
         * @param entrypoint Pointer to process entry point function
         */
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        /**
         * @brief Destroy the Task object
         * 
         */
        ~Task();
        // TODO: Add yield function to move onto next process.
        // See example code here: https://wiki.osdev.org/Kernel_Multitasking
};

class TaskManager {
    private:
        Task* tasks[256];   // Array of current tasks (maxed at 256 right now)
        int numTasks;       // Number of running tasks
        int currentTask;    // Current task index
    public:
        /**
         * @brief Construct a new Task Manager object
         * 
         */
        TaskManager();
        /**
         * @brief Destroy the Task Manager object
         * 
         */
        ~TaskManager();
        /**
         * @brief Adds a task to the task manager
         * 
         * @param task Task to be added
         * @return true Task was added successfully
         * @return false Kernel failed to add task. Likely due to max number of tasks running.
         */
        bool addTask(Task* task);
        // TODO: Watch the video and document what exactly this does
        /**
         * @brief 
         * 
         * @param cpustate 
         * @return CPUState* 
         */
        CPUState* schedule(CPUState* cpustate);
};

#endif /* PANIX_CPU_MULTITASKING */