#include "strclass.h"

// base class for house painting hierarchy
class House
{
   private:
      String id;        // id for House
   public:
      // constructor. initialize id to "House"
      House(void)
      {
         id = "House";
      }
      
      // virtual method.   prints the string "House"
      virtual void Paint(void)
      {
         cout << id;
      }
};

class WoodFrameHouse: public House
{
   private:
      // id for WoodFrameHouse
      String id;
   public:
      // constructor. assign id = "Wood Frame"
      WoodFrameHouse(void): House()
      {
         id = "Wood Frame";
      }
      
      // virtual method. print id and call Paint in base class
      virtual void Paint(void)
      {
         cout << "Painting a " << id << " ";
         House::Paint();
      }
};

class StuccoHouse: public House
{
   private:
      // id for StuccoHouse
      String id;
   public:
      // constructor. assign id = "Stucco"
      StuccoHouse(void): House()
      {
         id = "Stucco";
      }
      
      // virtual method. print id and call Paint in base class
      virtual void Paint(void)
      {
         cout << "Painting a " << id << " ";
         House::Paint();
      }
};

class VinylSidedHouse: public House
{
   private:
      // id for VinylSidedHouse
      String id;
   public:
      // constructor. assign id = "Vinyl Sided"
      VinylSidedHouse(void): House()
      {
         id = "Vinyl Sided";
      }
      
      // virtual method. print id and call Paint in base class
      virtual void Paint(void)
      {
         cout << "Painting a " << id << " ";
         House::Paint();
      }
};
