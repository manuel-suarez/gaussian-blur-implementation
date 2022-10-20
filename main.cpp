//
// Created by masuarez on 20/10/22.
//
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

void FilterCreation(double GKernel[][5])
{
    // initialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;
}