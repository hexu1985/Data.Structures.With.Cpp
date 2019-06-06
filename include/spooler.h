#include <iostream.h>

// include the random number generator and LinkedList class 
#include "random.h"        // simulate print times
#include "link.h"          

// printer speed is 8 pages per minute
const int PRINTSPEED = 8;  // pages per minute

// record containing information for each print job
struct PrintJob
{
    int  number;
    char filename[20];
    int  pagesize;
};

// the print spooler class
class Spooler
{
    private:
        // queue that holds print jobs and status
        LinkedList<PrintJob> jobList;
  
        // deltaTime holds a random value in the range 1 - 5 
        // minutes to simulate elapsed time
        // Job info is updated by the UpdateSpooler method
        int deltaTime;

        void UpdateSpooler(int time);
        
        RandomNumber rnd;
        
    public:
        // constructor
        Spooler(void);
        
        // add job to the spooler   
        void AddJob(const PrintJob& J);
        
        // spooler evaluation methods 
        void ListJobs(void);
        int CheckJob(int jobno);
        int NumberOfJobs(void);
};

// construct; initialize deltaTime to 0
Spooler::Spooler(void): deltaTime(0)
{}

// spooler update. assumes time elapses during which pages
// are printed.  method deletes completed jobs and updates 
// the remaining pages for the current running job
void Spooler::UpdateSpooler(int time)
{ 
    PrintJob J;
    
    // number of pages that could print in the given time
    int printedpages = time*PRINTSPEED;

    // use value printedpages and scan list of jobs in queue.
    // update the print queue
    jobList.Reset();
    while (!jobList.ListEmpty() && printedpages > 0)   
    {
        // look at first job
        J = jobList.Data();

        // if pages printed greater than pages for job,  
        // update printed pages count and delete job      
        if (printedpages >= J.pagesize)
        {
            printedpages -= J.pagesize;
            jobList.DeleteFront();
        }
        // part of job complete; update remaining pages       
        else
        {
            J.pagesize -= printedpages;
            printedpages = 0;
            jobList.Data() = J;       // update info in node
        }
    }
}

// update spooler and add the new job; compute the random time
// before the next spooler update event. 
void Spooler::AddJob(const PrintJob& J)
{
    UpdateSpooler(deltaTime);
    deltaTime = 1 + rnd.Random(5);   // range 1 - 5 minutes
    jobList.InsertRear(J);           // add the new job
}

// update spooler and list all jobs currently in the spooler
void Spooler::ListJobs(void)
{
    PrintJob J;

    // update the print queue
    UpdateSpooler(deltaTime);
    
    // generate the time until the next event
    deltaTime = 1 + rnd.Random(5);

    // check for empty spooler before scanning of the list
    if (jobList.ListSize() == 0)
        cout << "Print queue is empty\n";
    else
    {
        // reset to the beginning of list and use a
        // loop to scan the list of jobs. stop on end of list.
        // print information fields for each job
        for(jobList.Reset(); !jobList.EndOfList(); 
                                            jobList.Next())
        {
            J = jobList.Data();
            cout << "Job " << J.number << ": " << J.filename;
            cout << "  " << J.pagesize << " pages remaining"
                 << endl;
        }
    }
}

// update spooler; scan list for job with the designated job
// number; if found, return number of pages remaining to print
int Spooler::CheckJob(int jobno)
{
    PrintJob J;

    UpdateSpooler(deltaTime);
    
    deltaTime = 1 + rnd.Random(5);

    // use a sequential scan of the list with jobno as the key
    for(jobList.Reset();!jobList.EndOfList();jobList.Next())
    {
        J = jobList.Data();
        if (J.number == jobno)
            break;
    }
    
    // if match found. return number of remaining pages or  0 
    if (!jobList.EndOfList())
        return J.pagesize;
    else
        return 0;
}


// retrieve the number of jobs currently in the spooler
int Spooler::NumberOfJobs(void)
{
    return jobList.ListSize();
}
