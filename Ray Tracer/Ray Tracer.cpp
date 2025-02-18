// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"

string filename = "output.png";
int width = 2560;
int height = 1440;

Camera camera;

Vec3 background;

vector<Object*> objects;

Sun sun;

int main()
{
    vector<unsigned char> image;

    float aspect_ratio = static_cast<float>(width) / height;

    camera = Camera();

    camera.SetAspectRatio(aspect_ratio);

    Sphere* sphere = new Sphere();

    sphere->center = Vec3(0, 0, -3);

    sphere->material.color = Vec3(255, 0, 0) / 255;

    objects.push_back(sphere);

    sun = Sun();
    sun.direction = Vec3(0, -1, -1).normalize();

    cout << "Printing Image" << endl;
    GetImage(image, width, height);

    cout << "Writing to File" << endl;
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error) {
        cout << "Error" << endl;
        return 1;
    }

    delete sphere;

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

    for (Object* object : objects) {

        if (object->hit(ray, normal)) {
            Material material = object->material;

            //Calculate brightness
            float brightness = 0;
            float dotProduct = Vec3::dot(sun.direction, normal.direction);
            if (dotProduct < 0)
            {
                brightness = -1 * dotProduct;
            }

            //Calculate specular
            Vec3 V = -1 * ray.direction.normalize();

            Vec3 R = 2 * Vec3::dot(normal.direction, sun.direction) * normal.direction - sun.direction;

            float specular = min(0.0, Vec3::dot(R, V));

            specular *= -1;

            specular = pow(specular, material.s);



            Vec3 color = material.kd * material.color * brightness 
                + material.ks * specular * material.specularColor;

            color.x = min(1.0f, color.x);

            color.y = min(1.0f, color.y);

            color.z = min(1.0f, color.z);


            return color;
        }
    }

    //Gradient from blue to white
    return Vec3(j, j, 1);
}

