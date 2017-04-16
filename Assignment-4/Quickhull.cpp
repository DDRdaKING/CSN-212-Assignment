//A C++ implementation of Quickhull algorithm 
#include <bits/stdc++.h>
using namespace std;

struct point
{
    int x, y;
};
bool comp(point a, point b)
{  
    return (a.x<b.x);
}
int determinant(point p, point q, point r)
{   
    return (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y);
}
void findPartialHull(vector<point> &arr, vector<point> &result, point p1, point pn)
{
    vector<point> s1 = vector<point>();   //holds points of a part
    for (vector<point>::iterator it = arr.begin(); it < arr.end(); it++)
    {  
        if (determinant(p1,pn,*it) > 0)
        {    
            //if the point is on the left of p1-->pn line put it into the vector
            s1.push_back(*it); 
        }
    }
    if (s1.empty())
    {    
        //if s1 is empty, write p1 to result array; base case
        result.push_back(p1);
    } 
    else 
    {    
        float maxDist = 0;  //distance to p1-->pn line
        point pmax;    //hold the pointer of pmax
        float dist; 
        float length = sqrt(pow(p1.x - pn.x, 2) + pow(p1.y - pn.y, 2)); //length of p1-->pn line
        for (vector<point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            dist = determinant(p1,pn,*it) / length; //distance(height) = area / length
            if (dist > maxDist)
            {    
                //find the point with max distance
                maxDist = dist;
                pmax = *it;
            }
        }
        //find points left to p1-->pmax and pmax-->pn
        vector<point> s11 = vector<point>();  //holds points left to p1-->pmax
        vector<point> s12 = vector<point>();  //holds points left to pmax-->pn
        for (vector<point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            //iterate s1 and find all points we are looking for
            if (determinant(p1,pmax,*it) > 0)
            {  
                //left to p1-->pmax
                s11.push_back(*it);
            } 
            else if (determinant(pmax,pn,*it) > 0)
            {   
                //left to pmax-->pn
                s12.push_back(*it);
            }
        }
        findPartialHull(s11, result, p1, pmax); //recursively search in s11
        findPartialHull(s12, result, pmax, pn); //recursively search in s12
    }
}
int main(){
    int n;
    cin>>n;
    vector<point> P = vector<point>();   //holds pointers of raw data
    vector<point> upper = vector<point>();    //holds the result of upper convex hull
    vector<point> lower = vector<point>();    //holds the result of lower convex hull
    for (int i=0;i<n;i++)
    {   
        point p;
        cin>>p.x>>p.y;
        P.push_back(p);
    }
    float t0 = clock();
    sort(P.begin(),P.end(),comp); //sort raw data in increasing order of x 
    findPartialHull(P, upper, P[0], P[n-1]);   //upper hull, line direction p1-->pn
    findPartialHull(P, lower, P[n-1], P[0]);   //lower hull, line direction pn-->p1
    sort(upper.begin(),upper.end(),comp); //sort result in increasing order of x
    sort(lower.begin(),lower.end(),comp);
    float t1 = clock();
    for (vector<point>::iterator it = upper.begin(); it < upper.end(); it++)
    {  
        //upper part, clock-wise
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    for (vector<point>::iterator it = lower.end()-1; it >= lower.begin(); it--)
    {
        //reverse iterating order for lower part; still clock-wise
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    cout << "Total time: " << (t1-t0)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}

//Test case1-Total time: 1.2e-05 seconds
//Test case2-Total time: 7.3e-05 seconds
//Test case3-Total time: 0.000537 seconds
//Test case4-Total time: 0.00032 seconds
//Test case5-Total time: 0.000623 seconds