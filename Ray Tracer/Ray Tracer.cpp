// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"


string filename = "output.ppm";
int width = 1920;
int height = 1080;

Camera camera;

Vec3 background;

Sphere sphere;

Sun sun;

int main()
{
    vector<vector<Vec3>> image;

    float aspect_ratio = static_cast<float>(width) / height;

    camera = Camera();

    camera.SetAspectRatio(aspect_ratio);

    sphere = Sphere(Vec3(0, 0, -2.0f), 0.5f);

    sphere.SetColor(Vec3(255, 0, 80));

    sun = Sun(Vec3(0, 0.5, 0.5));

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
        temp.clear();
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

    magnitude = magnitude.normalize();

    Ray ray(origin, magnitude);

    if (hits_sphere(sphere, ray)) 
    {
        float brightness = Vec3::dot(sun.direction, ray.direction);
        if (brightness < 0) brightness = 0;
        return sphere.Color() * brightness;
    }

    //Gradient from blue to white
    return Vec3( (1-j) * 255, (1-j) * 255, 255);
}

bool hits_sphere(const Sphere sphere, Ray& ray) 
{
    Vec3 OC = ray.origin - sphere.Center();
    double a = Vec3::dot(ray.direction, ray.direction);
    double b = 2 * Vec3::dot(ray.direction, OC);
    double c = Vec3::dot(OC, OC) - sphere.Radius() * sphere.Radius();
    double rad = b * b - 4 * a * c;

    if (rad < 0) return false;

    double t;
    if (rad == 0) { t = -b / (2 * a); }

    else t = min(-b + sqrt(rad), -b - sqrt(rad)) / (2 * a);

    Vec3 Phit = ray.origin + ray.direction * t;

    Vec3 Nhit = Phit - sphere.Center();

    ray.origin = Phit;

    ray.direction = Nhit.normalize();


    return true;
}


void WritePPM(const vector<vector<Vec3>>& image, const string& filename) {
    ofstream file(filename, ios::binary);

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
    //file << "P3\n";
    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";

    cout << "Start writing to file" << endl;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            Vec3 color = image[i][j];
            unsigned char red = static_cast<unsigned char>(color.X());
            unsigned char green = static_cast<unsigned char>(color.Y());
            unsigned char blue = static_cast<unsigned char>(color.Z());
            file.write((char*)&red, 1);
            file.write((char*)&green, 1);
            file.write((char*)&blue, 1);

        }
    }

    cout << "Done Writing to file" << endl;

    file.close();
}
