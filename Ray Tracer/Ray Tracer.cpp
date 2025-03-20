// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"

string filename = "output.png";
string STL_In = "teapot_binary.stl";
string STL_Out = "output.stl";
int width = 1920;
int height = 1080;

int main()
{
    vector<unsigned char> image;

	RayTracer rayTracer = RayTracer(width, height);

	ReadSTLFile(STL_In, rayTracer);

    //CreateObjects(rayTracer);

    WriteSTLFile(STL_Out, rayTracer);
    
    cout << "Printing Image" << endl;
    rayTracer.GetImage(image);

    cout << "Writing to PNG File" << endl;
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error) {
        cout << "Error" << endl;
        return 1;
    }

    return 0;
}


//Read from stl file
void ReadSTLFile(const string& filename, RayTracer& rayTracer) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return;
	}
	
    file.seekg(80); // Skip the 80-byte header
    uint32_t triangleCount;
    file.read(reinterpret_cast<char*>(&triangleCount), sizeof(triangleCount));
	cout << "Triangle count: " << triangleCount << endl;

	if (triangleCount == 0) {
		cout << "No triangles found" << endl;
		return;
	}

	Vec3 upper = Vec3(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	Vec3 lower = Vec3(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());

	vector<Triangle*> triangles;

	for (int i = 0; i < triangleCount; i++) {

		Vec3 normal;
		file.read(reinterpret_cast<char*>(&normal), sizeof(normal));
		Vec3 v1;
		file.read(reinterpret_cast<char*>(&v1), sizeof(v1));
		Vec3 v2;
		file.read(reinterpret_cast<char*>(&v2), sizeof(v2));
		Vec3 v3;
		file.read(reinterpret_cast<char*>(&v3), sizeof(v3));
		uint16_t attribute;
		file.read(reinterpret_cast<char*>(&attribute), sizeof(attribute));
		Triangle* triangle = new Triangle();
		triangle->A = v1;
		triangle->B = v2;
		triangle->C = v3;


        upper = Vec3(
            max(upper.x, triangle->upper().x),
            max(upper.y, triangle->upper().y),
            max(upper.z, triangle->upper().z)
        );

		lower = Vec3(
			min(lower.x, triangle->lower().x),
			min(lower.y, triangle->lower().y),
			min(lower.z, triangle->lower().z)
		);

		triangles.push_back(triangle);
		
	}

	BVHNode* object = BuildBVH(triangles, lower, upper, -1);

	rayTracer.objects.push_back(object);

	file.close();
}

void WriteSTLFile(const string& filename, RayTracer& rayTracer) {
    cout << "Writing STL File." << endl;

    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    file.write("Generated STL file", 80);

    vector<Triangle*> triangles = vector<Triangle*>();

    stack<BVHNode*> nodes;
    for (BVHNode* object : rayTracer.objects) {
		nodes.push(object);
    }

	while (!nodes.empty()) {
		BVHNode* node = nodes.top();
		nodes.pop();
		if (node->Left != nullptr) {
			nodes.push(node->Left);
		}
		if (node->Right != nullptr) {
			nodes.push(node->Right);
		}
		for (Triangle* triangle : node->triangles) {
			triangles.push_back(triangle);
		}
	}

    //
    uint32_t triangleCount = triangles.size();

    file.write(reinterpret_cast<char*>(&triangleCount), sizeof(triangleCount));

    for (Triangle* triangle : triangles) {
        Vec3 A = triangle->A;
        Vec3 B = triangle->B;
        Vec3 C = triangle->C;

        Vec3 normal = cross(B - A, C - A).normalize();
        file.write(reinterpret_cast<char*>(&normal), sizeof(normal));

        file.write(reinterpret_cast<char*>(&A), sizeof(A));
        file.write(reinterpret_cast<char*>(&B), sizeof(B));
        file.write(reinterpret_cast<char*>(&C), sizeof(C));


        uint16_t attribute;
        file.write(reinterpret_cast<char*>(&attribute), sizeof(attribute));
    }



}
/*
//Write to STL File
void WriteSTLFile(const string& filename, RayTracer& rayTracer) {
    cout << "Writing STL File." << endl;

    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    file.write("Generated STL file", 80);
    uint32_t triangleCount = 0;

    for (BVHNode* object : rayTracer.objects) {
        triangleCount += object->triangles.size();
    }

    file.write(reinterpret_cast<char*>(&triangleCount), sizeof(triangleCount));

    for (BVHNode* object : rayTracer.objects) {
        for (Triangle* triangle : object->triangles) {
            Vec3 A = triangle->A;
            Vec3 B = triangle->B;
            Vec3 C = triangle->C;

            Vec3 normal = cross(B - A, C - A).normalize();
            file.write(reinterpret_cast<char*>(&normal), sizeof(normal));

            file.write(reinterpret_cast<char*>(&A), sizeof(A));
            file.write(reinterpret_cast<char*>(&B), sizeof(B));
            file.write(reinterpret_cast<char*>(&C), sizeof(C));


            uint16_t attribute;
            file.write(reinterpret_cast<char*>(&attribute), sizeof(attribute));
        }
    }

    

    file.close();
}
*/


BVHNode* CreateSphere(const float radius, const int numLat, const int numLong) 
{
    vector<Triangle*> triangles;

    float theta = 0;
    float phi = 0;

    float  delTheta = numbers::pi / numLat;
    float delPhi = 2 * numbers::pi / numLong;

    //Iterate through all Latitudes

    for (int i = 0; i < numLat; i++) {


        float nextTheta = theta + delTheta;

        phi = 0;

        //Iterate through all longitudes
        for (int j = 0; j < numLong; j++) {

            float nextPhi = phi + delPhi;

            Vec3 v1 = FromPolar(radius, theta, phi);

            Vec3 v2 = FromPolar(radius, theta, nextPhi);

            Vec3 v3 = FromPolar(radius, nextTheta, phi);

            Vec3 v4 = FromPolar(radius, nextTheta, nextPhi);

            if (i == 0) {
               
                Triangle* triangle = new Triangle(v4, v3, v1);
                triangles.push_back(triangle);

            } else if (i == numLat - 1) {
        
                Triangle* triangle = new Triangle(v3, v2, v1);
                triangles.push_back(triangle);


            } else {

                Triangle* triangleA = new Triangle(v1, v2, v3);

                Triangle* triangleB = new Triangle(v4, v3, v2);

                triangles.push_back(triangleA);

                triangles.push_back(triangleB);

            }


            phi = nextPhi;
        }
        theta = nextTheta;
    }

	Vec3 upper = Vec3(radius, radius, radius);
	Vec3 lower = Vec3(-radius, -radius, -radius);

	BVHNode* sphere = BuildBVH(triangles, lower, upper, -1);
    
    return sphere;

}


void CreateObjects(RayTracer& rayTracer) 
{
    BVHNode* sphere = CreateSphere(0.15, 100, 100);


    rayTracer.objects.push_back(sphere);

    vector<Triangle*> triangles = vector<Triangle*>();

    //Create floor

    Vec3 v1(-0.6, -0.3, 0.7);
    Vec3 v2(0.6, -0.3, 0.7);
    Vec3 v3(-0.6, -0.3, -0.7);
    Vec3 v4(0.6, -0.3, -0.7);

    Triangle* triangle = new Triangle(v1, v2, v3);

    triangles.push_back(triangle); 

    triangle = new Triangle(v2, v4, v3);

    triangles.push_back(triangle);

    //Create left wall

    Vec3 v5(-0.6, 0.3, 0.7);
    Vec3 v6(-0.6, 0.3, -0.7);

    triangle = new Triangle(v1, v3, v5);

    triangles.push_back(triangle);
    
    triangle = new Triangle(v5, v3, v6);

    triangles.push_back(triangle);

    //Create back wall
    Vec3 v7(0.6, 0.3, -0.7);

    triangle = new Triangle(v3, v4, v6);

    triangles.push_back(triangle);

    triangle = new Triangle(v6, v4, v7);
    
    triangles.push_back(triangle);

	Vec3 upper = Vec3(0.6, 0.3, 0.7);
	Vec3 lower = Vec3(-0.6, -0.3, -0.7);
	//

	BVHNode* room = BuildBVH(triangles, lower, upper, -1);

    rayTracer.objects.push_back(room);

}

void RayTracer::GetImage(vector<unsigned char>& image) 
{

    for (int h = 0; h < height; h++) {

        float percentDone = static_cast<float>(h) / height * 100.0f;

        cout << percentDone << "% done." << endl;
        
        for (int w = 0; w < width; w++) {

			float i = static_cast<float>(w) / width;
			float j = static_cast<float>(h) / height;

			if (i == 0.5 && j == 0.5) {
				cout << "Center" << endl;
			}

            Vec3 origin = camera.UpperLeft() +
                i * camera.SensorW() * camera.right -
                j * camera.SensorH() * camera.up;

            Vec3 magnitude = (origin - camera.origin).normalize();

            Ray ray(origin, magnitude);
            Vec3 color = GetColor(ray, maxDepth);
            //Convert color to values of 255
            color *= 255;

            unsigned char r, g, b, a;
            r = static_cast<unsigned char>(color.x);
            g = static_cast<unsigned char>(color.y);
            b = static_cast<unsigned char>(color.z);
            a = 255;
            image.push_back(r);
            image.push_back(g);
            image.push_back(b);
            image.push_back(a);
        }
        
    }
}

Vec3 RayTracer::GetColor(const Ray& ray, const int depth)
{
    //Define very small limit
    constexpr float epsilon = 1e-5f;

    //Background color
    Vec3 up = Vec3(0, 1, 0);

    float dotProduct = dot(ray.direction, up);

    float gradient = (1 - dotProduct) / 2;
    //Gradient from blue to white
    Vec3 background = Vec3(gradient, gradient, 1);

    if (depth == 0) return background;

	float t = numeric_limits<float>::max();
    Triangle* hitTriangle = nullptr;
	Ray hitNormal;

    for (BVHNode* object : objects) {
        vector<Triangle*> hitTriangles = vector<Triangle*>();

        float ttemp = object->hit(ray, hitTriangles);

		if (ttemp <= 0 || ttemp >= t) continue;

		for (Triangle* triangle : hitTriangles) {
			Ray normal;

			float hitT = triangle->hit(ray, normal);

			if (hitT > 0 && hitT < t) {
				hitTriangle = triangle;
				hitNormal = normal;
				t = hitT;
			}
		}
    }
    
	//Get color from closest object
    if (hitTriangle != nullptr) {

        Material material = hitTriangle->material;

        //Calculate reflected ray
        Ray reflectedRay = Ray();
        reflectedRay.direction = ray.direction - 2 * dot(ray.direction, hitNormal.direction) * hitNormal.direction;
        reflectedRay.origin = hitNormal.origin + reflectedRay.direction * epsilon;

        //Check if in shadow
        if (shadows) {
            Ray shadowRay = Ray();
            shadowRay.direction = -1 * sun.direction;
            shadowRay.origin = hitNormal.origin + shadowRay.direction * epsilon;

            Ray norm;

            for (BVHNode* object : objects) {
                vector<Triangle*> hitTriangles = vector<Triangle*>();

                float ttemp = object->hit(shadowRay, hitTriangles);

                if (ttemp <= 0) continue;

				for (Triangle* triangle : hitTriangles) {
					float Ttemp = triangle->hit(shadowRay, norm);
					if (Ttemp > 0) {
                        return material.kr * GetColor(reflectedRay, depth - 1);
					}
				}

            }
            
        }

        

        //Calculate diffuse
        float dotProduct = dot(-1 * sun.direction, hitNormal.direction);
        float brightness = max(0.0f, dotProduct);

        //Calculate specular
        Vec3 V = ray.direction.normalize();

        Vec3 R = 2 * dot(hitNormal.direction, sun.direction) * hitNormal.direction - sun.direction;

        float specular = max(0.0f, dot(R, V));

        specular = pow(specular, material.s);


        //Calculate color
        Vec3 color = material.kd * material.color * brightness
            + material.ks * specular * sun.color
            + material.kr * GetColor(reflectedRay, depth - 1);

        color.x = min(1.0f, color.x);

        color.y = min(1.0f, color.y);

        color.z = min(1.0f, color.z);


        return color;
    }

    
	return background;
}

