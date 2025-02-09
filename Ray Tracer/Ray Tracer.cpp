// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"
#include <iostream>
#include <fstream>

string filename = "output.ppm";
int width = 800;
int height = 800;

int main()
{
    vector<vector<Vec3>> image;

    GetImage(image, width, height);

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

void GetImage(vector<vector<Vec3>>& image, const int width, const int height) {
    for (int i = 0; i < width; i++) {
        vector<Vec3> column;
        for (int j = 0; j < height; j++) {
            Vec3 color = GetColor(i, j);
            column.push_back(color);
        }

        image.push_back(column);
    }
}

Vec3 GetColor(const int i, const int j) 
{

    return Vec3(255, 255, 0);
}

void WritePPM(const vector<vector<Vec3>>& image, const string& filename) {
    ofstream file(filename);

    if (!file.is_open())
    {
        string msg = "Can't open file";
        throw std::runtime_error(msg);
    }

    if (image.size() < 1 || image[0].size() < 1) 
    {
        string msg = "No image data to write";
        throw std::runtime_error(msg);
    }

    int width = image.size();
    int height = image[0].size();

    // Write PPM header
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Vec3 color = image[i][j];
            file << color.x << " " << color.y << " " << color.z << "\n";
        }
    }

    file.close();
}
