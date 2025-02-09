#pragma once
#include <vector>
#include <string>
#include "Vec3.h"

using namespace std;

void WritePPM(const vector<vector<Vec3>>& image, const string& filename);
void GetImage(vector<vector<Vec3>>& image, const int width, const int height);
Vec3 GetColor(const int i, const int j);