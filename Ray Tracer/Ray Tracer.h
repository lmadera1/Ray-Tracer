#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include "Vec3.h"
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "lodepng.h"

using namespace std;

class RayTracer
{
public:
	RayTracer(const string& filename, const int width, const int height)
		: filename(filename), width(width), height(height)
	{
		
		float aspect_ratio = static_cast<float>(width) / height;

		camera = Camera();
		camera.SetAspectRatio(aspect_ratio);

		sun = Sun();
		sun.direction = Vec3(-0.4, -1, -0.5).normalize();

		CreateObjects();

		maxDepth = 4;

	}

	~RayTracer()
	{
		for (auto object : objects) {
			delete object;
		}
	}

	void GetImage(vector<unsigned char>& image);

	void CreateObjects();

	

	Camera camera;
	vector<Object*> objects;
	Sun sun;
	string filename;
	int maxDepth;

	int width;
	int height;

private:
	Vec3 GetColor(const Ray& ray, const int depth);
};