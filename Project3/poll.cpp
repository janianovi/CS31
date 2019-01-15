//
//  main.cpp
//  poll
//
//  Created by Janis Chen on 10/21/18.
//  Copyright © 2018 Test Project. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

// tests if the state code is valid
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//runs through the pollData to check if the format is correct
bool checkStateForecast(string pollData)
{
    int i = 0;
    //runs through whole string
    while (i != pollData.size())
    {
        //checks for each separate forecast by commas
        if (pollData[i] != ',')
        {
            string stateCode = "";
            //checks and increments through the state code
            while (isalpha(pollData[i]))
            {
                stateCode += toupper(pollData[i]);
                i++;
            }
            if(!isValidUppercaseStateCode(stateCode))
                return false;
            
            // checks the votes for each party
            while (isalpha(pollData[i]) || isdigit(pollData[i]))
            {
                string votes = "";
                while (isdigit(pollData[i]))
                {
                    votes += pollData[i];
                    i++;
                    //limits votes to two digits
                    if (votes.size() > 2)
                        return false;
                }
                // returns false if there is no party code
                if (!isalpha(pollData[i]))
                    return false;
                else
                    i++;
            }
        }
        //continues through to the next forecast
        else
        {
            i++;
        }
        
    }
    return true;
}

//checks for proper usage of numbers, characters, and commas
bool hasProperSyntax(string pollData)
{
    //checks for improper symbols and spaces
    for (int i = 0; i != pollData.size(); i++)
    {
        if (!isalpha(pollData[i]) && !isdigit(pollData[i]) && pollData[i] != ',')
            return false;
        
    }
    
    //checks if the state forecast is formatted correctly
    if (!checkStateForecast(pollData))
        return false;
    
    return true;
}

//changes strings to ints for adding votes
int stringToInt(string number)
{
    int totalVotes = 0;
    for (int i = 0; i < number.size(); i++)
        totalVotes = totalVotes * 10 + (number[i] - '0');
    return totalVotes;
}

//calculates the amount of votes each party has in the poll data
int tallySeats(string pollData, char party, int& seatTally)
{
    //checks for proper syntax
    if (!hasProperSyntax(pollData))
        return 1;
    
    //checks if the party is a character
    if (!isalpha(party))
        return 2;
    
    int i = 0;
    //return 0 for a blank poll data
    if (pollData == "")
        return 0;
    
    int totalVotes = 0;
    //loops through the poll data
    while (i < pollData.size())
    {
        //increments past the state code
        while(isalpha(pollData[i]))
            i++;
        
        string votes = "";
        //adds string numbers to votes
        while (isdigit(pollData[i]))
        {
            votes += pollData[i];
            i++;
        }
        //if reached the party code, change the string numbers to ints
        if (toupper(pollData[i]) == toupper(party))
        {
           totalVotes += stringToInt(votes);
            seatTally = totalVotes;
        }
        i++;
    }
    return 0;
}

int main()
{
    string state = "cA05r";
    string state3 = "CT5D,NY9R17D1I VTne3r00D";
    cerr << hasProperSyntax(state) << endl;
    cerr << hasProperSyntax(state3) << endl;
    int seats;
    cerr << tallySeats("cA05r", 'R', seats) << endl;
    cerr << seats << endl;
    int seats2;
    cerr << tallySeats("aL5D2r,Nv9R3D0I,sc2r,IL6r08I,ca34d", 'r', seats2) << endl;
    cerr << seats2 << endl;
  
}

