// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"
#include <iostream>
#include <fstream>

string filename = "output.ppm";

void WritePPM(const vector<vector<Vec3>>& image, const string& filename) {
    ofstream file(filename);

    if (!file.is_open())
    {
        string msg = "Can't open file";
        throw std::runtime_error(msg);
    }

    file.close();
}

int main()
{
    vector<vector<Vec3>> image;

    try 
    {
        WritePPM(image, filename);
    }
    catch(exception ex) 
    {
        return 1;
    }

    return 0;
}
