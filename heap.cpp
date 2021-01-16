#include <iostream>

using namespace std;

class MinHeap {
    int* harr;
    int capacity;
    int heap_size;
public:
    MinHeap(int capacity);

    void heapify(int root_idx);

    int parent(int i){return (i - 1) / 2;}

    int left(int i);
    int right(int i);

    void swap(int* a, int* b);
    void insertKey(int key);

    int extractMin();
    int getMin();
    void deleteKey(int key);

    void decreaseKey(int i, int new_val);
};

/* If the argument of this member function is named 'capacity', 
it would collide with the 'capacity' data member, 
so the data member won't be initialized correctly. */
MinHeap::MinHeap(int capacity){
    this->capacity = capacity;
    heap_size = 0;
    harr = new int[capacity];
}

void MinHeap::swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int MinHeap::left(int parent){
    return parent * 2 + 1;
}

int MinHeap::right(int parent){
    return parent * 2 + 2;
}

// Insert the key at the end of the array and then bubble it up until it doesn't violate the invariant.
void MinHeap::insertKey(int key) {
    if(heap_size < capacity){
        harr[heap_size] = key;
        int i = heap_size;
        while(i > 0 && harr[i] < harr[parent(i)]){
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
        heap_size++;
    }
    else cout << "\nOverflow: Could not insertKey\n"; 
    // cout << "Heap size = " << heap_size <<endl;
}

// Assume only one violation exists in the subtree rooted at the given index.
// We need to know exactly which of the parent and the two children is the largest, 
// so that we can continue heapifying.
void MinHeap::heapify(int root_idx){
    int smallest = root_idx;
    int l = left(root_idx);
    int r = right(root_idx);
    // cout << "Heap size = " << heap_size <<endl;
    // for(int i = 0; i < heap_size; i++)
    //     cout << " " << harr[i];
    // cout <<endl;
    if(l <= heap_size - 1 && harr[root_idx] > harr[l])
        smallest = l;

    if(r <= heap_size - 1 && harr[r] < harr[smallest])
        smallest = r;

    // cout << "Smallest idx is: " << smallest <<endl;
    if(smallest != root_idx){
        swap(&harr[smallest], &harr[root_idx]);
        heapify(smallest);
    }
}

int MinHeap::getMin(){
    return harr[0];
}

int MinHeap::extractMin(){
    // Store the minimum and swap the last nonempty element with the root of the tree.
    int min = harr[0];
    // cout << "Min = " << min <<endl;
    swap(&harr[heap_size - 1], &harr[0]);
    // cout << "swapped 1st and " << heap_size << "th element" <<endl;
    heap_size--;
    
    // Fix the invariant violation for the tree.
    heapify(0);
    return min; 
}

int main(){
    int capacity = 20;
    MinHeap myHeap(capacity);

    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_variable = std::rand();
    std::cout << "Random value on [0 " << RAND_MAX << "]: " 
              << random_variable << '\n';
 
    int RANGE_MAX = 100;
    // roll 200-sided dice 20 times
    for (int n=0; n != capacity; ++n) {
        int x = RANGE_MAX + 1;
        while(x > RANGE_MAX) 
            x = 1 + std::rand()/((RAND_MAX + 1u)/RANGE_MAX);  // Note: 1+rand()%6 is biased
        // std::cout << x << ' ';
        myHeap.insertKey(x);
    }

    // myHeap.insertKey(9);
    // myHeap.insertKey(1);
    // myHeap.insertKey(65);
    // myHeap.insertKey(3);
    // myHeap.insertKey(36);
    // myHeap.insertKey(18);
    // myHeap.insertKey(22);
    // myHeap.insertKey(12);

    // cout << "Min is: " << myHeap.getMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    // cout << "Pull out min is: " << myHeap.extractMin() << endl;
    for( int i = 0; i < capacity; i++){
        cout << myHeap.extractMin() << " ";
    }

    return 0;
}


