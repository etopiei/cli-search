all: @

@:
	g++ -o @ search.cpp

clean:
	rm @

update: @
	mv @ ~/scripts/

install: @
	if [ ! -d "~/scripts" ]; then
		mkdir ~/scripts
	fi
	mv @ ~/scripts/
	@echo 'export PATH=$$PATH:~/scripts' >> ~/.bashrc
