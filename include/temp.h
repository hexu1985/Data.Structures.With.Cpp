#ifndef TEMPERATURE_CLASS
#define TEMPERATURE_CLASS

class Temperature
{
    private:
        // data holding current high and low readings for the day   
        float highTemp, lowTemp;
    public:
        // constructor. no default parameters
        Temperature (float h, float l);
        
        // methods to retrieve and modify private data
        void UpdateTemp (float temp);                   
        float GetHighTemp (void) const;             
        float GetLowTemp (void) const;          
};

// constructor. asssign user data h to highTemp and l to lowTemp. 
Temperature::Temperature(float h, float l) : highTemp(h), lowTemp(l)
{}
    
// update current temperature readings if temp produces new high or low
void Temperature::UpdateTemp (float temp)
{
    if (temp > highTemp)
        highTemp = temp;
    else if (temp < lowTemp)
        lowTemp = temp;
}

// return the high
float Temperature::GetHighTemp(void) const
{
    return highTemp;
}

// return the low
float Temperature::GetLowTemp(void) const
{
        return lowTemp;
}

#endif  // TEMPEATURE_CLASS
