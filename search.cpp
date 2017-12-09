#include <iostream>
#include <unistd.h>

std::string helpMenu() {
		std::string menu = "Usage: @ [site] 'search term'";

		menu += "\nSearch term can be in quotes or not.\n";
		menu += "\nSite can be any of the following (ensure to use lowercase):";
		menu += "\n\tso (stack overflow)";
		menu += "\n\tgoogle";
		menu += "\n\twiki (wikipedia)";
		menu += "\n\tyoutube";
		menu += "\n\timdb";
		menu += "\n\tgithub";
		menu += "\n\tfacebook";
		menu += "\n\tnetflix";
		menu += "\n\treddit";
		menu += "\n";

		return menu;
}

int main(int argc, char **argv) {
	if (argc < 2) {
			return 0;
	}
	std::string urlPart1, name;
	if(!strcmp(argv[1], "google")) {
		urlPart1 = "https://google.com/search?dcr=0&q=";
		name = "Google";
	} else if(!strcmp(argv[1], "wiki")) {
			urlPart1 = "https://en.wikipedia.org/w/index.php?search=";
			name = "Wikipedia";
	} else if(!strcmp(argv[1], "youtube")) {
			urlPart1 = "https://www.youtube.com/results?search_query=";
			name = "YouTube";
	} else if(!strcmp(argv[1], "imdb")) {
			urlPart1 = "https://www.imdb.com/find?q=";
			name = "IMDB";
	} else if(!strcmp(argv[1], "github")) {
			urlPart1 = "https://github.com/search?q=";
			name = "GitHub";
	} else if(!strcmp(argv[1], "so")) {
			urlPart1 = "https://stackoverflow.com/search?q=";
			name = "Stack Overflow";
	} else if(!strcmp(argv[1], "help")) {
			std::cout << helpMenu();
			return 0;
	} else if(!strcmp(argv[1], "facebook")) {
			urlPart1 = "https://www.facebook.com/search/top?q=";
			name = "Facebook";
	} else if(!strcmp(argv[1], "netflix")) {
			urlPart1 = "https://www.netflix.com/search?q=";
			name = "Netflix";
	} else if(!strcmp(argv[1], "reddit")) {
			urlPart1 = "https://www.reddit.com/search?q=";
			name = "Reddit";
	} else {
			std::cout << "Invalid option" << std::endl;
			std::cout << helpMenu();
			return 0;
	}

	std::string search(argv[2]);
	for(int i = 3; i < argc; i++) {
			search = search + '+' + argv[i];
	}
	for(int i = 0; i < search.length(); i++) {
		if(search[i] == ' ') {
				search[i] = '+';
		}
	}

	std::string url = urlPart1 + search;
	int pid = fork();
	if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
	} else if (pid == 0) {
		std::cout << "*Searching " << name << "*" << std::endl;
		execlp("open", "open", url.c_str(), NULL);
	} else {
		std::cerr << "Failed fork" << std::endl;
	}
    return 0;
}
