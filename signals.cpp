#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void signal_handler(int signal_num) {
	cout << "Modi says (" << signal_num << "). \n";

	// terminate program
	exit(signal_num);
}

void signal_handler1(int signal_num) {
	cout << "Rahul says (" << signal_num << "). \n";

	// terminate program
	exit(signal_num);

}

int main() {
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler1);
	// register signal SIGABRT and signal handler
	int count = 0;
	while (true) { 
		// 5 second loop, Ctrl+C to see the handler
		if ( count == 5)
			raise(SIGSEGV);
		cout << "Hello Bashar..." << endl;
		sleep(1);
		count++;
	}
	return 0;
}
