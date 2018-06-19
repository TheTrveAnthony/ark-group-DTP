# Makefile to build everzthing cuz typping the g++ thing pisses me off.

.SUFFIXES:

# Variables 

g = g++
cv = `pkg-config --cflags --libs opencv`
class = gbtrees/
opti =

# builds

all: start create load predict end

create: create.cpp xtraml.cpp
	$(g) $^ $(cv) -o $(class)$@ -g

load: load.cpp xtraml.cpp
	$(g) $^ $(cv) -o $(class)train

predict: predict.cpp xtraml.cpp
	$(g) $^ $(cv) $(opti) -o $(class)$@




# clean and rebuild 


dir:
	mkdir $(class)

clean:
	rm create train predict 

rebuild: clean all

buildclass: dir all 

#Messages of looooooove

start:
	@echo "\n\n Hola Cabron, let's start cooking this shit.\n\n "

end:
	@echo "\n\n Coffee is ready, enjoy. \n\n "