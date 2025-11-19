#include<bits/stdc++.h>
using namespace std;
#define EPS 1e-6

// Point template, use long long or double, avoid int.
template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<double> point;

// Vector a->b
point toVec(point a, point b) { return point(b.x-a.x, b.y-a.y); }
point scale(point v, double s) { return point(v.x*s, v.y*s);}
point translate(point p, point v) { return point(p.x + v.x, p.y + v.y);}
double cross(point a, point b, point c) { return toVec(a, b).cross(toVec(b, c)); }
double dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y);}
double distSq(point p1, point p2) { 
    return (p1.x - p2.x)*(p1.x - p2.x)+ (p1.y - p2.y)*(p1.y - p2.y);
}

// pour accepter des points colineaires remplacer > par >= et ajouter un EPS peut-etre
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return (toVec(p, q).cross(toVec(p, r))) > 0;
}
bool collinear(point p, point q, point r) {
    return abs(toVec(p, q).cross(toVec(p, r))) < EPS;
}
int insideCircle(point p, point c, double r) {
    double eucSq = distSq(p, c);
    double rSq = r*r;
    if (fabs(eucSq - rSq) > EPS && eucSq < rSq) return 0; // inside
    else if (fabs(eucSq - rSq) < EPS) return 1; // border
    else return 2; // outside
}
//returns $\angle AOB$ in rad
double angle(point a, point o, point b) { 
	point oa = toVec(o, a), ob = toVec(o, b);
	return acos(oa.dot(ob) / sqrt(oa.dist2() * ob.dist2()));
}
// distance from p to the line defined by two points a and b.
// The closest point to p on the segment is stored in c. 
double distToLine(point p, point a, point b, point &c) {
    point ap = toVec(a, p), ab = toVec(a, b);
    double u = ap.dot(ab) / ab.dist2();
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

// distance from p to the segment defined by two points a and b.
// The closest point to p on the segment is stored in c. 
double distToSegment(point p, point a, point b, point &c) {
    auto ap = toVec(a, p), ab = toVec(a, b);
    double u = ap.dot(ab) / ab.dist2();
    if (u < 0.0) {
        c = point(a.x, a.y);
        return ap.dist();
    } else if (u > 1.0) {
        c = point(b.x, b.y);
        return toVec(p, b).dist();
    } else return distToLine(p, a, b, c);
}

// Line representation using equation $ax+by+c=0$
struct line { double a, b, c; };
// Line that passes through two points, stored in the third parameter.
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x - p2.x) < EPS) {// vertical 
    l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           
  } else {
    l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x); l.b = 1.0; 
    l.c = -(double)(l.a * p1.x) - p1.y;
} }

bool areParallel(line l1, line l2) { // check coefficients a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
  
// Solves the linear system to find the intersection of two lines
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false; // no intersection
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
  else                  p.y = -(l2.a * p.x + l2.c);
  return true; 
}