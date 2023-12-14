#ifndef HUFMANN_H
#define HUFMANN_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

struct Dictionary{
    unsigned char ascii;
    unsigned char rep;
};

struct Node{
    unsigned char frequency;
    unsigned char data; 
    bool visited;
    struct Node* left;
    struct Node* right;
};

struct Tree{
    unsigned char capacity;
    struct Node** nodes;
};


// Macro to set a specific bit in an unsigned char
#define SET_BIT(byte, bitPosition) ((byte) |= (1U << (bitPosition)))

// Macro to reset a specific bit in an unsigned char
#define RESET_BIT(byte, bitPosition) ((byte) &= ~(1U << (bitPosition)))


struct Tree createHufmannTree(unsigned char text[], unsigned char length);

struct Tree findFrequencies(unsigned char text[], unsigned char length);

void quickSort(struct Tree tree);

void printTree(struct Tree tree);

void deleteTree(struct Tree tree);

struct Dictionary* makeHufmannDictionary(struct Tree tree, unsigned char *length);

void printDictionary(struct Dictionary* dict, unsigned char length);

void deleteDictionary(struct Dictionary* dict);
#endif