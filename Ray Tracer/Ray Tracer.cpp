// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"


string filename = "output.ppm";
int width = 640;
int height = 360;

Camera camera;

Vec3 background;

Sphere sphere;

int main()
{
    vector<vector<Vec3>> image;

    float aspect_ratio = static_cast<float>(width) / height;

    camera = Camera();

    camera.SetAspectRatio(aspect_ratio);

    sphere = Sphere(Vec3(1, 0, -2.0f), 0.5f);

    background = Vec3(0, 0, 0);

    cout << "Printing Image" << endl;
    GetImage(image, width, height);

    try 
    {
        cout << "Writing to File" << endl;
        WritePPM(image, filename);
    }
    catch(exception ex) 
    {
        cout << "Error" << endl;
        return 1;
    }

    return 0;
}

void GetImage(vector<vector<Vec3>>& image, const int width, const int height) 
{
    vector<Vec3> temp;
    for (int w = 0; w < width; w++) {
        temp = {};
        for (int h = 0; h < height; h++) {
            Vec3 color = GetColor(static_cast<float>(w) / width, static_cast<float>(h) / height);
            temp.push_back(color);
        }
        image.push_back(temp);
    }
}


//i and j go from [0, 1]
Vec3 GetColor(const float i, const float j) 
{
    Vec3 origin = camera.LowerCorner() + 
        i * camera.SensorW() * camera.Right() + 
        j * camera.SensorH() * camera.Up();

    Vec3 magnitude = origin - camera.Origin();

    magnitude.normalize();

    Ray ray(origin, magnitude);

    if (hits_sphere(sphere, ray)) 
    {
        return Vec3(255, 0, 0);
    }
    
    //Gradient from blue to white
    return Vec3( (1-j) * 255, (1-j) * 255, 255);
}

bool hits_sphere(const Sphere sphere, const Ray ray) 
{
    Vec3 OC = ray.Origin() - sphere.Center();
    double a = Vec3::dot(ray.Direction(), ray.Direction());
    double b = 2 * Vec3::dot(ray.Direction(), OC);
    double c = Vec3::dot(OC, OC) - sphere.Radius() * sphere.Radius();
    double rad = b * b - 4 * a * c;

    if (rad <= 0) return false;

    return true;
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

    cout << width << " " << height << endl;

    // Write PPM header
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";
    
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Vec3 color = image[i][j];
            file << color.X() << " " << color.Y() << " " << color.Z() << "\n";
        }
    }

    file.close();
}
