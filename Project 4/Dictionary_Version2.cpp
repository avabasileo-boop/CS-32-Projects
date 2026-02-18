// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);
//void sortLettersByAlpha(string& s);
void removeAndSort(string& s);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int /* maxBuckets */) {
        for (int j = 0; j < 14348907; j++)
            myIndex->push_back(0);
        //cout << "hi " << endl;
        
    }
        
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string));  //const
    //void removeAndSort(string& s);
    //void swap(int* a, int* b);  
    bool isAnagram(const string& a, const string& b) const;

private:
    list<string> m_words;
    vector<string> myVector1;
    vector<string> myVector2;
    
    vector<int> myIndex[14348907];
};
    

void DictionaryImpl::insert(string word)
{
    int i = 0;
    int pos = 0;
    
    int val1 = 0, val2 = 0, val3 = 0, val4 = 0, val5 = 0;

    //system("pause");

    removeNonLetters(word);
    string originalWord = word;
    
    if (!word.empty())
    {
        std::sort(word.begin(), word.end());
              
        if (myVector1.size() == 0)
        {
            myVector1.insert(myVector1.begin() + i, word);
            myVector2.insert(myVector2.begin() + i, originalWord);
            i++;           
        }
        else
        {
            while (i < myVector1.size() && (word.compare(myVector1[i]) > 0)) // while the new word is greater than word at index i, kepp going 
            {
                i++;
            }


            myVector1.insert(myVector1.begin() + i, word);
            myVector2.insert(myVector2.begin() + i, originalWord);

            for (int j = 0; j < myVector1.size(); j++)
            {
                val1 = myVector1[j].at(0) - 96;
                if (myVector1[j].size() > 1) { val2 = myVector1[j].at(1) - 96; }
                else { val2 = 0; }
                if (myVector1[j].size() > 2) { val3 = myVector1[j].at(2) - 96; }
                else { val3 = 0; }
                if (myVector1[j].size() > 3) { val4 = myVector1[j].at(3) - 96; }
                else { val4 = 0; }
                if (myVector1[j].size() > 4) { val5 = myVector1[j].at(4) - 96; }
                else { val5 = 0; }

                pos = (val1 * 27 * 27 * 27 * 27) + (val2 * 27 * 27 * 27) + (val3 * 27 * 27) + (val4 * 27) + val5;

                myIndex->at(pos) = j;
            }
        }
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) //const 
{
    
    
    int pos = 0;   

    if (callback == nullptr)
        return;

    removeNonLetters(letters);

    if (letters.empty())
        return;

    std::sort(letters.begin(), letters.end());

    int size = letters.size();
    int val[20] = {};

    if (size > 5)
    { size = 5; }

    for (int i = 0; i < size; i++)
    {
        val[i] = letters.at(i) - 96;
    }
    
    pos = (val[0] * 531441) + (val[1] * 19683) + (val[2] * 729) + (val[3] * 27) + val[4];
    
    int compPoint = myIndex->at(pos);    

    while (letters != myVector1[compPoint])
    {
        //callback(myVector2[compPoint]);
        compPoint--;
        if (letters.substr(0, 5) != myVector1[compPoint].substr(0, 5))
        {
            return;
        }            
    }
    while (compPoint >= 0 && letters == myVector1[compPoint])
    {
        callback(myVector2[compPoint]);
        compPoint--;
    }
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
/*

void removeNonLetters(string& s)
{
    
    int pos = 0;
    int size = s.size();

    for (int i = 0; i < size; i++)
    {
        if ((s[i] > 64) && (s[i] < 91))
        {
            s[pos++] = (s[i + 32]);
        }

        if ((s[i]) > 96 && s[i] < 123)
        {
            s[pos++] = (s[i]);
        }
    }
    s.erase(pos, size - pos);
}


    
 */

void removeAndSort(string& s)
{
    int arr[27] = { 0 };
    int pos = 0;
    int size = s.size();   

    for (int i = 0; i < size; i++)
    {
        if (s[i] > 96 && s[i] < 123)
        {
            (arr[s[i] - 96]++);
        }
        else if ((s[i] > 64) && (s[i] < 91))
        {
            (arr[s[i] - 64]++);
        }
    }

    for (int i=0;i<27;i++)
    {
        //cout << arr[i] << endl;

        while (arr[i] > 0)
        {
            s[pos++] = i + 96;
            arr[i]--;
        }
                   
    }
    s.erase(pos, size - pos);
    //cout << ":" << s << endl;
    //while (1);
      
}
/*
void removeNonLetters(string& s)
{

    int pos = 0;
    int size = s.size();
    
    for (int i = 0; i < size; i++)
    {
       if ((s[i]) > 96 && s[i] < 123)
        {
            s[pos++] = (s[i]);
        }
        else if ((s[i] > 64) && (s[i] < 91))
        {
            s[pos++] = (s[i + 32]);
        }
    }
    s.erase(pos, size - pos);
}

*/

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






void sortLettersByAlpha(string& s)
{
    int i, j, temp;
    for (i = 0; i < s.size(); i++)
    {
        for (j = (s.size() - 1); j > 0; j--)  // 
        {
            if (s[j] < s[j - 1])
            {
                temp = s[j - 1];
                s[j - 1] = s[j];
                s[j] = temp;
            }
        }
    }
    //cout << "sort letters by alpha: " << s << endl;
}



/*

void sortLettersByAlpha(string& s)
{
    int arr[27];
    int i;
    for (i = 0; i < s.size(); i++)
    {
        arr[s[i] - 96]++;
    }

    s.clear();
    for (i = 0; i<27;i++)
    {
        for (int j = 0; j < arr[i]; j++)
        {
            s.push_back(arr[i + 96]);
        }
    }
    //cout << "sort letters by alpha: " << s << endl;
}

*/
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

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