#include <iostream>
//5.) Create a class, call it MyObject (or anything you like). In your main function,
//  create and delete the class using new and delete.
class MyObject
{
public:
	MyObject();
	~MyObject();
	void* operator new(size_t size);
	void operator delete(void* pMem);

	//Class Specfic New/Delete Overloading
private:

};

MyObject::MyObject()
{
	std::cout << "Contructor Called:";
}

MyObject::~MyObject()
{
	std::cout << "Destructor Called:";
}

void* MyObject::operator new(size_t size)
{
	//For Reference
	std::cout << "New Operator Overloading" << std::endl;

	//Store Requested Bytes
	void* p = malloc(size);
	return p;
}

void MyObject::operator delete(void* pMem)
{
	std::cout << "Delete Operator Overloading" << std::endl;
	free(pMem);
}

//Global New/Delete Overload Operators
void* operator new (size_t size)
{
	//For Reference
	std::cout << "New Operator Overloading" << std::endl;
	
	//Store Requested Bytes
	void* p = malloc(size);
	return p;
}

void operator delete (void* pMem)
{
	std::cout << "Delete Operator Overloading" << std::endl;
	free(pMem);

}

int main()
{
	/*
	2. Write some debug output using cout – for example, 
	write “The number is 7”, where 7 is the value of an integer.
	
	int num = 7;
	std::cout << "The number is " << num;
	*/
	/*
	3. In your main function, allocate some integer memory using new, 
	free the memory using delete.The memory should be an array of 10 integers.
	
	//C++ Styled Dynamic Memory Allocation
	//Here we create an pointer array that stores 10 int pointers.
	//Each pointers address is randomly stored on heap.
	//	*Heap Blocks

	int* p_num[10];
	p_num[0] = new int(1);
	p_num[1] = new int(2);
	p_num[2] = new int(3);
	p_num[3] = new int(4);
	p_num[4] = new int(5);
	p_num[5] = new int(6);
	p_num[6] = new int(7);
	p_num[7] = new int(8);
	p_num[8] = new int(9);
	p_num[9] = new int(10);

	delete(p_num);
*/
	/*4. Do the same as(3), but use malloc and free.
	Adjusting to malloc and free (c styled dynamic memory allocation).
	

	//Using malloc, we requested to enough bytes to store 10 integers,
	//we can also only store 10 integers too
	int* num_array = (int*)malloc(10 * sizeof(int));

	//Using square brackets, this allows us to access different bytes
	//on memory (each byte has allocated memory address).
	//Since an int is 4 bytes, that means one byte is covered by 4 memory addresses.
	//We donot need to worry about that.
	num_array[0] = 1;
	num_array[1] = 2;
	num_array[2] = 3;
	num_array[3] = 4;
	num_array[4] = 5;
	num_array[5] = 6;
	num_array[6] = 7;
	num_array[7] = 8;
	num_array[8] = 9;
	num_array[9] = 10;

	//We only need to call num array as this was the address used to request bytes (from malloc).
	free(num_array);
	*/

	//Using new keyword, this will call the constructor, in turn allowing us to allocate
	//many objects dynamically via one pointer.
	MyObject* object = new MyObject();



	delete(object);
	return 0;

	
}

/*
int x = 1;
float y = 2;
float* pf = &y;
int main()
{

	float f_array[] = { 1 , 2, 3 , 4, 5, 6 };
	int* pn = new int;

	void* pv = malloc(sizeof(float) * 3);
	float* pf = new float[7];

	delete pn;
	register int a = 0;

}

1.) Which of the following lines of code are examples of dynamic memory allocation
and which are static?

Static Objects - int x and y are static,they do not use the static keyword.
We can use the static keyword to make the lifetime of local variables (within callstack)
lifespan of the program.

	*For readability, we can explicitly describe variables static
	* We may also need to make a local object static
			*We can make classes static too.
Object pf(globally declared) is still static due to this.

Automatic Objects - object f_array is an automatic object.
	
	*Allocated upon stack, delete once out of stack. 

Dynamic Objects - Objects pn , pv and pf are dynamically allocated via the utility of the new and malloc
allocators.

2.)A memory leak will occur. How many bytes of memory will be leaked? 
You can assume that all data types in the code are 4 bytes in size

We can eliminate all static objects from being the potential cause of a memory leak.

Why?

The scope of static/global objects is the lifetime of the program.

ALl dynamically allocated objects, pv, pf would cause memory leaks.

	* 8 Bytes wide
Why? Because we do not deallocate/release memory.

3.)What is wrong with the following code?

BaseObject* bArrWithNew2 = new BaseObject[1];
delete bArrWithNew2;

The use of square brackets, [], is used to index/access element in an array.
Instead, the utility of, (), should be used which will allow us to
pass an argument using the new keyword.

		*Operator new requires argument, this argument being size.

4.) What will likely happen when the following code is executed in a function?

int myArray[999999];

This will cause an stack overflow.

5.) For the code in main.cpp above.
In the code which resides in the main() function, 
which lines indicate memory which is allocated on the Heap,
and which on the Stack.

Stack Stored - f_array.
	*Automatic memory allocation stores objects on stack.
	*Why Automatic, objects declared within a callstack unless declared static
	or allocated dynamically, such objects are allocated once entered call stack.
	Then terminated once out of scope within callstack, meaning the function object
	is bound too has ended executing.
	
Heap Stored - pn , pv, and pf.
	*Utility of dynamic memory allocation call new, while locally declared, using new explcitly stores objects on heap.
	Where we must manually manage the deallocation of the object to prevent memory management issues.

	
If memory allocation in C++ is so complicated,
and prone to error, why do games companies choose to program 
in C++ rather than a language with a memory manager like C# or Java?

This is due to C++ allowing programmers to dynamically manage memory fully.
C# and Java while may allow you to dynamically allocate objects, due to their
garbage handling systems where they deallocate memory for you, having a lack
of control over your objects is inefficient when we can use C++ and have full control
and build systems around this.

6.) Why can’t you increment a void pointer, such that you can with an int or float pointer?

Because the pointer points to nothing, using void allows us to a assign data type to pointer. Until the pointer is
no longer void and has an assigned type and address, we cannot use pointer arithmetics.
*/


