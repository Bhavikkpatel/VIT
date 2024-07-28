#include <iostream>
#include <unistd.h>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

// Bhavikk Patel
// 24MCS0047

int main () {
	pid_t pid = fork();
	
	if (pid > 0) {
		std::cout << "Parent process ID ::: " << getpid() << std::endl;
		std::cout << "Child process ID ::: " << pid  << std::endl;
		sleep(5);
		std::cout << std::time(0) << std::endl;
		std::string cmd = "ps -p " + pid;
		std::cout << cmd.c_str() << std::endl;
		system("ps");
		wait(NULL);
		std::cout << "Parent process cleared the zombie child process with PID ::: " << pid << std::endl;
		execl("/bin/ps", "-p " + pid, (char *)0);
	} else if (pid == 0) {
		std::cout << "Exiting child process" << " time ::: " << std::time(0)  << std::endl;
		exit(0);
	} else {
		std::cout << "Failed" << std::endl;
		return 1;
	}
	return 0;
}
