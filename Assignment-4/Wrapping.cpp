// A C++ implementation of Gift Wrapping algorithm
#include <bits/stdc++.h>
using namespace std;
 
struct Point
{
    int x, y;
};
// To find orientation of ordered triplet (p, q, r).
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y); 
    if (val == 0) 
    return 0; 
    if(val > 0)
    return 1;
    return 2;
}
void convexHull(Point points[], int n)
{
    if (n < 3) return;
    vector<Point> hull;
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    do
    {
        hull.push_back(points[p]);
        // Search for a point 'q' such that orientation(p, x, q) is counterclockwise for all points 'x'.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        // Set p as q for next iteration, so that q is added to result 'hull'
        p = q;
 
    } while (p != l);  
    //Output
    for (int i = 0; i < hull.size(); i++)
    {
        cout << "(" << hull[i].x << ", "<< hull[i].y << ")\n";
    }
}
int main()
{
    int n;
    cin>>n;
    Point *P= new Point[n];
    for(int i=0;i<n;i++)
    {
       cin>>P[i].x>>P[i].y;
    }
    float t0 = clock();
    convexHull(P, n);
    float t1 = clock();
    cout<<"Total time:"<<(t1-t0)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}

//Test case1-Total time:2.9e-05 seconds
//Test case2-Total time:0.000266 seconds
//Test case3-Total time:0.000438 seconds
//Test case4-Total time:0.000532 seconds
//Test case5-Total time:0.001057 seconds