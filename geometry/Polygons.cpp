#include<bits/stdc++.h>
#include "Points and Lines.cpp"

using namespace std;
typedef Point<double> point;
#define PI 3.14159265358979323

// Convex Hull
vector<point> andrew(vector<point> &P) {
    int n = P.size(), k = 0;
    vector<point> H(2*n);
    sort(P.begin(), P.end());
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && !ccw(H[k-2], H[k-1], P[i])) k--;
        H[k++] = P[i];
    }
    // Build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && !ccw(H[k-2], H[k-1], P[i])) k--;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}

double heron(double a, double b, double c){
    double s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double area(const vector<point> &P) {
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size()-1; i++) 
    result += (P[i].x * P[i+1].y - P[i+1].x * P[i].y);
  return abs(result) / 2.0; }
  
//returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((int)P.size() == 0) return false;
  double sum = 0;   
  for (int i = 0; i < (int)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);                
    else sum -= angle(P[i], pt, P[i+1]); }                 
  return fabs(fabs(sum) - 2*PI) < EPS; }
  
// $O(log n)$ Seulement pour les convexes (ordonnes ccw)!
bool inConvexPolygon(point q, vector<point> const &p) {
	if (cross(p[0], p[1], q)<0 || cross(p[p.size() - 2], p[0], q)<0)
		return false;
	int ini = 1, fin = p.size() - 2, mid;
	while (ini != fin - 1) {
		mid = (ini + fin) / 2;
		if (cross(p[0], p[mid], q) < 0) fin = mid;
		else ini = mid;
	}
	if (cross(p[ini], p[fin], q)<0) return false;
	return true;
}

// Cut Polygon 

// returns the point on segment $PQ$ that is closest to line $AB$ 
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
  double u = abs(a * p.x + b * p.y + c), v = abs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }

// Cuts a polygon, keeping only the points on the left side of the directed line a->b 
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
    double left1 = toVec(a, b).cross(toVec(a, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = toVec(a, b).cross(toVec(a, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)        // edge (Q[i], Q[i+1]) crosses line ab
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());        // make P's first point = P's last point
  return P; }                                
