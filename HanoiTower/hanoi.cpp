#include "hanoi.h"
#include <iostream>

Hanoi::Hanoi(int n, int m) {
    discs = n;
    num_towers = m;
    for (int i = 0;i < num_towers;i++) {
        std::vector<int> temp;
        towers.push_back(temp);
    }
    for (int i = discs;i > 0;i--) {
        towers[0].push_back(i);
    }
}

void Hanoi::print() {
    for (int i = 0;i < num_towers;i++) {
        std::cout << "Tower " << i + 1 << " contains: [ ";
        std::vector<int>::iterator it;
        for (it = towers[i].begin();it != towers[i].end();it++) {
            std::cout << *it << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "The Number of Moves= " << get_moves() << std::endl;
}
int Hanoi::get_moves() {
    return moves;
}
void Hanoi::set_moves() {
    moves++;
}

bool Hanoi::is_valid() {
    for (int i = 0;i < num_towers;i++) {
        if (towers[i].size() > 0) {
            std::vector<int>::iterator it;
            for (it = towers[i].begin();it != towers[i].end() - 1;it++) {
                if (*it < *(it + 1)) {
                    return false;
                }
            }
        }
        else
            continue;
    }
    return true;
}

void Hanoi::moveTop(int s, int d) { // moves the top disk from source tower s to destination tower d (if valid)
    std::cout << "Move disk " << towers[s].back() << " from tower ";
    std::cout << s + 1 << " to tower " << d + 1;
    towers[d].push_back(towers[s].back());
    towers[s].pop_back();
    if (is_valid())
        std::cout << " (Legal move)" << std::endl;
    else
        std::cout << " (Illegal move)" << std::endl;
}

void Hanoi::move(int n, int s, int d, int m) { // this is the recursion.
    // It moves n disks from the source s to the destination d using a "storage" disk m
    if (n == 1) {
        set_moves();
        moveTop(s, d);
    }// if only one disk is to be moved this is the same as moving immediately the top disk from source s to destination d
    else { // if more than one moves, then we recursively break it down into moving n-1 disks first, followed by a single disk later.
        move(n - 1, s, m, d); // notice the change: moving the n-1 disks we use as a new destination the previous "storage"; and the new storage is the previous destination.
        moveTop(s, d);
        set_moves();// this leaves one disk to be moved immediately to the destination.
        move(n - 1, m, d, s); // finally, we move the remaining ones from the storage (where they currently are) to the destination using the original source as the new storage.
    }
}

Hanoi4::Hanoi4(int n, int m) {
    discs = n;
    num_towers = m;
    for (int i = 0;i < num_towers;i++) {
        std::vector<int> temp;
        towers.push_back(temp);
    }
    for (int i = discs;i > 0;i--) {
        towers[0].push_back(i);
    }
}

void Hanoi4::print() {
    for (int i = 0;i < num_towers;i++) {
        std::cout << "Tower " << i + 1 << " contains: [ ";
        std::vector<int>::iterator it;
        for (it = towers[i].begin();it != towers[i].end();it++) {
            std::cout << *it << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "The Number of Moves= " << get_moves() << std::endl;
}
int Hanoi4::get_moves() {
    return moves;
}
void Hanoi4::set_moves() {
    moves++;
}

bool Hanoi4::is_valid() {
    for (int i = 0;i < num_towers;i++) {
        if (towers[i].size() > 0) {
            std::vector<int>::iterator it;
            for (it = towers[i].begin();it != towers[i].end() - 1;it++) {
                if (*it < *(it + 1)) {
                    return false;
                }
            }
        }
        else
            continue;
    }
    return true;
}

void Hanoi4::moveTop(int s, int d) { // moves the top disk from source tower s to destination tower d (if valid)
    std::cout << "Move disk " << towers[s].back() << " from tower ";
    std::cout << s + 1 << " to tower " << d + 1;
    towers[d].push_back(towers[s].back());
    towers[s].pop_back();
    if (is_valid())
        std::cout << " (Legal move)" << std::endl;
    else
        std::cout << " (Illegal move)" << std::endl;
}
int Hanoi4::calculate_k(int n) {
    int k = std::sqrt(2 * n);
    return k;
}
void Hanoi4::tower_of_three(int n, int s, int d, int m) {
    // It moves n disks from the source s to the destination d using a "storage" disk m
    if (n == 0) {
        return;
    }
    if (n == 1) {
        set_moves();
        moveTop(s, d);
    }// if only one disk is to be moved this is the same as moving immediately the top disk from source s to destination d
    else { // if more than one moves, then we recursively break it down into moving n-1 disks first, followed by a single disk later.
        tower_of_three(n - 1, s, m, d); // notice the change: moving the n-1 disks we use as a new destination the previous "storage"; and the new storage is the previous destination.
        moveTop(s, d);
        set_moves();// this leaves one disk to be moved immediately to the destination.
        tower_of_three(n - 1, m, d, s); // finally, we move the remaining ones from the storage (where they currently are) to the destination using the original source as the new storage.
    }

}

void Hanoi4::move(int n, int s, int d, int m1, int m2) { // this is the recursion.
    // It moves n disks from the source s to the destination d using a "storage" disk m
    int k = calculate_k(n);
    if (n == 0) {
        return;
    }

    if (n == 1) {
        set_moves();
        moveTop(s, d);
    }// if only one disk is to be moved this is the same as moving immediately the top disk from source s to destination d
    else { // if more than one moves, then we recursively break it down into moving n-1 disks first, followed by a single disk later.
        move(n - k, s, m1, d, m2);
        // notice the change: moving the n-1 disks we use as a new destination the previous "storage"; and the new storage is the previous destination.
        tower_of_three(k, s, d, m2);
        // this leaves one disk to be moved immediately to the destination.
        move(n - k, m1, d, s, m2); // finally, we move the remaining ones from the storage (where they currently are) to the destination using the original source as the new storage.
    }
}

