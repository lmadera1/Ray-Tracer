#pragma once
#include <vector>
#include <string>
#include "Vec3.h"

using namespace std;

void WritePPM(const vector<vector<Vec3>>& image, const string& filename);
