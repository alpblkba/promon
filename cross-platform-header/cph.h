//
// Created by Alp Bolukbasi on 17.12.25.
//

#ifndef PROMON_CPH_H
#define PROMON_CPH_H


#include <iostream>

class System {
public:
    void printOS() {
#ifdef __APPLE__
        std::cout << "Running on macOS (UNIX)\n";
#elif __linux__
        std::cout << "Running on Linux\n";
#endif
    }

    double getMemoryUsage();
};

#endif //PROMON_CPH_H

