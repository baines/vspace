.PHONY: engine clean

all: 
	$(MAKE) -C src
win: 
	$(MAKE) -C src -f makefile.win
cleanwin:
	$(MAKE) clean -C src -f makefile.win
clean:
	$(MAKE) clean -C src
