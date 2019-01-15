//
//  main.cpp
//  rate
//
//  Created by Janis Chen on 11/7/18.
//  Copyright © 2018 Test Project. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

//Checks if the element in each array is in proper form
bool checkValid(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int n)
{
    //separation cannot be less than 0
    if (separation[n] < 0)
        return false;
    
    //length cannot be equal or less than 0
    if (strlen(word1[n]) == 0 || strlen(word2[n]) == 0)
        return false;
    
    //Checks if all characters within element is a letter
    for (int m = 0; m < strlen(word1[n]); m++)
    {
        if (!isalpha(word1[n][m]))
            return false;
    }
    for (int m = 0; m < strlen(word2[n]); m++)
    {
        if (!isalpha(word2[n][m]))
            return false;
    }
    return true;
}

//Makes all the characters in the element lower case
void makeLower(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nPatterns)
{
    for (int i = 0; i < nPatterns; i++)
    {
        for (int m = 0; m < strlen(word1[i]); m++)
            word1[i][m] = tolower(word1[i][m]);
        for (int m = 0; m < strlen(word2[i]); m++)
            word2[i][m] = tolower(word2[i][m]);
    }
}

//removes the element in the specific row
void removeElement(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns, int row)
{
    for(int i = row; i < nPatterns - 1; i++)
    {
        strcpy(word1[i], word1[i+1]);
        strcpy(word2[i], word2[i+1]);
        separation[i] = separation[i + 1];
    }
}


int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns)
{
    //checks for negative nPatterns
    if(nPatterns <= 0)
        nPatterns = 0;
    
    //makes all characters lower case
    for (int i = 0; i < nPatterns; i++)
    {
        for (int j = 0; j < MAX_WORD_LENGTH+1; j++)
            makeLower(word1, word2, nPatterns);
    }
    
    //removes element if it is not in proper form
    for (int i = 0; i < nPatterns; i++)
    {
            if (!checkValid(word1, word2, separation, i))
            {
                removeElement(word1, word2, separation, nPatterns, i);
                nPatterns--;
                i--;
                
            }
    }

    //checks for same patterns by looping through both arrays
    for (int i = 0; i < nPatterns; i++)
    {
        for (int j = 0; j < nPatterns; j++)
        {
            if (strcmp(word1[i], word2[j]) == 0 && strcmp(word1[j], word2[i]) == 0) //if element in word1 matches element in word2
            {
                if (separation[i] < separation[j]) //remove element with lower separation
                {
                    removeElement(word1, word2, separation, nPatterns, i);
                    nPatterns--;
                    i--;
                }
                else
                {
                    removeElement(word1, word2, separation, nPatterns, j);
                    nPatterns--;
                    i--;
                }
            }
        }
    }
    for (int i = 0; i < nPatterns; i++)
    {
        for (int j = i + 1; j < nPatterns; j++)
        {
            if (strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0) //if element in word1/2 matches another element in word1/2
            {
                if (separation[i] < separation[j]) //remove element with lower separation
                {
                    removeElement(word1, word2, separation, nPatterns, i);
                    nPatterns--;
                    i--;
                }
                else
                {
                    removeElement(word1, word2, separation, nPatterns, j);
                    nPatterns--;
                    i--;
                }
            }
        }
    }
    return nPatterns;
}

//calculates the number of patterns within a document
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns)
{
    //checks nPatterns
    if (nPatterns <= 0)
        return 0;
    
    //creates a copy of the document
    char wordDoc[250][251];
    
    int i = 0;
    int j = 0;
    int word = 0;
    
    //copies document into the copy of the document
    for (i = 0; document[i] != '\0'; i++)
    {
        if (document[i] == ' ') //adds word onto new line when reaching a space
        {
            if (document[i+1] == '\0' && ((i + 1) < strlen(document))) //exit loop if end of the document
                break;
            
            wordDoc[word][j] = '\0';
            
            j = 0;
            word++; //keeps track of how many words are in the document
        }
        if(isalpha(document[i])) //if letter, add to the copy of the document
        {
            wordDoc[word][j] = tolower(document[i]);
            j++;
        }
    }
    
    //adds zero byte for last element
    wordDoc[word][j] = '\0';
    
    
    int match = 0;
    
    //checks the separation between the elements
    for (int i = 0; i < nPatterns; i++)
    {
        bool pattern = false; //sets a boolean variable to see if there is a pattern
        
        //loops through the amount of words in copy of document
        for (int j = 0; j <= word && pattern == false; j++)
        {
            if (strcmp(wordDoc[j], word1[i]) == 0) //if same word
            {
                //calculate the minimum amd maximum distance between two words for a pattern
                int mindex = j - (separation[i] + 1);
                int maxdex = j + (separation[i] + 1);
                
                for (int k = mindex; k <= maxdex; k++)
                {
                    //if second word is between the min/max separations, add to pattern and break out of loop
                    if (strcmp(wordDoc[k], word2[i]) == 0)
                    {
                        pattern = true;
                        match++;
                        break;
                    }
                }
            }
        }
    }
    
    return match;
}

int main()
{
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    cerr << "All tests succeeded" << endl;
    
}


