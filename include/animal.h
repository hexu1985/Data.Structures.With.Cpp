#ifndef ANIMAL_CLASSES
#define ANIMAL_CLASSES

class Animal
{
   private:
      char animalName[20];
   public:
      Animal(char nma[])
      {
         strcpy(animalName,nma);
      }
      
      virtual void Identify(void)
      {
         cout << "I am a " << animalName << " animal" << endl;
      }
};

class Cat: public Animal
{
   private:
      char catName[20];
   public:
      Cat(char nmc[], char nma[]): Animal(nma)
      {
         strcpy(catName,nmc);
      }
      
      virtual void Identify(void)
      {
         Animal::Identify();
         cout << "I am a " << catName << " cat" << endl;
      }
};


class Tiger: public Cat
{
   private:
      char tigerName[20];
   public:
      Tiger(char nmt[], char nmc[], char nma[]): Cat(nmc,nma)
      {
         strcpy(tigerName,nmt);
      }
      
      virtual void Identify(void)
      {
         Cat::Identify();
         cout << "I am a " << tigerName << " tiger" << endl;
      }
};

// Announce1 - pass an Animal object by value 
void Announce1(Animal a)
{
   // example of static binding; the compiler directs the 
   // execution of the Identify method of an Animal object
   cout << "In static Announce1, calling Identify:" << endl;
   a.Identify();
   cout << endl;
}

// Announce2 - pass a pointer to an Animal object 
void Announce2(Animal *pa)
{
   // dynamic binding is used. the Identify method of the
   // object pointed to by pa is called
   cout << "In dynamic Announce2, calling Identify:" << endl;
   pa->Identify();
   cout << endl;
}

#endif   // ANIMAL_CLASSES

