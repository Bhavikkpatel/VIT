#include <iostream>
#include <unistd.h>
#include <ctime>

// Bhavikk Patel
// 24MCS0047

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		std::cerr << "failed" << std::endl;
		return 1;
	} else if (pid == 0) {
		std::cout << "child process" << "time ::: " << std::time(0)  << std::endl;
		sleep(15);
		std::cout << "child after 15 sec, time ::: " << std::time(0) << std::endl;
		exit(0);
	} else {
		std::cout << "terminating parent process" << std::endl;
		exit(0);
	}
	return 0;
}