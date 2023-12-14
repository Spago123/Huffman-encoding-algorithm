#include "../Inc/hufmann.h"

// Swap two nodes
static void swap(struct Node* a, struct Node* b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
static int partition(struct Node *arr[], int low, int high) {
    unsigned char pivot = arr[high]->frequency;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->frequency > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort algorithm
static void quicksort(struct Node *arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

/**
 * @brief Function used to check if a node given via the name letter is already in the tree
 * 
 * @param tree 
 * @param letter 
 * @return true 
 * @return false 
 */
static char checkForNodeInTree(struct Tree tree, unsigned char letter){
    for(unsigned char i = 0; i < tree.capacity; i++){
        if(tree.nodes[i]->data == letter) return i;
    }
    return -1;
}

/*static struct Node* findMin(struct Tree tree){
    unsigned char min = 0;
    for(unsigned char i = 0; i < tree.capacity; i++){
        if(tree.nodes[i] != NULL && tree.nodes[i]->data < tree.nodes[min]->data){
            min = i;
        }
    }
    struct Node* helper = (struct Node*)malloc(sizeof(struct Node));
    helper->data = tree.nodes[min]->data;
    helper->frequency = tree.nodes[min]->frequency;
    helper->left = NULL;
    helper->right = NULL;
    free(tree.nodes[min]->data);
    tree.nodes[min] = NULL;
    return helper;
}*/

struct Tree findFrequencies(unsigned char text[], unsigned char length){
    struct Node** nodes = (struct Node**)malloc(sizeof(struct Node*));
    unsigned char capacity = 0;
    unsigned char freq = 0;
    for(unsigned char i = 0; i < length; i++){
        char index;
        if((index = checkForNodeInTree((struct Tree){capacity, nodes}, text[i])) != -1){
            /// Node is in the tree, now we increase its frequency
            nodes[index]->frequency++;
        }else{
            nodes = (struct Node**)realloc(nodes, (capacity + 1) * sizeof(struct Node*));
            nodes[capacity] = (struct Node*)malloc(sizeof(struct Node));
            nodes[capacity]->data = text[i];
            nodes[capacity]->frequency = 1;
            nodes[capacity]->left = NULL;
            nodes[capacity]->right = NULL;
            nodes[capacity]->visited = false;
            capacity++;
        }
    }
    return (struct Tree){capacity, nodes};
}

struct Tree createHufmannTree(unsigned char text[], unsigned char length){
    unsigned char cnt = 0;
    struct Tree tree = findFrequencies(text, length);
    quickSort(tree);
    while (tree.capacity > 1){
        struct Node* node = (struct Node*)malloc(sizeof(struct Node*));
        node->data = tree.nodes[tree.capacity - 1]->data;
        node->frequency = tree.nodes[tree.capacity - 1]->frequency + tree.nodes[tree.capacity - 2]->frequency;
        node->left = tree.nodes[tree.capacity - 1];
        node->left = tree.nodes[tree.capacity - 1];
        node->right = tree.nodes[tree.capacity - 2];
        free(tree.nodes[tree.capacity - 1]);
        free(tree.nodes[tree.capacity - 2]);
        tree.capacity--;
        tree.nodes[tree.capacity - 1] = node;
        printf("Trenutni kapacitet: %d\n", tree.capacity);
        quickSort(tree);
        printTree(tree);
    }
    
    return tree;
}

void printTree(struct Tree tree){
    for(unsigned char i = 0; i < tree.capacity; i++){
        printf("%c :=  %d\n", tree.nodes[i]->data, tree.nodes[i]->frequency);
    }
}

void deleteTree(struct Tree tree){
    for(unsigned char i = 0; i < tree.capacity; i++){
        free(tree.nodes[i]);
    }
    free(tree.nodes);
}

void quickSort(struct Tree tree){
    quicksort(tree.nodes, 0, tree.capacity - 1);
}


static bool checkIfInDict(struct Dictionary* dict, unsigned char size, unsigned char letter){
    for(unsigned char i = 0; i < size; i++){
        if(dict[i].ascii == letter)
            return true;
    }
    return false;
}

struct Dictionary* makeHufmannDictionary(struct Tree tree, unsigned char* length){
    struct Node* endOfLine = (struct Node*)malloc(sizeof(struct Node));
    unsigned char cnt = 0;
    unsigned char value = 0x00;
    unsigned char bitPos = 0;
    struct Dictionary* dict = (struct Dictionary*)malloc(sizeof(struct Dictionary));
    struct Node* curr = tree.nodes[0];
    while(curr != NULL){
/*         if(curr->left == NULL && curr->right == NULL && checkIfInDict(dict, cnt, curr->data)){
            if(curr == tree.nodes[0]) break;
            free(curr);
            curr = NULL;
            value = 0x00;
            bitPos = 0;
            curr = tree.nodes[0];
        }else */ /* if(curr->left == NULL && curr->right == NULL){
            /// Found a node
            printf("found it");
            dict = (struct Dictionary*)realloc(dict, (cnt + 1)*sizeof(struct Dictionary));
            dict[cnt].ascii = curr->data;
            dict[cnt].rep = value;
            value = 0x00;
            bitPos = 0;
            free(curr);
            curr = NULL;
            curr = tree.nodes[0];
            cnt++;
        }else */if(curr->left != NULL){
            /// Go left
            printf("left\n");
            curr = curr->left;
            RESET_BIT(value, bitPos);
            bitPos++;
            break;
        }else if(curr->right != NULL){
            /// Go right
            printf("right\n");
            curr = curr->right;
            SET_BIT(value, bitPos);
            bitPos++;
            break;
        }

    }
    (*length) = cnt;
    return dict;
}

void printDictionary(struct Dictionary* dict, unsigned char length){
    for(unsigned char i = 0; i < length; i++){
        printf("%c := %d\n", dict[i].ascii, dict[i].rep);
    }
}

void deleteDictionary(struct Dictionary* dict){
    free(dict);
}