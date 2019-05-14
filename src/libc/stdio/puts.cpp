#include <libc/stdio.hpp>
// TODO: We need to fix these functions to actually follow the
//		 standard C / C++ format.
int puts(const char* string) {
	kprint(string);
	return 0;
}