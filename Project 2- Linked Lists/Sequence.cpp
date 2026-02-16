#include "Sequence.h"
#include <iostream>
using namespace std;


//constructor 
Sequence::Sequence()
{
	//initialize the empty sequence
	m_size = 0; 
	head = nullptr; 
	tail = nullptr; 
}



//destructor
Sequence::~Sequence()
{
	//if the Sequence has no values, leave function
	if (head == nullptr)
	{
		return;   //exit function
	}

	//if list is not empty: delete memory that was dynamically allocated 
	Node* currentNode = head; 
	Node* nextNode;           

	while (currentNode != nullptr)         //checks if we are at the end of the linked list
	{
		nextNode = currentNode->nextNode;  //save pointer to next node 
		delete currentNode;                //delete current node 
		currentNode = nextNode;            //change pointer of current node to pointer of next node 
	}
}




//copy constructor -- takes in reference to another sequence object, copy object values to object calling it
Sequence::Sequence(const Sequence& other)
	:m_size(0), head(nullptr), tail(nullptr)
{
	//copy over private data memeber
	m_size = other.m_size; 

	//check if other is empty 
	if (other.m_size == 0)  
	{
		head = nullptr; 
		tail = nullptr; 
		return;  //exit 
	}

	//create new linked list 
	//first create head node 
	this->head = new Node; 
	this->head->prevNode = nullptr; 

	//node follows one behind the current node in for loop 
	//this will allow us to set each nodes next pointer 
	Node* prev_New_Node = this->head; 

	//cycle through other linked list
	//start with head of Other linked list; contiue until you reach tail node; move to next node in Other linked list
	for (Node* currentNode = other.head; currentNode->nextNode != nullptr; currentNode = currentNode->nextNode)
	{
		Node* newNode = new Node;                      //create new object and ptr to it 
		newNode->m_value = currentNode->m_value;       //set CURRENT new object's value to that of other
		newNode->prevNode = prev_New_Node;             //set CURRENT new object's prev pointer 
		prev_New_Node->nextNode = newNode;             //set PREVIOUS new object's next pointer 
		prev_New_Node = newNode;                       //update the previous node 
	}

	//set tail node 
	this->tail->m_value = other.tail->m_value; 
	this->tail->nextNode = nullptr; 

	//at this point pre_new_node points to the last item in the linked list that is not the tail 
	//prev_new_node should point to tail node 
	prev_New_Node->nextNode = this->tail; 

	
}




//assignment opperator
Sequence& Sequence::operator=(const Sequence& rhs)
{
	//don't assign if they rhs and this are already the same
	if (this != &rhs)  
	{
		Sequence tempSequence(rhs);   //use copy constructor 
		swap(tempSequence);           //swap temp sequence and this Sequence object
	}
	return *this;                     //return pointer to this object 
	//once we leave the destructor will be called on the tempSequence object 
}




//Dump Function 
void Sequence::dump() const
{
	/* 
	cerr << "______________________________________" << endl; 

	//display the sequence
	//head and tail values 
	if (head == nullptr)
	{
		cerr << "Head is nullptr" << endl; 
	}
	else
	{
		cerr << "Head at: " << head << endl; 
	}

	if (tail == nullptr)
	{
		cerr << "Tail is nullptr" << endl; 
	}
	else
	{
		cerr << "Tail at: " << tail << endl; 
	}

	//display size 
	cerr << "Size: " << m_size << endl; 

	int counter = 0; 

	//display all elements of linked list 
	for (Node* currentNode = head; currentNode != nullptr; currentNode = currentNode->nextNode)
	{
		//information about current node 
		cerr << "\nELEMENT NUMBER: " << counter << endl; 
		cerr << "Address: " << currentNode << endl;
		cerr << "element value: " << currentNode->m_value << endl;
		//display prevNode 
		if (currentNode->prevNode == nullptr)
		{
			cerr << "Previous node: nullptr" << endl; 
		}
		else
		{
			cerr << "Previous node: " << currentNode->prevNode << endl;                               //what will this display, address or some value idk 
		}
		//display nextNode
		if (currentNode->nextNode == nullptr)
		{
			cerr << "Next node: nullptr" << endl;
		}
		else
		{
			cerr << "Next node: " << currentNode->nextNode << endl;                           
		}
		counter++; 
	}
	cerr << endl << "!!!Done!!!----------------------------------------------" << endl; 
	*/
}




//empty function
bool Sequence::empty() const
{
	if (m_size == 0)
	{
		return true; 
	}
	return false; 
}




//size function -- return m_size
int Sequence::size() const
{
	return m_size; 
}




//insert first item -- when m_size == 0 
void Sequence::insertOnlyItem(ItemType value)
{
	//create new node and set prev and next node to nullptr b/c the list only has one node 
	Node* newNode = new Node; 
	newNode->m_value = value; 
	newNode->prevNode = nullptr; 
	newNode->nextNode = nullptr; 

	//set head and tail to be this node b/c it is the only node so far
	head = newNode; 
	tail = newNode; 

	//increment size 
	m_size++; 
}




//insert first item -- when m_size != 1 and pos == 0
void Sequence::insertFirstItem(ItemType value)
{
	//create new node 
	Node* newNode = new Node;

	//set next node's prev node 
	this->head->prevNode = newNode; 

	//set fields of new node
	newNode->m_value = value; 
	newNode->prevNode = nullptr; 
	newNode->nextNode = this->head; 

	//change header
	head = newNode; 

	//increment size
	m_size++; 
}




//insert last item -- when pos == m_size - 1
void Sequence::insertLastItem(ItemType value)
{
	//create new node
	Node* newNode = new Node; 

	//change nextPointer of former last item
	this->tail->nextNode = newNode; 

	//set fields of new node
	newNode->m_value = value; 
	newNode->prevNode = tail; 
	newNode->nextNode = nullptr; 

	//change tail 
	tail = newNode; 

	//increment size
	m_size++; 
}



//insert at a specific position 
void Sequence::insertAtPosition(ItemType value, int pos)
{
	//create new node
	Node* newNode = new Node;
	newNode->m_value = value;



	//cycle through list and insert new item 
	int forwardCounter = 0;
	Node* currentNode = this->head;


	//go forward in linked list 
	while (forwardCounter <= pos)
	{
		if (forwardCounter == pos)
		{
			newNode->nextNode = currentNode;

			newNode->prevNode = currentNode->prevNode; 

			currentNode->prevNode->nextNode = newNode;

			currentNode->prevNode = newNode;

			//incremement size 
			m_size++;
		}
		forwardCounter++; 
		currentNode = currentNode->nextNode;
	}
}




//insert function -- insert function position pos 
int Sequence::insert(int pos, const ItemType& value)
{
	//test if pos is out of range 
	if (pos < 0 || pos > m_size)
	{
		return -1;
	}

	//test if the linked list has no items 
	if (m_size == 0)
	{
		insertOnlyItem(value); 
		return 0; 
	}

	//test if the linked list has items and pos == 0 
	if (pos == 0)
	{
		insertFirstItem(value); 
		return pos; 
	}

	//test if we are inserting into last position 
	if (pos == m_size)
	{
		insertLastItem(value);
		return pos; 
	}

	//pos is not first, last, or only position:
	insertAtPosition(value, pos); 
	return pos; 
}




//insert function -- insert item so \ it is at the first spot where it is <= to the value in front of it 
int Sequence::insert(const ItemType& value)
{
	//check if list is empty 
	if (m_size == 0)
	{
		insert(0, value);
		return 0;
	}

	//find position to insert item 
	int position = 0;
	Node* currentNode = head;

	while (position < m_size)
	{
		if (value <= currentNode->m_value)
		{
			insert(position, value); 
			return position; 
		}

		//if we are looking at the last element 
		if (position == m_size - 1) 
		{
			//if you get to the last position without finding an item <= value 
			insert(m_size, value);
			return position;
		}
		
		position++; 
		currentNode = currentNode->nextNode; 
	}
}




//erase function -- return false if out of range, remove item at pos and then return true 
bool Sequence::erase(int pos)
{
	//check if in range 
	if (pos < 0 || pos >= m_size)
	{
		return false; 
	}


	Node* currentNode; 

	//if it is the only item 
	if (m_size == 1)
	{
		currentNode = head;
		delete currentNode;
		tail = nullptr;
		head = nullptr;
		m_size--;
		return true;
	}

	//if it is the last item 
	if (pos == (m_size - 1))
	{
		currentNode = tail; 
		//item one behind is the new tail 
		tail->prevNode->nextNode = nullptr; 
		tail = tail->prevNode; 
		delete currentNode; 
		m_size--;
		return true;
	}


	//if it is the first item and string isn't empty 
	if (pos == 0)
	{
		currentNode = head; 
		head->nextNode->prevNode = nullptr; 
		head = head->nextNode; 
		delete currentNode; 
		m_size--;
		return true;
	}

	//otherwise: erase object at pos
	//cycle through list and insert new item 
	int forwardCounter = 0;
	currentNode = this->head;


	//go forward in linked list 
	while (forwardCounter <= pos)
	{
		if (forwardCounter == pos)
		{
			currentNode->prevNode->nextNode = currentNode->nextNode; 
			currentNode->nextNode->prevNode = currentNode->prevNode; 
			delete currentNode; 
			m_size--;
			return true;
		}
		forwardCounter++;
		currentNode = currentNode->nextNode;
	}
}



//remove function: erase all items == value; return the num of items removed 
int Sequence::remove(const ItemType& value)
{
	int forwardCounter = 0;
	Node* currentNode = this->head;
	int counter = 0; 
	Node* tempNextNode = nullptr; 

	//go forward in linked list 
	while (forwardCounter < m_size)
	{
		tempNextNode = currentNode->nextNode; 

		if (currentNode->m_value == value)
		{
			erase(forwardCounter); 
			counter++; 
			forwardCounter--; 
		}
	
		forwardCounter++;
		currentNode = tempNextNode;
	}

	return counter; 
}




bool Sequence::get(int pos, ItemType& value) const
{
	//check if in range 
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}

	int forwardCounter = 0;
	Node* currentNode = head; 

	//go forward in linked list 
	while (forwardCounter < m_size)
	{
		//once you get to the position
		if (forwardCounter == pos) 
		{
			value = currentNode->m_value;
			return true; 
		}

		forwardCounter++;
		currentNode = currentNode->nextNode;
	}

	return true; 
}



//set function
bool Sequence::set(int pos, const ItemType& value)
{
	//check if in range 
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}

	int forwardCounter = 0;
	Node* currentNode = head;

	//go forward in linked list 
	while (forwardCounter < m_size)
	{
		//once you get to the position
		if (forwardCounter == pos)
		{
			currentNode->m_value = value; 
			return true;
		}

		forwardCounter++;
		currentNode = currentNode->nextNode;
	}

	return true;
}



//find function 
int Sequence::find(const ItemType& value) const
{
	int forwardCounter = 0;
	Node* currentNode = head;

	//go forward in linked list 
	while (forwardCounter < m_size)
	{
		//once you get to the position
		if (currentNode->m_value == value)
		{
			return forwardCounter;
		}

		forwardCounter++;
		currentNode = currentNode->nextNode;
	}

	return -1; 
}




void Sequence::swap(Sequence& other)
{
	//swap the size of each sequence 
	int tempSize = this->m_size; 
	this->m_size = other.m_size; 
	other.m_size = tempSize; 

	//swap the head of each sequence 
	Node* tempHead = this->head; 
	this->head = other.head; 
	other.head = tempHead; 

	//swap the tail of each sequence 
	Node* tempTail = this->tail; 
	this->tail = other.tail; 
	other.tail = tempTail; 
}


//NON-MEMBER FUNCTIONS

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (seq2.empty())
	{
		return -1;
	}

	ItemType temp1; 
	ItemType temp2; 

	bool foundIt = false; 

	int pos1 = 0; 
	for (int i = 0; i < seq1.size(); i++)
	{
		if ((i + seq2.size()) < seq1.size() + 1)
		{
			foundIt = true;
			pos1 = i; 

			for (int j = 0; j < seq2.size(); j++)
			{
				seq1.get(pos1, temp1);
				seq2.get(j, temp2);
				if (temp1 != temp2)
				{
					foundIt = false;
				}
				pos1++; 
			}

			if (foundIt == true)
			{
				return i; 
			}
		}
	}
	return -1; 
}



void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	int oriSize = result.size(); 

	for (int i = 0; i < oriSize; i++)
	{
		result.erase(0); 
	}

	int position = 0; 

	ItemType temp; 
	for (int i = seq1.size() - 1; i >= 0; i--)
	{
		seq1.get(i, temp); 
		result.insert(position, temp); 
		position++; 
	}

	for (int i = seq2.size() - 1; i >= 0; i--)
	{
		seq2.get(i, temp);
		result.insert(position, temp);
		position++; 
	}
}