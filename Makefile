all: search

search:
	g++ -o search search.cpp

clean:
	rm ~/scripts/search
	rm ~/scripts/sites.txt

update: search
	mv search ~/scripts/

install: search
	mv search ~/scripts
	cp sites.txt ~/scripts
