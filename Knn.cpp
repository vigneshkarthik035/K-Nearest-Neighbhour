#include<iostream>
#include<math.h>
#include<queue>
#include<set>
using namespace std;
struct point
{
	int x,y,label;
};
class myComparator
{
public:
	int operator()(const pair<double,int> &pt1,const pair<double,int> &pt2)
	{
		return pt1.first<pt2.first;
	}
};
void getInput(point *p,bool notnewPoint=1)
{
	cin>>p->x>>p->y;
	if(notnewPoint)
	{
		cout<<"\n\n Enter its class:\t";
		cin>>p->label;
	}
}
int distinctClassCount(point *p,int n)
{
	set<int> countSet;
	for(int i=0;i<n;i++)
	{
		countSet.insert((p+i)->label);
	}
	return countSet.size();
}
int distance(point *pt1,point *pt2)
{
	//cout<<"\n\n train "<<pt2->x<<" "<<pt2->y;
	return abs(pt1->x-pt2->x)+abs(pt1->y-pt2->y);/*This Manhatten you could also do with euclidean*/ 
}
void calculateDist(point *newPoint,point *train,priority_queue<pair<double,int>,vector<pair<double,int>>,myComparator> &pq,bool insert)
{
	int dist=distance(newPoint,train);
	//cout<<dist;
	if(insert)
	{
		pq.push(make_pair(dist,train->label));
	}
	else if(pq.top().first>dist)
	{
		pq.pop();
		pq.push(make_pair(dist,train->label));
	}
}
int findClass(priority_queue<pair<double,int>,vector<pair<double,int>>,myComparator> &pq,int classCount)
{
	int myMap[classCount+1]={0};
	while(!pq.empty())
	{
		pair<double,int> p=pq.top();
		pq.pop();
		myMap[p.second]+=1;
	}
	int maxInd=0;
	//cout<<"\n\n The occurences are:\t";
	for(int i=1;i<classCount+1;i++)
	{
		//cout<<" ("<<i<<","<<myMap[i]<<")";
		if(myMap[maxInd]<myMap[i])
		{
			maxInd=i;
		}
	}
	return maxInd;
}
void print(point *p,int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"\n\n The Point "<<i+1<<"\t"<<(p+i)->x<<" "<<(p+i)->y;
	}
}
void printpq(priority_queue<pair<double,int>,vector<pair<double,int>>,myComparator> pq)
{
	cout<<"\n\n The queue is\t";
	while(!pq.empty())
	{
		cout<<"("<<pq.top().first<<","<<pq.top().second<<")\t";
		pq.pop();
	}
}
int main()
{
	int k;
	int n;

	/*Input Segment*/

	cout<<"\n\n K-Nearest Neigbhour";
	cout<<"\n\n Enter the value for k:\t";
	cin>>k;
	cout<<"\n\n Enter the number of points:\t";
	cin>>n;
	point *p=new point[n];
	for(int i=0;i<n;i++)
	{
		cout<<"\n\n Enter the Coordinates for point "<<i+1<<":\t";
		getInput(p+i);
	}
	//print(p,n);print input points
	while(1)
	{
		point *newPoint=new point;
		cout<<"\n\n Enter the Coordinates of the new point:\t";
		getInput(newPoint,0);

		/* End of Input Segment*/

		/*Calculaion*/
		priority_queue<pair<double,int>,vector<pair<double,int>>,myComparator> pq;/*Try a different Data structure 
		to acheive a better Time Complecity*/

		int classCount=distinctClassCount(p,n);
		//cout<<"\n\n The number of distinct class:\t"<<classCount;

		for(int i=0;i<n;i++)
		{
			//cout<<"\n\n Distance betweem point "<<i+1<<":\t";
			calculateDist(newPoint,p+i,pq,i<k);
			//printpq(pq);
		}
		/*End of Calculation*/

		//printpq(pq);printing the priority queue
		/*count the class which occured max*/
		cout<<"\n\n The new point belongs to the class\t"<<findClass(pq,classCount);
	}
	return 0; 
}