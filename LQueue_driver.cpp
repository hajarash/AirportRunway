/*---------------------------------------------------------------------
                  Airport Runway Simulator to go with the LQueue
  ----------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdio.h>

using namespace std;

#include "LQueue.h"


Queue takeoff;
Queue landing;
int totalLandingTime = 0;
int totalTakingoffTime = 0;


void landingRequest(Queue &q, int k)
{
	QueueElement flighNumber = k;
	//enqueue plane landing queue
	q.enqueue(flighNumber);
}


void takeoffRequest(Queue &q, int k)
{
	QueueElement flighNumber = k;
	//enqueue plane takeoff queue
	q.enqueue(flighNumber);
}

void calculateStatistics(int mLandingQueueSize,int mTakingoffQueueSize, double ttlLandingTime,double ttlTakingoffTime, int ttlSimulationTime)
{
	cout << "STATISTICS"<<endl;
	cout << "Maximum number of planes in landing queue was : "<<mLandingQueueSize<<endl;
	cout << "Average minutes spent waiting to land : " << double(ttlLandingTime/ttlSimulationTime)<<endl;
	cout << "Maximum number of planes in takeoff queue was : "<<mTakingoffQueueSize<<endl;
	cout << "Average minutes spent waiting to takeoff : " << double(ttlTakingoffTime/ttlSimulationTime)<< endl;
}
void print(Queue q)
{ q.display(cout); }



int main(void)
{
	int landTimeInterval;
	int takeTimeInterval;
	int landingRate, takeOffRate ,clockInterval,minuteInterval, maxLandingSize, maxTakingoffSize,landingTime,takeOffTime, totalSimulationTime;
	clockInterval = 100;//millisecond
	minuteInterval = 60;
	maxLandingSize = 0;
	maxTakingoffSize = 0;
	bool land = false;
	bool take = false;
	landingTime = 0;
	takeOffTime = 0;
    srand (time(NULL));
	


	cout << "Time for a plane to land (in minutes): ";
	cin >> landTimeInterval;
	cout << "Time for a plane to takeOff (in minutes): ";
	cin >> takeTimeInterval;
	cout << "Landing rate (planes per hour): ";
	cin >> landingRate;
	cout << "Takeoff rate (planes per hour):";
	cin >> takeOffRate;
	cout << "How long to run the simulation (in minutes): ";
	cin >> totalSimulationTime;
    
    int notFreeUntil = 0;
    int k=1000;
	for (int i = 1; i <= totalSimulationTime; i++){
    
        int one = (rand() % 60)+1;
        int two = (rand() % 60)+1;
        land = one %60 < landingRate;
        take = two %60 < takeOffRate;
        if(land){
            
            landingRequest(landing,k);
            printf ("Time= %d\n", i);
            printf ("Plane %d wants to land; added to landing queue; %d in queue\n", k,landing.getSize());
            k++;
        }
        if(take){
            int myK=k+totalSimulationTime;
            takeoffRequest(takeoff,k+totalSimulationTime);
            printf ("Time= %d\n", i);
            printf ("Plane %d wants to take off; added to takeoff queue; %d in queue\n", myK,takeoff.getSize());

        
        }
        
        if(i >notFreeUntil){
            
            if (!landing.empty()){
                notFreeUntil = i+ landTimeInterval;
                totalLandingTime+= (landing.getSize()-1);
                landing.dequeue();
                
            }else{
                if(!takeoff.empty()){
                    notFreeUntil = i+ takeTimeInterval;
                    totalTakingoffTime+= (takeoff.getSize()-1);
                    takeoff.dequeue();
                }
            }
        }else{
            totalLandingTime+= (landing.getSize());
            totalTakingoffTime+= (takeoff.getSize());
        }
        if (landing.getSize() > maxLandingSize){
            maxLandingSize = landing.getSize();
        }
        if (takeoff.getSize()>maxTakingoffSize){
            maxTakingoffSize = takeoff.getSize();
        }
    
    }
	
    calculateStatistics(maxLandingSize, maxTakingoffSize,double(totalLandingTime),double(totalTakingoffTime),totalSimulationTime);
   system("PAUSE");
   return 0;
}
