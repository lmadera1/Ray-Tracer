#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Vec3.h"
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "lodepng.h"

using namespace std;

void GetImage(vector<unsigned char>& image, const int width, const int height);
Vec3 GetColor(const float i, const float j);