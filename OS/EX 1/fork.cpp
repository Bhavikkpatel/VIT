#include <iostream>
#include <unistd.h>

// Bhavikk Patel
// 24MCS0047

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		std::cerr << "failed" << std::endl;
	} else if (pid == 0) {
		std::cout << "child" << std::endl;
	} else {
		std::cout << "parent" << std::endl;
	}
	return 0;
}
