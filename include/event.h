#ifndef EVENT_CLASS
#define EVENT_CLASS

enum EventType {arrival, departure};

class Event                                         
{
    private:
        int time;
        EventType etype;
        int customerID;
        int tellerID;
        int waittime;
        int servicetime;
    public:
        Event(void);
        Event(int t, EventType et, int cn, int tn, int wt, int st);
        int GetTime(void);
        EventType GetEventType(void);
        int GetCustomerID(void);
        int GetTellerID(void);
        int GetWaitTime(void);
        int GetServiceTime(void);
};

Event::Event(void)  // default constructor - data filled by assignment later
{}

Event::Event(int t, EventType et, int cn, int tn, int wt, int st): 
                time(t), etype(et), customerID(cn), tellerID(tn),
                waittime (wt), servicetime(st) 
{}
    
int Event::GetTime(void)
{
    return time;
}
    
EventType Event::GetEventType(void)
{
    return etype;
}
    
int Event::GetCustomerID(void)
{
    return customerID;
}
    
int Event::GetTellerID(void)
{
    return tellerID;
}
    
int Event::GetWaitTime(void)
{
    return waittime;
}

int Event::GetServiceTime(void)
{
    return servicetime;
}

// compare two Event objects using the time at 
// which the events occur. needed for the
// priority queue

int operator< (Event e1, Event e2)
{
    return e1.GetTime() < e2.GetTime();
}


#endif  // EVENT_CLASS