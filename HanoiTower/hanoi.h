#ifndef hanoi_hpp
#define hanoi_hpp

#include <stdio.h>
#include <vector>
#include <cmath>

class Hanoi {
private:
    int discs;
    int num_towers;
    std::vector<std::vector<int>> towers;
    int moves = 0;
public:
    Hanoi(int, int);
    bool is_valid();
    void print();

    void moveTop(int, int);
    void move(int n, int s, int d, int m);
    int get_moves();
    void set_moves();
};

class Hanoi4 {
private:
    int discs;
    int num_towers;
    std::vector<std::vector<int>> towers;
    int moves = 0;
public:
    //Constructors
    Hanoi4(int, int);

    //Getters
    int get_moves();

    //Setters
    void set_moves();

    //Auxillary Functions
    void print();
    bool is_valid();
    void moveTop(int, int);
    void move(int n, int s, int d, int m1, int m2);
    void tower_of_three(int n, int s, int d, int m);
    int calculate_k(int n);

};

#endif /* hanoi_hpp */
#pragma once
