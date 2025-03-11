#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numbers>
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
		camera.origin += Vec3(0, 0, 0.5);
		camera.SetAspectRatio(aspect_ratio);

		sun = Sun();
		sun.direction = Vec3(-0.4, -1, -0.5).normalize();

		maxDepth = 1;
		shadows = false;

	}

	~RayTracer()
	{
		for (auto triangle : triangles) {
			delete triangle;
		}
	}

	void GetImage(vector<unsigned char>& image);

	

	Camera camera;
	vector<Triangle*> triangles;
	Sun sun;
	string filename;
	int maxDepth;

	int width;
	int height;

	bool shadows;

private:
	Vec3 GetColor(const Ray& ray, const int depth);
};

void ReadSTLFile(const string& filename, RayTracer& rayTracer);

void WriteSTLFile(const string& filename, RayTracer& rayTracer);

void CreateObjects(RayTracer& rayTracer);

vector<Triangle*> CreateSphere(const float radius, const int numLat, const int numLong);