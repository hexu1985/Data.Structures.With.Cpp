int FindPat(String S, String P, int startindex)
{
    // first and last character of pattern and pattern length
    char   patStartChar, patEndChar;
    int    patLength;
    
    // index last char of the pattern
    int    patInc;
    
    // start at searchIndex and look for match of 1st char of
    // pattern. match found at index matchStart. check for
    // match at index matchEnd with last char of pattern.
    int searchIndex, matchStart, matchEnd;
    
    // index of last char in S. matchEnd must be less than
    // or equal to this value
    int    lastStrIndex;
    
    // if a match occurs at ends, copy interior substring
    // to insidePattern
    String insidePattern;
    
    patStartChar = P[0];        // first char in the pattern
    patLength = P.Length();     // length of the pattern
    patInc = patLength-1;       // index last char of pattern
    patEndChar = P[patInc];     // last char of the pattern
    
    // if pattern length > 2, get all but the first and last
    // characters of the pattern
    if (patLength > 2)
        insidePattern = P.Substr(1,patLength-2);
    
    lastStrIndex = S.Length()-1; // index last char in S
    // start search from here to match first chars
    searchIndex = startindex;
    
    // look for match with 1st char of the pattern
    matchStart = S.Find(patStartChar,searchIndex);
    // index of last char of possible match
    matchEnd = matchStart + patInc;

    // repeatedly look for match at 1st char and test
    //  that last char not past the end of the string.
    while(matchStart != -1 && matchEnd <= lastStrIndex)
    {
        // do 1st and last chars match?
        if (S[matchEnd]==patEndChar)
        {
            // if pattern one or two chars, have a match
            if (patLength <= 2)
                return matchStart;
                
            // compare all but 1st and last characters
            if (S.Substr(matchStart+1,patLength-2) ==
                    insidePattern)
                return matchStart;
        }

        // pattern not found. contine search at next char
        searchIndex = matchStart+1;
        matchStart = S.Find(patStartChar,searchIndex);
        matchEnd = matchStart+patInc;
    }
    return -1;  // did not find a match
}
