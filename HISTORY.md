## CS-3950 Progress Report History
Update Progress (Starting August 2019)
- August 28-30:
    - Interrupt handler manager was refactored to use function pointers with loops
    - Keyboard driver was refactored to use allow shell access (added key buffer)
    - Kernel level shell (Basch) was further implemented
    - Basic terminal commands were added for debugging
    - Kernel panics no longer infinitely cycle text on screen. (Halt asm is now called)
    - VGA drivers were implemented in a hack-ish manner (lots of temporary code)
    - Unused kernel libc functions and files were removed to slim kernel size
    - Ported some useful string functions from the master branch into the Switch-to-Grub branch
    - Basic refactorization in various areas (variable renames, comment and syntax cleaning, etc.)

- September 1-7:
    - Added shutdown command which allows the kernel to complete and halt the processor
    - Refactored some of the interrupt logic to be more centrally located
    - Added exception descriptions to help debug when a panic occurs
    - Added the cowsay "deadcow" art when the kernel panics
    - PLANNED: More VGA support

### Course Requirements:
Turn-in Requirements:
- Final Report - 8+ pages
- Biweekly Progress Report
- Two proposed lab assignment proposals
- One OS project proposal
- List of resources/bibliography
