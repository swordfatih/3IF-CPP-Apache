OBJECTS := main.o Analyseur.o Interpreteur.o Statistiques.o
OUTPUT := analog
CXX := g++
CXXFLAGS := -ansi -pedantic -Wall -std=c++11

main: $(OBJECTS)
	$(CXX) -o $(OUTPUT) $^

debug: CXXFLAGS := $(CXXFLAGS) -DMAP
debug: main

%.o: %.c
	$(CXX) -c $(patsubst %.o, %.cpp, $@) $(CXXFLAGS) 

clean:
	rm -rf $(OBJECTS) $(OUTPUT)

help:
	@echo "Pour générer un exécutable : make main"
	@echo "Pour générer un exécutable en mode debug : make debug"
	@echo "Pour supprimer les fichiers compilés et l'exécutable : make clean"
