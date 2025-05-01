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
bool schedHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>&  shifts,
    size_t day,
    size_t curr
);


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
    // Add your code below
    size_t n = avail.size(); // number of days
    size_t k = avail[0].size(); // number of workers
    sched.resize(n);
    std::vector<size_t> shifts(k, 0); //stores how many shifts an employee has worked in n-day period
    return schedHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool schedHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>&  shifts,
    size_t day,
    size_t curr
){
    size_t n = avail.size(); // number of days
    size_t k = avail[0].size(); // number of workers
    if(day == n){ // if we've scheduled all days then we're done
        return true;
    }
 
    if(curr == dailyNeed){ // if the day already has enough workers we go on to the next
        return schedHelper(avail, dailyNeed, maxShifts, sched, shifts, day+1, 0);
    }

    for(size_t i = 0; i < k; i++){ //for all the workers on a given day
        if(avail[day][i] && shifts[i] < maxShifts && std::find(sched[day].begin(), sched[day].end(), i) == sched[day].end()){ //if they are avalible and haven't worked the max shifts for the week and have not already been scheduled fo rthat day
            sched[day].push_back(i); //we schedule them for the day
            shifts[i]++;// increase their number of shifts

            if(schedHelper(avail, dailyNeed, maxShifts, sched, shifts, day, curr+1)){// increase the count of workers for the day if it returns true that means we are done
                return true;
            }

            sched[day].pop_back(); //else we remove the day from to be scheduled 
            shifts[i]--;
        }
    }
    return false;
}

