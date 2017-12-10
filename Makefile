all: search

search:
	g++ -o search search.cpp

clean:
	rm ~/scripts/search

update: search
	mv search ~/scripts/

install: search
	if [ ! -d "~/scripts" ]; then
		mkdir ~/scripts
	fi
	mv search ~/scripts/
	@echo 'export PATH=$$PATH:~/scripts' >> ~/.bashrc
