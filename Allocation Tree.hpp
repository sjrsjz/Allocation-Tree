#pragma once
#include <vector>
#include <ctype.h>
#include <iostream>
#include <string>
class AllocationTree {
    std::vector<bool> allocated{};
public:
    AllocationTree(size_t size) {
        // Initialize the tree with the given size
        // The tree is represented as a binary tree
        // The root is at index 0
        // The left child of a node at index i is at index 2 * i + 2
        // The right child of a node at index i is at index 2 * i + 3
        // The parent of a node at index i is at index (i - 2) / 2
        // The tree is represented as an array of booleans
        // If the node is allocated, the value is true
        // If the node is free, the value is false
        // The tree is initialized with all nodes free
        // The tree is initialized with the given size
        // The tree is initialized with the smallest power of 2 that is greater than or equal to the given size
        allocated.resize(size * 2, false);
    }
    void print_(){
        // Print the tree
        // The tree is printed as a binary tree
        // The tree is printed as a list of booleans
        // If the node is allocated, the value is 1
        // If the node is free, the value is 0
        // The tree is printed as a list of booleans
        std::cout << "Tree: ";
        int level = 0;
        // print Tree as:
        //          L
        //      R       F
        //    F   E   F   F
        //
        // L: Left child have empty space
        // R: Right child have empty space
        // F: Full
        // E: Empty
        
        size_t k = allocated.size();
        while (k > 0)
        {
            k >>= 1;
            level++;
        }
        std::cout << "Level: " << level - 1 << std::endl;
        size_t index = 0;
        for(int i = 0; i < level; i++){
            std::string s = " ";
            // tab
            std::string line = "";
            for(int j = 0; j < level - i - 1; j++){
                s += s;
            }
            s=s.substr(0, s.size() - 1);
            for(int j = 0; j < (1 << i); j++){
                if (index >= allocated.size())
                {
                    break;
                }
                if(allocated[index] && allocated[index + 1]){
                    line += "F";
                } else if(allocated[index]){
                    line += "L";
                } else if(allocated[index + 1]){
                    line += "R";
                } else {
                    line += "E";
                }
                line += s;
                index += 2;
            }
            std::cout << line << std::endl;
        }


        std::cout << std::endl;
    }
    intptr_t allocate(){
        // Find the first free block
        // If no free block is found, return -1

        if(allocated.empty()) return -1;
        if(allocated[0] && allocated[1]) return -1;
        size_t index = 0;
        while(!(allocated[index] && allocated[index + 1])){
            if(!allocated[index] && !allocated[index + 1]){
                allocated[index] = true; // Mark as allocated and redirect to the left child
                // rollback to the parent
                if (index == 0)
                    return index >> 1;
                if ((index + 2) * 2 - 2 >= allocated.size() || (index + 2) * 2 -2 >= allocated.size())
                {
                    allocated[index + 1] = true;
                }
                size_t temp = index;
                while (index > 0 && allocated[index] && allocated[index + 1])
                {
                    index = (((index >> 1) - 1) >> 1) << 1;
                    if (allocated[index])
                    {
                        allocated[index + 1] = true;
                        allocated[index] = (index + 2) * 2 >= allocated.size();
                    }
                    else
                    {
                        allocated[index] = true;
                    }
                }                
                return temp >> 1;
            }
            if(allocated[index] && allocated[index + 1]){
                return -1;
            } 
            size_t last_index = index;
            if(allocated[index]){
                index = (index + 2) * 2 - 2; // Locate the left child
            } else {
                index = (index + 2) * 2; // Locate the right child
            }
        }
        
        return -1;
    }
    void deallocate(intptr_t index){
        if (index < 0)
            return;

        size_t temp = index;
        // Adjust the tree and rollback to the parent
        size_t last_index = index + 1;
        index = (index + 1) >> 1;

        while (index > 0)
        {
            size_t leftChildIndex = index * 2 - 2;
            size_t rightChildIndex = index * 2 - 1;

            // Ensure we do not access out of bounds
            if (leftChildIndex >= allocated.size() || rightChildIndex >= allocated.size())
                break;

            if (allocated[leftChildIndex] || allocated[rightChildIndex])
            {
                if (last_index == index * 2)
                {
                    allocated[leftChildIndex] = true;
                    allocated[rightChildIndex] = false;
                }
                else if (last_index == index * 2 + 1 && !(allocated[leftChildIndex] && !allocated[rightChildIndex]))
                {
                    allocated[leftChildIndex] = false;
                    allocated[rightChildIndex] = true;
                }
            }

            last_index = index;
            index = index >> 1;
        }

        // Reset the children of the original node
        // Ensure we do not access out of bounds
        if (temp * 2 < allocated.size() && (temp * 2 + 1) < allocated.size())
        {
            allocated[temp * 2] = false;
            allocated[temp * 2 + 1] = false;
        }
    }
};