OBJECTS := main.o 
OUTPUT := apache
CXX := g++
CPPFLAGS := -ansi -pedantic -Wall -std=c++11

main: $(OBJECTS)
	$(CXX) -o $(OUTPUT) $(OBJECTS)

debug: CPPFLAGS := $(CPPFLAGS) -DMAP
debug: main

test: CPPFLAGS := $(CPPFLAGS) -DTEST
test: main

$(OBJECTS): $(@: .o = .cpp)
	$(CXX) -c $(patsubst %.o, %.cpp, $@) $(CPPFLAGS) 

clean:
	rm -rf $(OBJECTS) $(OUTPUT)

help:
	@echo "Pour générer un exécutable : make main"
	@echo "Pour générer un exécutable en mode debug : make debug"
	@echo "Pour supprimer les fichiers compilés et l'exécutable : make clean"
