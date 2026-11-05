CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = main.cpp grades.cpp
HDR = grades.h

grades: $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o grades $(SRC)

clean:
	rm -f grades

.PHONY: clean
