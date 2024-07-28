#include <iostream>
#include <unistd.h>

// Bhavikk Patel
// 24MCS0047

int main() {
	std::cout << "Executing ls -l using execlp command" << std::endl;
	execlp("ls", "ls", "-l", (char *)0);
	return 0;
}