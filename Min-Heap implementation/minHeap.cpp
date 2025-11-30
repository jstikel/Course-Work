#include "minHeap.h"

minHeap :: minHeap(vector<int> data){
    for (auto num : data){ //Runs through all elements in data
        heap.push_back(num); //Works similarly to insert
        siftUp(heap.size() - 1); //Then simply sift up
    }
}

void minHeap :: siftUp(int pos){
    while(pos > 0){ //Keep us in bounds

        int parent = (pos - 1) / 2;
        if (heap[parent] > heap[pos]){ //If the parent is greater than the child
            swap(heap[pos], heap[parent]);
            pos = parent; //We continue from the parent position and restart the loop
        }
        else{
            break;
        }
    }
}

void minHeap :: siftDown(int pos){
    int size = heap.size();

    while (true){
        int leftChild = 2 * pos + 1;
        int rightChild = 2 * pos + 2;
        int smallest = pos;

        if (leftChild < size && heap[leftChild] < heap[smallest]){
            smallest = leftChild; //We check if the left child is smaller
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]){
            smallest = rightChild; //We check if the right child is smaller
        }

        //If neither are smaller than we are done and the loop can break
        if (smallest == pos){
            break;
        }
        swap(heap[pos], heap[smallest]); //Then we swap the head and the smaller of the two nodes
        pos = smallest; //And continue down the tree
    }
}

void minHeap :: insert(int val){
    heap.push_back(val); //First we add our new value to the bottom of the heap

    //Then we simply use our siftup function
    //we know its in the last position because it was just added to the vector
    siftUp(heap.size() - 1);
}

int minHeap :: removeMin(){
    int minVal = heap[0];

    heap[0] = heap.back(); //Set the final value to the top of the heap and sift down
    heap.pop_back();
    if (!heap.empty()){
        siftDown(0);
    }
    return minVal; //Return our minimum value
}