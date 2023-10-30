#include <iostream>
struct Node
{
	int data;
	Node* next;
	Node* previous;

	//Struct Constructor - Can be called to initialise
	//member variables, once we create node variable, we can call this.

	//Default Constructor
	Node(int d) : data(d), next(nullptr), previous(nullptr)
	{}

};

//Insert new node 
void insert_back(Node** node, int data)
{
	Node* new_node = new Node(data);

	if ((*node)->next == nullptr)
	{
		new_node->previous = (*node);

	}


}

//Insert new node with data in front of list
void insert_front(Node** current_node, int data)
{
	//Creates New Node
	Node* new_node = new Node(data);
	
	//Places current node infront of new node
	new_node->next = (*current_node);

	//If list is not empty
	if ((*current_node) != nullptr)
	{
		(*current_node)->previous = new_node;
	}

	//Point head to new node
	(*current_node) = new_node;
}
//Contains Reference to Linking/Walking through heap
int main()
{


	// create a pointer to the head node
	Node* head = nullptr;

	// create a pointer to end node
	Node* end = nullptr;
	// call the insert_at_front function four times
	insert_front(&head, 1);
	insert_front(&head, 2);
	insert_front(&head, 3);
	insert_front(&head, 4);

}

