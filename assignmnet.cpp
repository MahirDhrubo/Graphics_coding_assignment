#include<bits/stdc++.h>
#include <filesystem>
#include "bitmap_image.hpp"

using namespace std;
using std::filesystem::current_path;

class Color{
public:
    int r, g, b;

    Color(int r=0, int g=0, int b=0){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setVal(int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void operator = (const Color &color){
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
    }
};

class Point{
public:
    double x,y,z;
    Point(double x=0, double y=0, double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point(const Point &point){
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
    }

    void normalize(){
        double magnitude = sqrt(x*x+y*y+z*z);
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }

    double distanceFrom(Point point){
        return sqrt(pow(x-point.x,2) + pow(y-point.y,2) + pow(z-point.z,2));
    }

    void operator = (const Point &point){
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
    }

    Point operator + (const Point &point){
        return Point(this->x + point.x,this->y + point.y,this->z + point.z);
    }

    Point operator - (const Point &p){
        return Point(x-p.x, y-p.y, z-p.z);
    }

    Point operator * (const double &d){
        return Point(x*d, y*d, z*d);
    }

    Point cross(const Point &b) {
		return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}

	double dot(const Point &b) {
		return (x * b.x) + (y * b.y) + (z * b.z);
	}


    void print(string s=""){
        cout << s << endl;
        cout << "("<<x <<","<< y <<","<<z<<")"<<endl;
    }
};

void swap(Point &p1, Point &p2){
    swap(p1.x,p2.x);
    swap(p1.y,p2.y);
}

int img_width, img_height;

class Line{
public:
    Point p1, p2;
    Color color;
    Line(Point a, Point b, Color color){
        if(a.x > b.x){
            swap(a,b);
        }
        this->p1 = a;
        this->p2 = b;
        this->color = color;
    }

    void print(string s=""){
        cout << s <<" line " << endl;
        p1.print();
        p2.print();
        cout << " ++++ line ++++ " << endl;
    }

    void draw(bitmap_image &image){
        //bitmap_image image(img_width, img_height);
        double m = (p2.y-p1.y) / (p2.x-p1.x);
        int dx = p2.x-p1.x;
        int dy = p2.y-p1.y;
        int x = p1.x, y = p1.y;

        image.set_pixel(x, img_height - y, color.r, color.g, color.b);
        
        if(m >=0 && m <= 1){
            int d = 2*dy - dx;
            int incrE = 2*dy;
            int incrNE = 2 * (dy-dx);
            while(x < p2.x){
                //cout << x << " "<<y<<endl;
                if(d <= 0){
                    d += incrE;
                    x++;
                }
                else{
                    d += incrNE;
                    x++; 
                    y++;
                }
                //cout << color.r <<" " << color.g <<" "<<color.b << endl;
                image.set_pixel(x, img_height - y, color.r, color.g, color.b);
            }
        }
        else if(m < 0 && m >= -1){
            int d = 2*dy + dx;
            int incrE = 2*(dy+dx);
            int incrNE = 2*dy;

            while(x < p2.x){
                //cout  <<d <<" "<< y << endl;
                //cout << x << " "<<y<<endl;
                if(d <= 0){
                    d += incrE;
                    x++;
                    y--;
                }
                else{
                    d += incrNE;
                    x++; 
                }
                //cout << color.r <<" " << color.g <<" "<<color.b << endl;
                image.set_pixel(x, img_height - y, color.r, color.g, color.b);
            }
        }
        else if(m > 1){
            if(p1.y > p2.y){
                swap(p1,p2);
            }
            int d = 2*dy - dx;
            int incrE = -2*dx;
            int incrNE = 2 * (dy-dx);
            x = p1.x;
            y = p1.y;
            //cout << y <<" "<<p2.y <<" "<<p1.y << endl;
            while(y < p2.y){
                //cout << x << " "<<y<<endl;
                if(d > 0){
                    d += incrE;
                    y++;
                }
                else{
                    d += incrNE;
                    x++; 
                    y++;
                }
                //cout << color.r <<" " << color.g <<" "<<color.b << endl;
                image.set_pixel(x, img_height - y, color.r, color.g, color.b);
            }
        }
        else{
            if(p1.y < p2.y){
                swap(p1,p2);
            }
            int d = 2*dy + dx;
            int incrE = 2*(dy+dx);
            int incrNE = 2*dx;
            x = p1.x;
            y = p1.y;
            cout << y <<" "<<p2.y <<" "<<p1.y << endl;
            while(y > p2.y){
                //cout  <<d <<" "<< y << endl;
                cout << x << " "<<y<<endl;
                if(d > 0){
                    d += incrE;
                    x++;
                    y--;
                }
                else{
                    d += incrNE;
                    y--; 
                }
                //cout << color.r <<" " << color.g <<" "<<color.b << endl;
                image.set_pixel(x, img_height - y, color.r, color.g, color.b);
            }
        }
    }
};

int totalLines;
vector<Line> lines;

void imageGeneration(){
    bitmap_image image(img_width, img_height);
    for(int i = 0; i < img_width; i++){
        for(int j = 0; j < img_height; j++){
            image.set_pixel(i,j, 255, 255 ,255);
        }
    }

    for(int i = 0; i < totalLines; i++){
        lines[i].draw(image);
    }
    string out_dir(current_path());
    out_dir += "/1_R.bmp";
    cout << out_dir  << endl;
    image.save_image(out_dir);
}


void fileInput(string file_name){
    ifstream scene(file_name);
    scene >> img_width >> img_height;
    scene >> totalLines;

    for(int i = 0; i < totalLines; i++){
        double x1,y1,x2,y2;
        scene >> x1 >> y1 >> x2 >> y2;
        int r,g,b;
        scene >> r >> g >> b;
        lines.push_back(Line(Point(x1,y1), Point(x2,y2), Color(r,g,b)));
    }

    for(int i = 0 ; i < totalLines; i++) lines[i].print();

}

int main()
{
    cout << " running...." << endl;
    fileInput("input.txt");
    //cout << current_path() << endl;
    imageGeneration();

    return 0;
}
