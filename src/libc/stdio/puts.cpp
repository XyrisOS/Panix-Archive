#include <libc/stdio.hpp>
// TODO: We need to fix these functions to actually follow the
//		 standard C / C++ format.
/**
 * @brief Put a string onto the display
 * 
 * @param string 
 * @return int 
 */
int puts(const char* string) {
	printf(string);
	return 0;
}