#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <grades_file>\n";
        return 1;
    }
    std::cout << "Grades report\n";
    return 0;
}
