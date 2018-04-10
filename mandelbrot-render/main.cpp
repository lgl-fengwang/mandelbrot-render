#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

double escape_radius = 4.0; //逃逸半径
int max_iter_number = 1000; //最大迭代次数

double ox = -0.743643135; //原点x坐标
double oy = 0.131825963; //原点y坐标
double width = 0.000014628; //图像宽
double ratio = 0.75; //高宽比

int image_width = 800;

int image_height = (int)(image_width * ratio);
double pixel_size = width / image_width;
double coffset = image_width / 2;
double roffset = image_height / 2;

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

Pixel Interpolation(int i, Pixel rgb1, Pixel rgb2);

int main() {
    string filename;
    cout << "输入文件名:";
    cin >> filename;
    ofstream file;
    cin.get();
    cout << "图形生成中..." << endl;
    file.open(filename + "-" +  to_string(escape_radius) + "-" + to_string(max_iter_number) + "-" + to_string(ox) + "-" + to_string(oy) + ".ppm", ios::trunc);
    file << "P6 " << image_width << " " << image_height << " " << 255 << " ";
    Pixel rgb;
    for (int row = 0; row < image_height; ++row) {
        for (int col = 0; col < image_width; ++col) {
            double cx = (col - coffset) * pixel_size + ox;
            double cy = (row - roffset) * pixel_size + oy;
            double x = 0;
            double y = 0;
            double temp;
            double distance;
            int i = 0;
            while (i < max_iter_number) {
                temp = x * x - y * y + cx;
                y = 2 * x * y + cy;
                x = temp;
                ++i;
                distance = x * x + y * y;
                if (distance >= escape_radius) {
                    Pixel rgb1 = { 0, 0, 0 };
                    Pixel rgb2 = { 255, 255, 255 };
                    rgb = Interpolation(i, rgb1, rgb2);
                    break;
                }
            }
            if (i == max_iter_number) {
                rgb = { 0, 0, 0 };
            }
            file.write((char*)&rgb, sizeof(rgb));
        }
    }
    cout << "图形生成完毕，保存至\"" << filename + "-" + to_string(escape_radius) + "-" + to_string(max_iter_number) + "-" + to_string(ox) + "-" + to_string(oy) + ".ppm\"" << endl;
    cin.get();
}

Pixel Interpolation(int i, Pixel rgb1, Pixel rgb2) {
    double f = i * 1.0 / max_iter_number;
    Pixel rgb;
    int a, b, c;
    //a = floor((1 - f) * rgb1.r + f * rgb2.r + 5);
    a = 0;
    rgb.r = (unsigned char) a;
    b = floor((1 - f) * rgb1.g + f * rgb2.g + 5);
    //b = 0;
    rgb.g = (unsigned char)b;
    c = floor((1 - f) * rgb1.b + f * rgb2.b + 5);
    //c = 0;
    rgb.b = (unsigned char)c;
    return rgb;
}