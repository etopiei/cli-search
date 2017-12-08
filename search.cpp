#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc < 2) {
			return 0;
	}
	std::string urlPart1 = "https://google.com/search?dcr=0&q=";
	std::string search(argv[1]);
	for(int i = 2; i < argc; i++) {
			search = search + '+' + argv[i];
	}
	for(int i = 0; i < search.length(); i++) {
		if(search[i] == ' ') {
				search[i] = '+';
		}
	}
	std::string url = urlPart1 + search;
	std::cout << url << std::endl;
	int pid = fork();
	if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
	} else if (pid == 0) {
		std::cout << "Searching..." << std::endl;
		execlp("open", "open", url.c_str(), NULL);
	} else {
		std::cerr << "Failed fork" << std::endl;
	}
    return 0;
}
