#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>

std::string helpMenu(std::vector<std::string> *sites) {
		std::string menu = "Usage: @ [site] 'search term'";

		menu += "\nSearch term can be in quotes or not.\n";
		menu += "\nSite can be any of the following (ensure to use lowercase):";
		for(int i = 0; i < sites->size(); i+=3) {
				menu += "\n\t" + (*sites)[i]; 
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
	confFile.open("sites.txt");

	//file will be structured with Name\nURL Start\n etc...
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
	} else {
		int index = -1;
		for(int i = 0; i < sites.size(); i+=3) {
			//get the correct details if the name matches.
			std::string siteArgument = argv[1];
			if(siteArgument == sites[i]) {
					found = true;
					name = sites[i+1];
					urlPart1 = sites[i+2];
			}
		}
	}

	if(!found) {
			std::cout << "Invalid option" << std::endl;
			std::cout << helpMenu(&sites) << std::endl;
			return 0;
	}

	std::string search(argv[2]);
	//here ensure + character and others like it are escaped (eg. searching c++)
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
