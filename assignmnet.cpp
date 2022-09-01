#include<bits/stdc++.h>
using namespace std;

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

class Line{
public:
    Point p1, p2;
    Line(Point a, Point b){
        this->p1 = a;
        this->p2 = b;
    }

    print(string s=""){
        cout << s <<" line " << endl;
        p1.print();
        p2.print();
        cout << " ++++ line ++++ " << endl;
    }
};

int img_width, img_height;
int totalLines;
vector<Line> lines;


void fileInput(string file_name){
    ifstream scene(file_name);
    scene >> img_width >> img_height;
    scene >> totalLines;

    for(int i = 0; i < totalLines; i++){
        double x1,y1,x2,y2;
        scene >> x1 >> y1 >> x2 >> y2;
        lines.push_back(Line(Point(x1,y1), Point(x2,y2)));
    }

    for(int i = 0 ; i < totalLines; i++) lines[i].print();

}

int main()
{
    cout << " running...." << endl;
    fileInput("input.txt");


    return 0;
}
