// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"

string filename = "output.png";
int width = 1920;
int height = 1080;

Camera camera;

Vec3 background;

Sphere sphere;

Sun sun;

int main()
{
    vector<unsigned char> image;

    float aspect_ratio = static_cast<float>(width) / height;

    camera = Camera();

    camera.SetAspectRatio(aspect_ratio);

    sphere = Sphere(Vec3(0, 0, -2.0f), 0.5f);

    sphere.SetColor(Vec3(255, 0, 80));

    sun = Sun(Vec3(0, -1, -0.25));

    cout << "Printing Image" << endl;
    GetImage(image, width, height);

    cout << "Writing to File" << endl;
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error) {
        cout << "Error" << endl;
        return 1;
    }

    return 0;
}

void GetImage(vector<unsigned char>& image, const int width, const int height) 
{
    for (int h = 0; h < height; h++) {
        
        for (int w = 0; w < width; w++) {
            Vec3 color = GetColor(static_cast<float>(w) / width, static_cast<float>(h) / height);
            //Convert color to values of 255
            color *= 255;

            unsigned char r, g, b, a;
            r = static_cast<unsigned char>(color.X());
            g = static_cast<unsigned char>(color.Y());
            b = static_cast<unsigned char>(color.Z());
            a = 255;
            image.push_back(r);
            image.push_back(g);
            image.push_back(b);
            image.push_back(a);
        }
        
    }
}


//i and j go from [0, 1]
Vec3 GetColor(const float i, const float j) 
{

    Vec3 origin = camera.UpperLeft() + 
        i * camera.SensorW() * camera.Right() - 
        j * camera.SensorH() * camera.Up();

    Vec3 magnitude = origin - camera.Origin();

    magnitude = magnitude.normalize();

    Ray ray(origin, magnitude);

    Ray normal;

    if (hits_sphere(sphere, ray, normal)) 
    {   
        //Calculate brightness
        float brightness = 0;
        float dotProduct = Vec3::dot(sun.direction, normal.direction);
        if (dotProduct < 0) 
        {
            brightness = -1 * dotProduct;
        }

        //Calculate specular
        float s = 50.0f;

        float ks = 0.2;

        Vec3 V = -1 * ray.direction.normalize();

        Vec3 R = 2 * Vec3::dot(normal.direction, sun.direction) * normal.direction - sun.direction;

        float specular = min(0.0, Vec3::dot(R, V));
        
        specular *= -1;

        specular = pow(specular, s);

        Vec3 specularColor = Vec3(1, 1, 1);

        Vec3 color = sphere.Color() * brightness + ks * specular * specularColor;

        color.x = min(1.0f, color.x);

        color.y = min(1.0f, color.y);

        color.z = min(1.0f, color.z);


        return color;
    }

    //Gradient from blue to white
    return Vec3(j * 255, j * 255, 255).normalize();
}

bool hits_sphere(const Sphere sphere, const Ray& ray, Ray& normal) 
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

    normal.origin = Phit;

    normal.direction = Nhit.normalize();


    return true;
}