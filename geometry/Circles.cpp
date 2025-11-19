#include<bits/stdc++.h>
#include "Points and Lines.cpp"
#include "Polygons.cpp"

using namespace std;
typedef Point<double> point;

// Retourne par reference le centre d'un cercle qui passe par 2 points et a un rayon donne
bool circle2PtsRad(point p1, point p2, double r, point &c) {
  double d2 = (p1.x - p2.x) * (p1.x - p2.x) + 
              (p1.y - p2.y) * (p1.y - p2.y);
  double det = r * r / d2 - 0.25;
  if (det < 0.0) return false;
  double h = sqrt(det);
  c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
  return true;
}

// Rayon du cercle inscrit donnees les longueurs des cotes
double rInCircle(double ab, double bc, double ca) {
  return heron(ab, bc, ca) / (0.5 * (ab+ bc+ca)); } 
  
// Retourne le centre et le rayon du cercle inscrit d'un triangle (par reference)
bool inCircle(point p1, point p2, point p3, point &ctr, double &r) {
  r = rInCircle(p1.dist(), p2.dist(), p3.dist());
  if (abs(r) < EPS) return false; // no inCircle center
  line l1, l2;// compute these two angle bisectors
  double ratio = dist(p1, p2) / dist(p1, p3);
  point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1);
  ratio = dist(p2, p1) / dist(p2, p3);
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);
  areIntersect(l1, l2, ctr);// get their intersection point
  return true; 
}
// Rayon du cercle circonscrit donnees les longueurs des cotes
double rCircumCircle(double ab, double bc, double ca) {
  return ab * bc * ca / (4.0 * heron(ab, bc, ca)); } 
// Retourne le centre et le rayon du cercle circonscrit d'un triangle (par reference)
bool circumCircle(point p1, point p2, point p3, point &ctr, double &r){
  double a = p2.x - p1.x, b = p2.y - p1.y, c = p3.x - p1.x, d = p3.y - p1.y;
  double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
  if (fabs(g) < EPS) return false;
  ctr.x = (d*e - b*f) / g; ctr.y = (a*f - c*e) / g;
  r = dist(p1, ctr);  // r = distance from center to 1 of the 3 points
  return true; 
}

// Retourne l'orthocentre d'un triangle. r n'a pas de sens ici
bool orthocenter(point a, point b, point c, point & ctr, double & r){
	return circumCircle(a+b-c,b+c-a,c+a-b, ctr, r);
}