// you will turn in one file named linear.cpp that contains the five functions and nothing more:
//no #include directives, no using namespace std;, no implementation of somePredicate and no main routine.


// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    //no elements 
    if (n <= 0)
    {
        return true;
    } 
    //Testing last position in the array 
    else if (n == 1)
    {
        return (somePredicate(a[0])); 
    }
    //continue if you are not at the last element of the array 
    else if (somePredicate(a[0]) == false)
    {
        return false; 
    }
    //if you get past the test above, test the rest of the array
    else
    {
        return allTrue(a + 1, n - 1);
    }
}





// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    //make sure n isn't negative 
    if (n <= 0)
    {
        return 0; 
    }
    else if (n == 1)  //base case, check for the last position
    {
        //Once you get to the last element, just test that element. 
        //Don't call the countTrue function again. 
        return somePredicate(a[0]); 
    }
    else
    {
        //remember that false is also represented by integer 0
        //true represented by integer 1
        return  somePredicate(a[0]) + countTrue(a + 1, n - 1);
    }
}








// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    int counter; 
    //make sure n isn't negative. 
    //You also get here if you get to the last element w/o ever getting True. 
    if (n <= 0)
    {
        return -1; 
    }
    //if the last element is false
    else if (n == 1 && somePredicate(a[0]) == false)
    {
        return -1; 
    }
    //if the element is true, return the position 
    else if (somePredicate(a[0]) == true)
    {
        return 0; 
    }
    //if the element is false, try again 
    else
    {
        counter =  firstTrue(a + 1, n - 1);
        if (counter == -1)
        {
            return -1;
        }
        else
        {
            return counter + 1;
        }
    }
}








// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    //bad input 
    if (n <= 0)
    {
        return -1;
    }
    //last element in array 
    else if (n == 1)
    {
        return 0; 
    }

    int midPoint = n / 2;                                                 //get position of middle element 
    int max1_pos = positionOfMax(a, midPoint);                            //check 1st half 
    int max2_pos = positionOfMax(a + midPoint, n - midPoint) + midPoint;  //check 2nd half 

    //make comparison 
    if (a[max1_pos] >= a[max2_pos]) 
    {
        return max1_pos; 
    }
    else
    {
        return max2_pos; 
    }
}









// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    //check bad input 
    if (n2 < 0)
    {
        return true;
    }
    else if (n1 < 0)
    {
        return false; 
    }
    


    //if you get to the end of a2 without running into a problem
    if (n2 == 0)
    {
        return true; 
    }
    //if you get to the end of a1 and never find all of a2 
    else if (n1 == 0)
    {
        return false; 
    }
    //if there are not enough elements in a1 left 
    else if (n1 < n2)
    {
        return false; 
    }

    //value found 
    if (a1[0] == a2[0])
    {
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);  //move forward in both arrays 
    }
    //value NOT found 
    else
    {
        return contains(a1 + 1, n1 - 1, a2, n2); //move forward in a1 array 
    }
}



