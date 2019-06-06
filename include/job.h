#ifndef JOBREQUEST
#define JOBREQUEST

// employee priority level (Manager=0, etc)
enum Staff {Manager, Supervisor, Worker};

// record defining a job request
struct JobRequest
{
    Staff staffPerson;
    int jobid;
    int jobTime;
};

// overload "<" to compare two JobRequests
int operator< (const JobRequest& a, const JobRequest& b)
{
    return a.staffPerson < b.staffPerson;
}

// print a JobRequest record
void PrintJobInfo(JobRequest PR)
{
    switch (PR.staffPerson)
    {
        case Manager:       cout << "Manager        ";
                            break;
        case Supervisor:    cout << "Supervisor     ";
                            break;
        case Worker:        cout << "Worker         ";
                            break;
    }
    cout << PR.jobid << "        " << PR.jobTime << endl;
}

#include <iomanip.h>		// use manipulator setw

// print total job time allocated to each employee category
void PrintJobSummary(int jobServicesUse[])
{
    cout << "\nTotal Support Usage\n";
    cout << "   Manager     "   << setw(3)
    	 << jobServicesUse[0]   << endl;
    cout << "   Supervisor  "   << setw(3)
    	 << jobServicesUse[1]   << endl;
    cout << "   Worker      "   << setw(3)
    	 << jobServicesUse[2]   << endl;
}

#endif  // JOBREQUEST

