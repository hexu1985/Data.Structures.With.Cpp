// record structure used to store film and customer data
struct FilmData
{
   char filmName[32];
   char customerName[32];
};

// overload "==" operator by comparing film names
int operator == (const FilmData& A, const FilmData& B)
{
   return strcmp(A.filmName,B.filmName) == 0;
}

// FilmData is the data type for all SeqList objects
typedef   FilmData DataType;
