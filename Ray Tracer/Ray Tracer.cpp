// Ray Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ray Tracer.h"

string filename = "output.png";
int width = 1920;
int height = 1080;

//TODO: Known bug. Colinear triangles

int main()
{
    vector<unsigned char> image;

	RayTracer rayTracer = RayTracer(filename, width, height);

    cout << "Printing Image" << endl;
    rayTracer.GetImage(image, width, height);

    cout << "Writing to File" << endl;
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error) {
        cout << "Error" << endl;
        return 1;
    }

    return 0;
}

//TODO: Modify function to read from a file instead
void RayTracer::CreateObjects() {
    //Create Sphere
    Sphere* sphere = new Sphere();
    sphere->center = Vec3(0, 0, -1);
    sphere->radius = 0.2;
    sphere->SetColor(Vec3(255, 0, 0));
    objects.push_back(sphere);

    //Create floor
    Vec3 v1(-0.6, -0.3, -0.7);
    Vec3 v2(0.6, -0.3, -0.7);
    Vec3 v3(-0.6, -0.3, -1.4);
    Vec3 v4(0.6, -0.3, -1.4);

    Vec3 color(0, 0, 200);

    Triangle* triangle1 = new Triangle();

    triangle1->A = v1;
    triangle1->B = v2;
    triangle1->C = v3;

    triangle1->SetColor(color);

    objects.push_back(triangle1);

    Triangle* triangle2 = new Triangle();

    triangle2->A = v2;
    triangle2->B = v4;
    triangle2->C = v3;

    triangle2->SetColor(color);

    objects.push_back(triangle2);


}

void RayTracer::GetImage(vector<unsigned char>& image, const int width, const int height) 
{
    for (int h = 0; h < height; h++) {
        
        for (int w = 0; w < width; w++) {
            Vec3 color = GetColor(static_cast<float>(w) / width, static_cast<float>(h) / height);
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

//i and j go from [0, 1]
Vec3 RayTracer::GetColor(const float i, const float j)
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

            //Check if in shadow
            Ray shadowRay = Ray();

            shadowRay.direction = -1 * sun.direction;
            shadowRay.origin = normal.origin + normal.direction * numeric_limits<float>::epsilon();

            Ray norm;

            for (auto object : objects) {
                if (object->hit(shadowRay, norm)) return Vec3();
            }

            //Calculate diffuse
            float dotProduct = dot(-1 * sun.direction, normal.direction);
            float brightness = max(0.0f, dotProduct);

            //Calculate specular
            Vec3 V = ray.direction.normalize();

            Vec3 R = 2 * dot(normal.direction, sun.direction) * normal.direction - sun.direction;

            float specular = max(0.0f, dot(R, V));


            specular = pow(specular, material.s);


            //Calculate color
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

