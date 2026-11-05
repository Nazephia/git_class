CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = main.cpp

grades: $(SRC)
	$(CXX) $(CXXFLAGS) -o grades $(SRC)

clean:
	rm -f grades

.PHONY: clean
