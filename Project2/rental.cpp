//
//  main.cpp
//  rental
//
//  Created by Janis Chen on 10/10/18.
//  Copyright © 2018 Test Project. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    // Gather the input
    cout << "Odometer at start: ";
    double startOdometer;
    cin >> startOdometer;
    
    cout << "Odometer at end: ";
    double endOdometer;
    cin >> endOdometer;
    
    cout << "Rental days: ";
    double daysRented;
    cin >> daysRented;
    cin.ignore(10000, '\n');
    
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    
    cout << "Luxury car? (y/n): ";
    string luxuryCar;
    getline(cin, luxuryCar);
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    double month;
    cin >> month;
    
    double totalMiles = endOdometer - startOdometer;
    double rentalCharge;
    
    //Compute results
    if (luxuryCar == "n")
    {
        rentalCharge = 33 * daysRented;
    }
    else
    {
        rentalCharge = 61 * daysRented;
    }
    
    if (totalMiles <= 100)
    {
        rentalCharge += totalMiles * 0.27;
    }
    if (totalMiles > 100 && totalMiles <= 400)
    {
        if (month == 12 || (month >= 1 && month <= 3))
        {
            rentalCharge += 27 + (totalMiles - 100) * 0.27;
        }
        else
        {
            rentalCharge += 27 + (totalMiles - 100) * 0.21;
        }
    }
    if (totalMiles > 400)
    {
        if (month == 12 || (month >= 1 && month <= 3))
        {
            rentalCharge += 27 + 300 * 0.27 + (totalMiles - 400) * 0.19;
        }
        else
        {
            rentalCharge += 27 + 300 * 0.21 + (totalMiles - 400) * 0.19;
        }
    }
    
    //Print results and error checking
    cout << "---" << endl;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    if (startOdometer < 0)
    {
        cout << "The starting odometer reading must be nonnegative." << endl;
    }
    else if (endOdometer < startOdometer)
    {
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
    }
    else if (daysRented <= 0)
    {
        cout << "The number of rental days must be positive." << endl;
    }
    else if (name == "")
    {
        cout << "You must enter a customer name." << endl;
    }
    else if (luxuryCar != "y" && luxuryCar != "n")
    {
        cout << "You must enter y or n." << endl;
    }
    else if (month < 1 || month > 12)
    {
        cout << "The month number must be in the range 1 through 12." << endl;
    }
    else
    {
        cout << "The rental charge for " << name << " is $" << rentalCharge << endl;
    }
}


