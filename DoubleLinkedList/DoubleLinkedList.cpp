#include <iostream>
struct Node
{
	int data;

	//This will be the number of the node to access it correctly.
	//Why? 
	int key;
	Node* next;
	Node* previous;

	//Struct Constructor - Can be called to initialise
	//member variables, once we create node variable, we can call this.

	//Default Constructor
	Node(int d) : data(d), next(nullptr), previous(nullptr)
	{}
	//Default Constructor
	Node(int d , int e) : data(d), key(3), next(nullptr), previous(nullptr)
	{}

};


//Inserts new node at front of list, requires current head as this new node will become the new current head.
Node* insert_front(struct Node** current_head, int new_data)
{

	//Allocate New Node
	Node* new_head = new Node(new_data);
	new_head->key = new_data;

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

//Inserts new node at the end of linked list
Node* insert_back(struct Node** head, int new_data)
{
	//Allocate New Node
	Node* new_node = new Node(new_data);
	new_node->key = new_data;

	//This will be used to traverse to end of the linked list
	Node* last = *head;

	//Since this will be last node in list, how can at this stage point to a node
	//ahead of it?
	new_node->next == nullptr;

	//Traverse to last node in list
	//How does this work? last initialy equals head (start of list)
	//We check if the next value isnt equal too null, if true
	//this would indicate there is another node in list
	//we then change last node value to the next node in list
	//repeats until there is no next node , this traverses us to the end.
	while (last->next != nullptr)
	{
		last = last->next;

	}

	//Once traverse to end, we change next of last node.
	//Previously this would of been nulllptr, however this "last" node
	//is no longer the last node hence why we make the next equal the new node
	//Making the new node the "next" node/ last node in list now.

	last->next = new_node;
	return new_node;
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
	new_node->key = new_data;

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

//Recursive Approach - Not the most suitable however,
//easy to follow
void delete_node(Node*& head, int key)
{
	Node* temp_head = head;
	Node* delete_node = nullptr;
	
	//Will be used to store delete node temp and next values, so we can link up the nodes again.
	//If there is either a null prev or next, no issue! Why? because there was nothing to link to anyway!
	Node* prev_temp = nullptr;
	Node* next_temp = nullptr;

	while (temp_head->key != key)
	{
		temp_head = temp_head->next;
	}

	//If true, we discovered what node needs to be deleted.
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

//Checks key to see if this node is present within the linked list
//This function will be usedwithin condition statements else where
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
//Contains Reference to Linking/Walking through heap
int main()
{
	Node* head = new Node(1 , 1);
	Node* node_1 = insert_front(&head, 2);
	Node* node_2 = insert_front(&head, 3);
	Node* node_3 = insert_front(&head, 4);
	Node* node_4 = insert_front(&head, 5);


	delete_node(head, 5);

	return 0;
}

