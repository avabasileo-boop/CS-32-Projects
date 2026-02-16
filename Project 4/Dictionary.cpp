// Dictionary.cpp
// Code by Ava Basileo
// Help from many TA's at multiple office hours during week 10



#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);


// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets)
        :m_bucketNum(maxBuckets)
    {
        m_dictionary.resize(m_bucketNum);
    }
    ~DictionaryImpl() {};
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    bool isAnagram(const string& a, const string& b) const;
    size_t generateHash(string&) const;
    vector<list<string>> m_dictionary;   //main data structure- vector composed of lists, each list is a bucket in the hash table 
    size_t m_bucketNum; 
    
};
//**************************************************************************************************************************************************









//***************************************************** PUBLIC DICTIONARYIMPL FUNCTIONS ****************************************************************
//insert function adds a word (stripped of any non-letters) to the dictionary
void DictionaryImpl::insert(string word)
{
    //remove non letters from the input 
    removeNonLetters(word); 

    //continue if the input was not empty
    if (word.empty() == true)
    {
        return;
    }

    //get the bucket
    size_t bucket = generateHash(word);

    //add value to vector at the specific bucket number
    m_dictionary[bucket].push_back(word);
}




//lookup function takes a string and a callback function, and for every word in the dictionary that 
//is an anagram of the letters in the string, it calls the callback function with that word as an argument
void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    //invalid input
    if (callback == nullptr)
        return; 

    //remove non letters 
    removeNonLetters(letters); 

    //invalid input
    if (letters.empty())
        return; 

    //figure out which bucket letters are in 
    //all anagrams will be in the same bucket becuase hash function develops same value for all words with the same letters
    size_t bucket = generateHash(letters);

    //go to the correct place in vector
    list<string>::const_iterator currentIterator = m_dictionary[bucket].begin();

    //cycle through vector 
    for (; currentIterator != m_dictionary[bucket].end(); currentIterator++)
    {
        //check if items in in vector are anagrams of letters 
        if (isAnagram(letters, *currentIterator) == true)
        {
            callback(*currentIterator);
        }
    }
}
//***************************************************************************************************************************************










//*************************************************** PRIVATE DICTIONARYIMPL FUNCTIONS *****************************************************
//generate the hash value 
//Optimization: all anagrams will have the same hash value!!!
size_t DictionaryImpl::generateHash(string& letters) const
{
    string letters2 = letters;

    //sort hashMe parameters so hat all all anagrams have same hash value 
    sort(letters2.begin(), letters2.end());

    //generate hash value using stl function 
    std::hash<string> str_hash;
    size_t hashValue = str_hash(letters2);

    //turn hashValue into bucket number (item in vector)
    size_t bucketNum = hashValue % m_bucketNum;
    return bucketNum;
}



//check if two strings are an anagram
bool DictionaryImpl::isAnagram(const string& a, const string& b) const
{
    //copy over the string because they are passed by reference 
    string a2 = a;
    string b2 = b;

    //if size mismatch return false immediately
    if (a2.size() != b2.size())
        return false;

    //sort both 
    sort(a2.begin(), a2.end());
    sort(b2.begin(), b2.end());

    //cheack if they are equal strings
    if (a2.compare(b2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//***************************************************************************************************************************************










//********************************************** NON MEMBER FUNCTIONS USED BY LOOK UP FUNCTION ********************************************
//UNCHANGED!!!
//remove non letters from the string 
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}
//*********************************************************************************************************************************************










//********************************************************  DICTIONARY FUNCTIONS ****************************************************************
// UNCHANGED!!!
// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
//***********************************************************************************************************************************************
