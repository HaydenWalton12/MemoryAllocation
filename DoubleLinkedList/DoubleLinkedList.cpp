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


//Inserts new node at front of list, requires current head as this new node will become the new current head.
Node* insert_front(struct Node** current_head, int new_data)
{

	//Allocate New Node
	Node* new_head = new Node(new_data);

	//Make next of new node as head and previous nullptr.
	//Why? New node is will be infront, making this node the new head
	new_head->next = (*current_head);
	new_head->previous = nullptr;

	//Make head nodes previous point to new node
	if ((*current_head) != nullptr)
	{
		(*current_head)->previous = new_head;
	}
	//Replace address of current head to point to new head, this is required to ensure if we want to use the push function again.
	(*current_head) = new_head;
	return new_head;
}

Node* insert_between(struct Node* previous_node, int new_data)
{
	//Check if node is nullptr, we cant insert if the node we want to insert with doesnt exist
	if (previous_node == nullptr)
	{
		std::cout << "Given previous node cannot be nullptr\n";
		return nullptr;
	}

	//Allocate New Node
	Node* new_node = new Node(new_data);

	//New node will now be behind previous_nodes next
	//This places the next pointer now behind new_node
	new_node->next = previous_node->next;
	
	//Previous node now needs to store the new_node in next
	//As this is the node now infront
	previous_node->next = new_node;

	//To complete this node being inbetween, new nodes previous
	//points to previous_node
	new_node->previous = previous_node;

	//Change previous of new_nodes next node
	//We do this in conditional to ensure there is a node infront of new_node.
	if (new_node->next != nullptr)
	{
		new_node->next->previous = new_node;
	}

	return new_node;

}
//Contains Reference to Linking/Walking through heap
int main()
{
	Node* head = new Node(1);
	Node* node_1 = insert_front(&head, 2);
	Node* node_2 = insert_front(&head, 3);
	Node* node_3 = insert_between(node_2, 5);


}

