#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sys/wait.h>
#include <string.h>

void addNewItem() {
		std::string name, shortcut, url;
		std::cout << "What is the name of the site (must be all one word): ";
		std::cin >> name;
		std::cout << "What shortcut would you like to use (must also not contain spaces): ";
		std::cin >> shortcut;
		std::cout << "What is the URL start (eg: https://site.com?query=): ";
		std::cin >> url;

		//write the new site to file
		std::ofstream myFile;
		std::string home = getenv("HOME");
		myFile.open((home + "/scripts/sites.txt").c_str(), std::ios_base::app);
		myFile << shortcut << std::endl;
		myFile << name << std::endl;
		myFile << url << std::endl;
		myFile.close();
}

std::string helpMenu(std::vector<std::string> *sites) {
		std::string menu = "Usage: search [site] 'search term'";

		menu += "\nSearch term can be in quotes or not.\n";
		menu += "\nSite can be any of the following (ensure to use lowercase):";
		for(int i = 0; i < sites->size(); i+=3) {
				menu += "\n\t" + (*sites)[i] + " - (" + (*sites)[i+1] + ")"; 
		}
		menu += "\n";

		return menu;
}

int main(int argc, char **argv) {
	if (argc < 2) {
			return 0;
	}

	//load in urls and names from file
	std::ifstream confFile;
	std::string home = getenv("HOME");
	confFile.open((home + "/scripts/sites.txt").c_str());

	std::vector<std::string> sites;
	std::string fileData;
	for(int n; confFile >> fileData;) {
			sites.push_back(fileData);
	}

	bool found = false;
	std::string urlPart1, name;

	if(!strcmp(argv[1], "help")) {
		std::cout << helpMenu(&sites);
		return 0;
	} else if(!strcmp(argv[1], "add")) {
			addNewItem();
			return 0;
	} else {
		int index = -1;
		for(int i = 0; i < sites.size(); i+=3) {
			//get the correct details if the name matches.
			std::string siteArgument = argv[1];
			if(siteArgument == sites[i]) {
					found = true;
					name = sites[i+1];
					urlPart1 = sites[i+2]; } }
	}

	if(!found) {
			std::cout << "Invalid option" << std::endl;
			std::cout << helpMenu(&sites) << std::endl;
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

	int command = 0;

	#ifdef __APPLE__
		command = 1;
	#endif

	std::string url = urlPart1 + search;
	int pid = fork();
	if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
	} else if (pid == 0) {
		std::cout << "*Searching " << name << "*" << std::endl;
		switch(command) {
			case 0:
				execlp("xdg-open", "xdg-open", url.c_str(), NULL);
				break;
			case 1:
				execlp("open", "open", url.c_str(), NULL);
				break;
		}
	} else {
		std::cerr << "Failed fork" << std::endl;
	}
    return 0;
}
