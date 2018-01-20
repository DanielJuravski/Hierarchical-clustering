#------------------------------------------------------------------------------

SOURCE=main.cpp HierarchicalClustering.cpp HierarchicalClustering.h
MYPROGRAM=a.out

CC= g++

#------------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o $(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)
