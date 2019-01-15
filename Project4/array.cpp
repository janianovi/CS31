//
//  main.cpp
//  array
//
//  Created by Janis Chen on 10/31/18.
//  Copyright © 2018 Test Project. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

//adds a string value to the array of strings
int appendToAll(string a[], int n, string value)
{
    if (n < 0) //if array length is negative
        return -1;

    for (int i = 0; i < n; i++)
        a[i] += value; //adds string values to arrays
    
    return n;
}

//returns the position of the string in the array that is equal to target
int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++)
    {
        if(a[i] == target) //if current element is equal to target
            return i; //return position of the element
    }
    return -1; //return -1 if target is not found
}

//returns the position of a string in the array that is greater than every other string in the array
int positionOfMax(const string a[], int n)
{
    if (n <= 0) //cannot find maximum if no array size
        return -1;
    string max = a[0]; //sets maximum to first element in array
    int position = 0; //records position of the maximum element
    
    for (int i = 0; i < n; i++)
    {
        if(a[i] > max) //if current element in array is greater than max
        {
            max = a[i]; //sets current element as maximum
            position = i;
        }
    }
    return position;
}

//moves all elements after element at position pos to the left
int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos >= n || pos < 0) //array cannot be moved if array size or pos is negative, or if pos is greater than n
        return -1;
    
    string rotate = a[pos];
    
    for (int i = pos; i < n - 1; i++) //loop moves all elements after element at pos to the left
        a[i] = a[i + 1];
    
    a[n - 1] = rotate; //lets last element in array to element at pos
    return pos;
}

//returns number of consecutive identical elements in array
int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    int counter = 1; //starts sequence counter at 1 to account for the first different element
    
    for (int i = 0; i < (n - 1); i++)
    {
        string sequence = a[i];
        if (a[i + 1] != sequence) //if the next element is not equal to the previous element
            counter++; //increment counter
    }
    return counter;
}

//reverses n number of the order of elements in the array
int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n / 2; i++) //sets loop to end at middle of the number flipped
    {
        string temp = "";
        temp = a[i]; //sets temporary variable to hold the element that will be switched
        a[i] = a[n - 1 - i]; //sets element in beginning half to the element in the end half
        a[n - 1 - i] = temp; //sets the element in the end to the temporary variable
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    int difference = 0; //records position of the different elements
    if (n1 >= n2) //if n1 is bigger or equal than n2 array
    {
        for (int i = 0; i < n2; i++) //loops through the shorter array
        {
            if (a1[i] == a2[i])
                difference++; //increments difference if elements are the same to an element that's different
        }
    }
    if (n2 > n1) //if n2 is bigger than n1 array
    {
        for (int i = 0; i < n1; i++)
        {
            if (a2[i] == a1[i])
                difference++;
        }
    }
    return difference;
}

//returns position of elements in n2 if they also appear in a1 in the same way
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if ( n1 < 0 || n2 < 0)
        return -1;
    if (a1 == 0 && a2 == 0) //returns zero if both arrays are 0
        return 0;
    
    int position = 0;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j])
            {
                position++; //if the elements are the same, increment position
                if (position == n2) // if position reaches length of n2
                    return i - position + 1; //return position of the first element of n2 in n1
                
                i++;
            }
            else
                position = 0;

        }
        
    }
    return -1;
}

//return smallest position of element in a1 that is equal to any element in n2
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j]) //if the elements are equal
                return i; //return the position in the first array
        }
    }
    return -1;
}

//All elements in the beginning are less than the divider, while all elements near the end are greater than the divider
int divide(string a[], int n, string divider)
{
    if (n < 0)
        return -1;
    
    int position = 0; //records position of all elements less than divider
    for (int i = n - 1; i >= 0; i--) //loops from the end of the loop to the middle
    {
        if (a[i] >= divider) //if element is greater than divider
            rotateLeft(a, n, i); //rotate elements before current element to the left
        else
            position++; //if not greater, increment position
    }
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] == divider) //if element is the divider
        {
            string holder = a[i]; //hold divider in temporary variable
            a[i] = a[position]; //set element of divider to element at the position variable
            a[position] = holder;
            position++; //increment past divider
        }
    }
    
    for (int j = 0; j < n; j++)
    {
        if (a[j] >= divider) //return element that is not less than divider
            return j;
    }
    return n;
}



int main()
{
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string e[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
    
    assert(divide(h, 7, "fiona") == 3);
    
    cerr << "All tests succeeded" << endl;

}
