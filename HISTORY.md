## CS-3950 Progress Report History
Update Progress (Starting August 2019)
- August 28-30:
    - Interrupt handler manager was refactored to use function pointers with loops (w/o tutorial)
    - Keyboard driver was refactored to use allow shell access (added key buffer)
    - Kernel level shell (Basch) was further implemented
    - Basic terminal commands were added for debugging
    - Kernel panics no longer infinitely cycle text on screen. (Halt asm is now called)
    - VGA drivers were implemented in a hack-ish manner (lots of temporary code)
    - Unused kernel libc functions and files were removed to slim kernel size
    - Ported some useful string functions from the master branch into the Switch-to-Grub branch
    - Basic refactorization in various areas (variable renames, comment and syntax cleaning, etc.)
- September 1-7:
    - Added shutdown command which allows the kernel to complete and halt the processor (w/o tutorial)
    - Refactored some of the interrupt logic to be more centrally located (w/o tutorial)
    - Added exception descriptions to help debug when a panic occurs (w/o tutorial)
    - Added the cowsay "deadcow" art when the kernel panics (w/o tutorial)
    - Added rudementary PC speaker support. Plays any square wave frequency. (w/o tutorial)
- September 8-14:
    - Added move VGA support for windows, widgets, desktop, etc. Ongoing.
    - Added CPU timer to the InterruptManager (w/o tutorial) (wiki)
    - Accidentally tested and proved that memory protection and it's associated kernel panic works perfectly.
    - Cleaned up more InterruptManager code by moving panic code to a function in stdio.hpp (w/o tutorial)
    - Added RTC as a driver and used code from OSDevWiki to help convert to necessary formats (UTC) (w/o tutorial) (wiki)
    - Moved the CPU timer to a driver to be more inline with the rest of the OS convention
    - Documented what happens when kernelMain returns
    - Removed the panic terminal function since it's been tested and proven to work for a lot of cases (accidentally)
    - Added color to the kernel terminal! (w/o tutorial) (wiki)
    - Refactored part of the kprint function to support a better print method (wiki)
- September 15-21:
    - Completed WYOOS desktop, window, widget and VGA implementation
    - Moved keyboard and mouse handlers into their appropriate classes (w/o tutorial ???)
        - Note: This fixed a serious bug where basically all events were being handled by the driver itself
                instead of the appropriate event handler we would set. It just wasn't obvious now until I
                had another event handler (the desktop) I wanted to use.
    - Fixed issue in shell console where the prompt could be erased using backspace.
    - Cleaned up some of the CPU port implementation. Moved inline ASM to source file instead of header.
    - Function based (parameterless) multitasking has been implemented
    - PIT and RTC now register for interrupts and use the InterruptHandler interface
    - Cleaned up some areas of code and began adding more documentation to areas like InterruptHandler
    - Shell now properly calls member function pointers and lists available commands

### Course Requirements:
Turn-in Requirements:
- Final Report - 8+ pages
- Biweekly Progress Report
- Two proposed lab assignment proposals
- One OS project proposal
- List of resources/bibliography
