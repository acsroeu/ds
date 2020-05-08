#include "iostream"
using namespace std;
struct HeapItem
{
	int priorityKey;
	int data;
};
struct Heap
{
	HeapItem *elements;
	int noElements;
	int arrayDim;
};
void initHeap(Heap& h, int size)
{
	h.arrayDim = size;
	h.noElements = 0;
	h.elements = (HeapItem*)malloc(sizeof(HeapItem)*size);
}
HeapItem* createHeapItem(int key, int data)
{
	HeapItem* item = (HeapItem*)malloc(sizeof(HeapItem));
	item->data = data;
	item->priorityKey = key;
	return item;
}
void ReheapUp(Heap heap, int first, int back) // max heap
{
	int parent;
	HeapItem temp;

	// Check base case in recursive calls.  If bottom's index is greater
	// than the root index we have not finished recursively reheaping.
	if (back > first)
	{
		parent = (back - 1) / 2;
		if (heap.elements[parent].priorityKey < heap.elements[back].priorityKey)
		{
			// Swap these two elements
			temp = heap.elements[parent];
			heap.elements[parent] = heap.elements[back];
			heap.elements[back] = temp;
			// Make recursive call till reheaping completed
			ReheapUp(heap, first, parent);
		}
	}
}
void ReheapDown(Heap heap, int first, int back)
{
	int maxChild;
	int rightChild;
	int leftChild;
	HeapItem temp;

	leftChild = first * 2 + 1;          // Get index of root's left child
	rightChild = first * 2 + 2;          // Get index of root's right child

										 // Check base case in recursive calls.  If leftChild's index is less
										 // than or equal to the bottom index we have not finished recursively 
										 // reheaping.
	if (leftChild <= back)
	{
		if (leftChild == back)          // If this root has no right child then 
		{
			maxChild = leftChild;     //     leftChild must hold max key
		}
		else
		{     // Get the one lowest in the tree (highest index in the array)
			if (heap.elements[leftChild].priorityKey <= heap.elements[rightChild].priorityKey)
				maxChild = rightChild;
			else
				maxChild = leftChild;
		}
		if (heap.elements[first].priorityKey < heap.elements[maxChild].priorityKey)
		{
			// Swap these two elements
			temp = heap.elements[first];
			heap.elements[first] = heap.elements[maxChild];
			heap.elements[maxChild] = temp;
			// Make recursive call till reheaping completed
			ReheapDown(heap, maxChild, back);
		}
	}
}
void Enqueue(Heap& heap, int key, int data)
{
	HeapItem *temp = createHeapItem(key, data);
	if (heap.noElements < heap.arrayDim)
	{
		heap.elements[heap.noElements] = *temp; // Copy item into array
		free(temp);
		ReheapUp(heap, 0, heap.noElements);
		heap.noElements++;
	}
}
HeapItem* Dequeue(Heap& heap)
{
	if (heap.noElements != 0)
	{
		HeapItem *temp = createHeapItem(heap.elements[0].priorityKey, heap.elements[0].data);
		heap.noElements--;
		// Copy last item into root
		heap.elements[0] = heap.elements[heap.noElements];
		// Reheap the tree
		ReheapDown(heap, 0, heap.noElements - 1);
		return temp;
	}
	return NULL;
}
void printHeap(Heap heap)
{
	for (int i = 0; i < heap.noElements; i++)
	{
		cout << "Heap element " << i + 1 << ". key=" << heap.elements[i].priorityKey << "  data=" <<
			heap.elements[i].data << endl;
	}
}
void main()
{
	Heap heap;
	initHeap(heap, 10);
	Enqueue(heap, 123, 1.23);
	Enqueue(heap, 345, 3.45);
	Enqueue(heap, 234, 2.34);
	Enqueue(heap, 678, 6.78);
	Enqueue(heap, 456, 4.56);
	Enqueue(heap, 567, 5.67);
	Enqueue(heap, 789, 7.89);
	printHeap(heap);
	HeapItem* temp;
	while ((temp = Dequeue(heap)) != NULL)
	{
		cout << "Dequeueing " << temp->priorityKey << endl;
		delete temp; // delete this one
					 // See what we have left
		cout << "Elements in the heap.\n";
		printHeap(heap);
		cout << endl;
	}
	Enqueue(heap, 789, 7.89);
	Enqueue(heap, 567, 5.67);
	printHeap(heap);
	while ((temp = Dequeue(heap)) != NULL)
	{
		cout << "Dequeueing " << temp->priorityKey << endl;
		delete temp; // delete this one
					 // See what we have left
		cout << "Elements in the heap.\n";
		printHeap(heap);
		cout << endl;
	}
}