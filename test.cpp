#include "Allocation Tree.hpp"
#include <iostream>
#include <vector>
int main(){
    int size = rand() % 1000 + 1;
    AllocationTree tree(size);
    std::vector<bool> allocated(size);
    for(int i = 0; i < 1000000; i++){
        bool free = rand() % 2;
        if(free){
            //std::cout << "Deallocating" << std::endl;
            size_t idx = rand() % size;
            if (allocated[idx]){
                //std::cout << "Deallocated: " << idx << std::endl;
                allocated[idx] = false;
                tree.deallocate(idx);
            } else {
                //std::cout << "Already deallocated" << std::endl;
            }
        } else {
            size_t idx = tree.allocate();
            if(idx != -1){
                //std::cout << "Allocated: " << idx << std::endl;
                if (allocated[idx]){
                    std::cout << "Crash! " << idx << std::endl;
                    tree.print_();
                    return 1;
                } else {
                    allocated[idx] = true;
                }
            } else {
                //std::cout << "Failed to allocate" << std::endl;
            }
        }
        //tree.print_();
        //for(auto a : allocated){
        //    std::cout << a << " ";
        //}
        //std::cout << std::endl;
    }

    return 0;
} 