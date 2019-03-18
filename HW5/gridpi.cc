// Calculating pi

#include <cmath>   // for pow()
#include <iostream>

double gridpi(unsigned npoints)
{
    if (npoints < 1){
        std::cout << "Cannot construct grid due to non-positive input.\n";
        return 0;
    }
    unsigned count {0};

    for (int row=0; row!=(npoints); ++row)          // From 0 to npoints exclusive, representing rows
        for (int col=0; col!=(npoints); ++col){     // From 0 to npoints exclusive, representing columns
            if (std::hypot(row, col) <= npoints)    // If the hypotenuse of the current point is smaller than radius, which is equal to npoints
                {++count;}                          // Increment count
        }    
    double piEstimate {(count/pow(npoints, 2))*4}; // This is a quarter circle, so divide the result to total points and multiply by 4.
    return piEstimate;                             // Return estimated value 
}

int main()
{
    int testValues [7] = {10, 50, 100, 500, 1000, 5000, 10000};
    for (int x : testValues)
    std::cout << "The result of gridpi for " << x << " input is " << gridpi(x) << ".\n";
    return 0;
}