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
#include "Triangle.h"
#include "Light.h"
#include "lodepng.h"
#include "BVHNode.h"

using namespace std;

class RayTracer
{
public:
	RayTracer(const int _width, const int _height)
		: width(_width), height(_height)
	{
		
		float aspect_ratio = static_cast<float>(width) / height;

		camera = Camera();
		camera.origin += Vec3(0, 0, 15);
		camera.SetAspectRatio(aspect_ratio);

		sun = Sun();
		sun.direction = Vec3(-0.4, -1, -0.5).normalize();

		objects = vector<BVHNode*>();

		maxDepth = 2;
		shadows = true;

	}

	~RayTracer()
	{
	}

	void GetImage(vector<unsigned char>& image);

	

	Camera camera;
	Sun sun;
	int maxDepth;

	int width;
	int height;

	bool shadows;
	vector<BVHNode*> objects;

private:
	Vec3 GetColor(const Ray& ray, const int depth);
};

void ReadSTLFile(const string& filename, RayTracer& rayTracer);

void WriteSTLFile(const string& filename, RayTracer& rayTracer);

void CreateObjects(RayTracer& rayTracer);

BVHNode* CreateSphere(const float radius, const int numLat, const int numLong);