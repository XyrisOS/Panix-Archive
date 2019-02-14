/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void entryTest() {
}

int main() {
    char * video_memory = (char *) 0xb8000;	// Define the VMEM constant
    * video_memory = 'X';					// Print an X to the VMEM
}