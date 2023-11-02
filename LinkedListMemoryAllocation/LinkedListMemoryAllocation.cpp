#include <iostream>
class Tracker
{
public:
	Tracker();
	~Tracker();

	void heap_walk();

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
void* Tracker::operator new(size_t size)
{
	//For Reference
	std::cout << "Class New Operator Overloading" << std::endl;

	//Store Requested Bytes
	void* p = malloc(size);
	return p;
}

void Tracker::operator delete(void* pMem)
{
	std::cout << "Class Delete Operator Overloading" << std::endl;
	free(pMem);
}

//Used for DMA  
struct footer
{
	char padding;
};
Tracker* main_tracker;
static int node_count;
//In this, the node from how we create linked lists enacts as the header for
//DMA
struct Node
{
	Tracker* p_tracker;
	Node* next;

	Node* previous;
	int key; // Used to search element
	int block_size; //int for demonstration purposes

};


//Using pointer artithemtics, will return the address we want to point to.
//We will use this to then add to linked list.
Node* return_header_address(void* pMem)
{
	//Same way we locate the pointer address.
	Node* heap_segment = (Node*)((char*)pMem - sizeof(Node));

	return heap_segment;
}
Node* insert_front(struct Node* current_head, int new_data)
{
	
	int* new_block = new int(new_data);
	Node* new_head = return_header_address(new_block);

	new_head->key = new_data;
	//If true, we create first node, being first head
	if (current_head == 0x0000000000000000)
	{
		
		current_head = new_head;
		return new_head;


	}


	if (current_head != nullptr)
	{
		current_head->previous = new_head;
		new_head->next = current_head;
		new_head->previous = nullptr;

	}
	current_head = new_head;
	return new_head; 
}
Node* insert_back(struct Node** head, int new_data)
{

	int* new_block = new int(new_data);
	Node* new_node = return_header_address(new_block);
	new_node->key = new_data;

	
	Node* last = *head;

	new_node->next == nullptr;

	while (last->next != nullptr)
	{
		last = last->next;

	}


	last->next = new_node;
	new_node->previous = last;
	return new_node;
}
Node* insert_between(struct Node* previous_node, int new_data)
{
	if (previous_node == nullptr)
	{
		std::cout << "Given previous node cannot be nullptr\n";
		return nullptr;
	}

	int* new_block = new int(new_data);
	Node* new_node = return_header_address(new_block);
	new_node->key = new_data;

	new_node->next = previous_node->next;

	previous_node->next = new_node;

	new_node->previous = previous_node;

	if (new_node->next != nullptr)
	{
		new_node->next->previous = new_node;
	}

	return new_node;

}
void delete_node(Node*& head, int key)
{
	Node* temp_head = head;
	Node* delete_node = nullptr;


	Node* prev_temp = nullptr;
	Node* next_temp = nullptr;

	while (temp_head->key != key)
	{
		temp_head = temp_head->next;
	}

	if (temp_head->key == key)
	{
		std::cout << key << " node will be deleted\n";
		if (temp_head->key == head->key)
		{
			Node* new_head = temp_head->next;
			head = new_head;
		}
		else
		{
			delete_node = temp_head;
			prev_temp = delete_node->previous;

			if (prev_temp != nullptr)
			{
				prev_temp->next = next_temp;

			}

			next_temp = delete_node->next;
			if (next_temp != nullptr)
			{
				next_temp->previous = prev_temp;

			}
		}

	}

	free(delete_node);

}
bool search_list(Node* head, int key)
{
	Node* current_node = head;
	while (current_node != nullptr)
	{
		if (current_node->key == key)
		{
			return true;
		}
	}
	return false;
}
//Global New/Delete Overload Operators

//This will initialise the memory block now stored as a node, however we now need
//to find a way to insert this memory block to linked list.
//Doing it in here isnt suitable.
void* operator new (size_t requested)
{

	//For Reference
	std::cout << "New Operator Overloading" << std::endl;

	//Total Size of Memory block
	size_t total = requested + sizeof(Node) + sizeof(footer);

	//Create Block
	char* block = (char*)malloc(total);

	//Assign block to this struct, allows us to manage block
	Node* heap_segment = (Node*)block;
	heap_segment->p_tracker = main_tracker;
	heap_segment->block_size = total;
	//Create memory address location for fotter, creates padding between blocks of heap.
	void* p_footer = block + sizeof(Node) + requested;

	footer* heap_footer = (footer*)p_footer;
	heap_footer->padding = 1;

	heap_segment->next = nullptr;
	heap_segment->previous = nullptr;

	void* data_segment = block + sizeof(Node);
	//We must return data segment (in middle of block), this is where
	//we want to store data itself, we can use this address with pointer arithmetics to decrement to header address.
	return data_segment;

}

void operator delete (void* pMem)
{
	std::cout << "Delete Operator Overloading" << std::endl;
	//Locate memory Address at start of heap segment, we do this since we pass in the data segment address.
	Node* heap_segment = (Node*)((char*)pMem - sizeof(Node));
	footer* heap_footer = (footer*)((char*)pMem + heap_segment->block_size);
	free(heap_segment);

}

int main()
{

	main_tracker = new Tracker();

	//Enacts as our current head
	Node* num1_node = insert_front(nullptr, 10);
	Node* num2_node = insert_front(num1_node, 15);
	Node* num3_node = insert_back(&num2_node, 20);
	Node* node4_node = insert_between(&num1_node , 25);
	return 0;
}
