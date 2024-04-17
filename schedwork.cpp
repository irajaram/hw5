#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool maxExceed(Worker_T nurse, size_t maxShifts,std::map<Worker_T, int>& numShifts );
bool scheduleHelper(const AvailabilityMatrix& avail, 
                    const size_t dailyNeed,
                    const size_t maxShifts,
                    DailySchedule& sched,
                    int day,
                    std::map<Worker_T, int>& numShifts);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    sched.resize(avail.size());
    // Add your code below
    std::map<Worker_T, int> numShifts;
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, numShifts);


}

bool maxExceed(Worker_T nurse,size_t maxShifts, std::map<Worker_T, int>& numShifts){
   if(numShifts[nurse] >= maxShifts){
        return true;
    }
   else {
        return false;
   }
}

bool scheduleHelper(const AvailabilityMatrix& avail, 
                    const size_t dailyNeed,
                    const size_t maxShifts,
                    DailySchedule& sched,
                    int day,
                    std::map<Worker_T,int>& numShifts)
{
    //base case: you went through all the slots for the nurses available; explored every possible choice
    if(day == avail.size()){ 
        return true;
    }
    
    //iterate through all the workers avaialble for that specific day and then check if they exceeded the max, check if they available, and check if below daily need and then schedule one
    for(int i= 0; i<avail[day].size(); i++){
        if(avail[day][i] && !maxExceed(i,maxShifts,numShifts)){            
            sched[day].push_back(i); //scheduling worker for this day
            numShifts[i]++; //increasing number of shifts
            if(sched[day].size() == dailyNeed){
                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day +1, numShifts)){
                    return true;
                }
            }

            else{
                //other condition is if there are enough slots left so stay on same day just incremenet slot
                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, numShifts)){
                    return true;
                }
            }
            //Backtracking: undo action if schedule not found
            sched[day].pop_back();
            numShifts[i]--;
        }
        //if daily quota is met, move to next day
        
    }
    
    return false; //no solution found

 /*sched: {(1,vector(workers)),
           (2,vector(workers))...}*/
}
