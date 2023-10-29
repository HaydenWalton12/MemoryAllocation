#include <iostream>

class Tracker
{
public:
	Tracker();
	~Tracker();

	void* operator new(size_t requested);
	void operator delete (void* pMem);
private:

};

Tracker::Tracker()
{
}

Tracker::~Tracker()
{
}
void* Tracker::operator new(size_t requested)
{
	 p1 = malloc(4 * sizeof(int));  // allocates enough for an array of 4 int

	return nullptr;
}
void Tracker::operator delete(void* pMem)
{
}
//Header / memory block forms a linked list, allowing us to rtr
struct memory_block 
{
	Tracker* p_tracker;
	int block_size;
	//Check Value
	int is_allocated;
};

struct footer
{
	char padding;
};

Tracker* main_tracker;
//Global New/Delete Overload Operators
void* operator new (size_t requested)
{
	//For Reference
	std::cout << "New Operator Overloading" << std::endl;
	
	//Total Size of Memory block
	size_t total = requested + sizeof(memory_block) + sizeof(footer);
	
	//Create Block
	char* block = (char*)malloc(total);
	
	//Assign block to this struct, allows us to manage block
	memory_block* heap_segment = (memory_block*)block;
	heap_segment->block_size = total;
	heap_segment->p_tracker = main_tracker;

	//Create memory address location for fotter, creates padding between blocks of heap.
	void* p_footer = block + sizeof(memory_block) + total;

	footer* heap_footer = (footer*)p_footer;
	heap_footer->padding = 1;
	void* data_segment = block + sizeof(memory_block);
	return data_segment;

}

void operator delete (void* pMem)
{
	std::cout << "Delete Operator Overloading" << std::endl;
	//Locate memory Address at start of heap segment, we do this since we pass in the data segment address.
	memory_block* heap_segment = (memory_block*)((char*)pMem - sizeof(memory_block));
	footer* heap_footer = (footer*)((char*)pMem + heap_segment->block_size);
	free(heap_segment);

}

int main()
{
	
	int* num = new int(5);
	delete(num);
	return 0;

	
}
