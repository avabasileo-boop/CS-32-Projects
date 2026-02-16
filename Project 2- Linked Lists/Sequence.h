
#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include <string>
using ItemType = std::string; 

//using ItemType = unsigned long;

class Sequence
{
public:
    Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const; 

    //house keeping functions
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs); 

private:
    void insertOnlyItem(ItemType value); 
    void insertFirstItem(ItemType value);
    void insertLastItem(ItemType value); 
    void insertAtPosition(ItemType value, int pos); 

    //create Node data structure with a value and two pointers
    struct Node  
    {
        ItemType m_value; 
        Node* prevNode; 
        Node* nextNode; 
    };

    int m_size; 
    Node* head;     //pointer to head node
    Node* tail;     //poiner to tail node 
};

//non-member functions 
int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // SEQUENCE_INCLUDED