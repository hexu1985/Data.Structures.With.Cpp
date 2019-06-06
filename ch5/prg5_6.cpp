#include <iostream.h>
#include <fstream.h>
#pragma hdrstop

#include "job.h"

// priority queue elements are of type JobRequest
typedef  JobRequest DataType;

#include "apqueue.h"            // include the PQueue class

void main()
{
    // handle up to 25 job requests
    PQueue jobPool;
    
    // job requests are read from fin
    ifstream fin;
    
    // time spent working for each category of employee
    int jobServicesUse[3] = {0, 0, 0};
    
    JobRequest PR;
    char ch;

    // open "job.dat" for input. exit program if open fails
    fin.open("job.dat", ios::in | ios::nocreate);
    if (!fin)
    {
        cerr << "Cannot open file 'job.dat'" << endl;
        exit(1);
    }

    // read file. insert each job into priority queue jobPool.
    // each line starts with a character that identifies the
    // type of staff person
    while (fin >> ch)
    {
        // assign staffPerson field
        switch(ch)
        {
            case 'M':   PR.staffPerson = Manager;
                        break;
            case 'S':   PR.staffPerson = Supervisor;
                        break;
            case 'W':   PR.staffPerson = Worker;
                        break;
            default:    break;
        }
        
        // read the integer jobid and jobTime fields of PR
        fin >> PR.jobid;        
        fin >> PR.jobTime;
        
        // insert PR into the priority queue
        jobPool.PQInsert(PR);
    }
        
    // delete jobs from priority queue and print information
    cout << "Category     Job ID     Job Time\n\n";
    while (!jobPool.PQEmpty())
    {
        PR = jobPool.PQDelete();
        PrintJobInfo(PR);
        // accumulate job time for each category of employee
        jobServicesUse[int(PR.staffPerson)] += PR.jobTime;
    }
    
    PrintJobSummary(jobServicesUse);
}

/*
<Input file "job.dat">

M 300 20
W 301 30
M 302 40
S 303 10
S 304 40
M 305 70
W 306 20
W 307 20
M 308 60
S 309 30

<Run of Program 5.6>

Category     Job ID     Job Time

Manager        300        20
Manager        302        40
Manager        308        60
Manager        305        70
Supervisor     309        30
Supervisor     303        10
Supervisor     304        40
Worker         306        20
Worker         307        20
Worker         301        30

Total Job Usage
   Manager     190
   Supervisor   80
   Worker       70
*/
