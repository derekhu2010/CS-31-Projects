#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value); //tack on the string value to every element in the array
int lookup(const string a[], int n, string target); //find position of target string
int positionOfMax(const string a[], int n); //return the position of string last in alpha order; all lower case comes after upper case
int rotateLeft(string a[], int n, int pos); //delete the item @ pos and shift every following item one space to the left and put the item originally @ pos at the end
int countRuns(const string a[], int n); //count the max number of times a string appears consecutively
int flip(string a[], int n); //reverses the order of the array
int differ(const string a1[], int n1, const string a2[], int n2); // finds the index where the first element differs
int subsequence(const string a1[], int n1, const string a2[], int n2); //if a1 contains a2, find the index where it starts
int lookupAny(const string a1[], int n1, const string a2[], int n2); //return the smallest position in a1 of an element that is equal to any of the n2 elements in a2.
int divide(string a[], int n, string divider); //returns location of the first string not less than divider, after the array has been rearranged
void printArray(string a[], int n, string functionName);

/*int main()
{
    string a1[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
    assert(appendToAll(a1, 5, "!!!") == 5);
    assert(appendToAll(a1, 4, "!!!") == 4);
    assert(appendToAll(a1, 0, "!!!") == 0);
    assert(appendToAll(a1, -10, "!!!") == -1);
    assert(appendToAll(a1, 5, "") == 5);
    
    const string b1[] = {"alpha", "beta", "beta", "delta", "epsilon"};
    assert(lookup(b1, 5, "epsilon") == 4);
    assert(lookup(b1, 4, "epsilon") == -1);
    assert(lookup(b1, 5, "zeta") == -1);
    assert(lookup(b1, 5, "") == -1);
    assert(lookup(b1, 5, "Epsilon") == -1);
    assert(lookup(b1, 0, "epsilon") == -1);
    assert(lookup(b1, 5, "beta") == 1);
    
    const string c1[] = {"apple", "banana", "orange", "mango"};
    const string c2[] = {"apple", "banana", "Orange", "Mango"};
    const string c3[] = {"apple", "orange", "orange", "mango"};
    assert(positionOfMax(c1, 4) == 2);
    assert(positionOfMax(c2, 4) == 1);
    assert(positionOfMax(c1, 0) == -1);
    assert(positionOfMax(c1, -5) == -1);
    assert(positionOfMax(c3, 4) == 1);
    
    string d1[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
    assert(rotateLeft(d1, 5, 1) == 1);
    assert(rotateLeft(d1, 0, 0) == -1);
    assert(rotateLeft(d1, -5, 1) == -1);

    const string e1[] = {"three", "three", "three", "two", "two", "four", "four", "four", "four", "one"};
    const string e2[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    assert(countRuns(e1, 10) == 4);
    assert(countRuns(e2, 10) == 1);
    assert(countRuns(e1, 0) == 0);
    assert(countRuns(e1, -5) == -1);
    
    string f1[] = {"one", "two", "three", "four"};
    string f2[] = {"one", "two", "three", "four", "five"};
    assert(flip(f1, 4) == 4);
    assert(flip(f2, 5) == 5);
    assert(flip(f1, 0) == 0);
    assert(flip(f1, -5) == -1);

    const string g1[] = {"one", "two", "three", "four"};
    const string g2[] = {"one", "two", "three", "four", "five"};
    const string g3[] = {"one", "two", "333", "four"};
    const string g4[] = {"one", "two", "333", "four"};
    assert(differ(g1, 4, g2, 5) == 4);
    assert(differ(g3, 4, g2, 5) == 2);
    assert(differ(g3, 4, g4, 4) == 4);
    assert(differ(g1, 0, g2, 5) == 0);
    assert(differ(g1, 0, g2, 0) == 0);
    assert(differ(g1, -5, g2, 5) == -1);
    assert(differ(g1, -5, g2, -5) == -1);
    
    const string h1[] = {"zero", "one", "two", "three", "one", "two", "three"};
    const string h2[] = {"one", "two", "three"};
    const string h3[] = {"four", "five", "six"};
    const string h4[] = {"zero", "one", "three", "two"};
    assert(subsequence(h1, 7, h2, 3) == 1);
    assert(subsequence(h1, 7, h3, 3) == -1);
    assert(subsequence(h1, 7, h2, 0) == 0);
    assert(subsequence(h2, 3, h1, 7) == -1);
    assert(subsequence(h1, 7, h4, 4) == -1);
    
    const string i1[] = {"apple" , "pear", "banana"};
    const string i2[] = {"alpha", "apple", "airplane", "pear"};
    const string i3[] = {"dogs", "cats", "mice"};
    assert(lookupAny(i1, 3, i2, 4) == 0);
    assert(lookupAny(i1, 3, i3, 3) == -1);
    assert(lookupAny(i1, 0, i2, 4) == -1);
    assert(lookupAny(i1, 3, i2, 0) == -1);
    assert(lookupAny(i1, 0, i2, 0) == -1);
    
    string j1[] = {"ape", "dog", "cat", "bat", "bat"};
    assert(divide(j1, 5, "bat") == 1);
    assert(divide(j1, 5, "bax") == 3);
    assert(divide(j1, 5, "elk") == 5);
    assert(divide(j1, 0, "bat") == -1);

    cerr << "All test cases are successful." << endl;
}*/

int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    
    for (int k = 0; k < n; k++)
        a[k] += value;
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    for (int k = 0; k < n; k++)
    {
        if (target == a[k])
            return k;
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1;
    
    int max = 0; //stores the position of the greatest string so far
    string maxString = a[0]; //stores the greatest string so far
    
    for (int k = 0; k < n; k++)
    {
        if(a[k] > maxString) //if the current string is greater than the maxString, set maxString to the the current string and set max to the current position
        {
            max = k;
            maxString = a[k];
        }
    }
    return max;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0 || pos < 0)
        return -1;
    
    string temp = a[pos]; //temporary stores the string at position pos
    for (int k = pos; k < n-1; k++) //for loop shifts elements over to the left
        a[k] = a[k+1];
    
    a[n-1] = temp; //puts the string originally at pos at the end
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    int counter = 1; //counts the current run, starts @ 1 and not 0 because a unique string still occurs 1 time in a row
    int maxRunCount = 1;
    
    for (int k = 1; k < n; k++)
    {
        if (a[k] == a[k-1])
        {
            counter++; //add 1 to counter if an element matches the one before it
            if (counter > maxRunCount) //if the current run count is greater than the max run count, replace it
                maxRunCount = counter;
        }
        else
            counter = 1; //reset counter when run is broken
    }
    return maxRunCount;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    
    string temp;
    for (int k = 0; k < n/2; k++) //traverses half of the array and "flips" the elements in the beginning to the appropriate place at the end
    {
        //swaps kth first term w kth last term (e.g. first and last term swap, 2nd and 2nd to last term swap, etc.)
        temp = a[k];
        a[k] = a[n-1-k];
        a[n-1-k] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <0 || n2 < 0)
        return -1;
    if (n1 == 0 || n2 == 0) //if both arrays are empty, then they both "run out" before a different term is found so the size is returned
        return 0;
    
    int max;
    //set the max to the size of the smaller array so we do not go out of bounds
    if (n1 < n2)
        max = n1;
    else
        max = n2;
    
    for (int k = 0; k < max; k++)
    {
        if(a1[k] != a2[k]) //if the kth element of a1 and a2 are not equal, return k as the position where the two arrays differ
            return k;
    }
    return max; //return the size of the smaller array if all elements match
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1) //if a2 is larger than a1, it is impossible for a1 to contain a2 as a subsequence
        return -1;
    if (n2 == 0)
        return 0;
    
    int startIndex = -1; //marks the position in a1 where a2 may begin
    
    for (int k = 0; k < (n1 - n2 + 1); k++) //k is the counter for a1; (n1-n2+1) guarantees that the the following portion of code will not check elements outside of the bounds of a1
    {
        if (a2[0] == a1[k]) //if the first term of a2 matches the kth term of a1, set startIndex to k and check if the following terms match
        {
            startIndex = k;
            for (int i = 0; i < n2; i++) //j is the counter for a2
            {
                if(a2[i] != a1[k+i])
                {
                    startIndex = -1; //if any following elements do not match, set the startIndex back to -1 b/c a1 does not contain a2 at this point
                    break;
                }
                if(i == n2-1)
                    return startIndex; //if the loop makes it to the last iteration, then a2 is a subsequence of a1; return k; this line of code prevents the program for searching for another subsequence after one has already been found in order to return the lowest position of a subsequence
            }
        }
    }
    return startIndex; //if a subsequence is not found, startIndex will be set to -1
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 <= 0)
        return -1;
    
    for (int k = 0; k < n1; k++) //k is the counter for a1
    {
        for (int i = 0; i < n2; i++) //i is the counter for a2
        {
            if (a1[k] == a2[i])
                return k; //k represents the position of the first element of a1 that is contained somewhere in a2
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if (n<= 0)
        return -1;
    
    //goal of this function is to order the array alphabetically, then find the first position not less than divider
    string minString;
    int minIndex;
    
    //selection sort
    for (int k = 0; k < n; k++) //traverses each element of the string
    {
        minString = a[k];
        minIndex = k;
        for (int i = k; i < n; i ++) //this loop finds and stores the value and position of the lowest string in the unsorted portion of the array
        {
            if(a[i] < minString)
            {
                minString = a[i];
                minIndex = i;
            }
        }
        a[minIndex] = a[k]; //swap the lowest string from the unsorted portion of the array w the element right after the sorted portion
        a[k] = minString;
    }
    
    for (int j = 0; j < n; j ++)
    {
        if (a[j] >= divider) //finds the location where an element is not less than divider
            return j;
    }
    return n;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool dividecheck(const string a[], int n, int p, string divider)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= divider)
            return false;
    for ( ; p < n  &&  a[p] == divider; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= divider)
            return false;
    string b[100];
    copy(a, a+n, b);
    sort(b, b+n);
    return equal(b, b+n, c);
}

void testone(int n)
{
    const int N = 6;
    
    // Act as if  a  were declared:
    //   string a[N] = {
    //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
    //   };
    // This is done in a way that will probably cause a crash if
    // a[-1] or a[N] is accessed:  We place garbage in those positions.
    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~string();
    a[N].string::~string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);
    
    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };
    
    string d[9] = {
        "alpha", "beta",  "beta", "beta", "alpha",
        "alpha", "delta", "beta", "beta"
    };
    
    switch (n)
    {
        case  1: {
            assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
        } break; case  2: {
            assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
        } break; case  3: {
            assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
                   a[1] == "beta");
        } break; case  4: {
            assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
                   a[1] == "betarho" && a[2] == "gammarho" &&
                   a[3] == "gammarho" && a[4] == "betarho" &&
                   a[5] == "deltarho");
        } break; case  5: {
            assert(lookup(z, -1, "alpha") == -1);
        } break; case  6: {
            assert(lookup(z, 0, "alpha") == -1);
        } break; case  7: {
            assert(lookup(a, 1, "alpha") == 0);
        } break; case  8: {
            assert(lookup(a, 6, "delta") == 5);
        } break; case  9: {
            assert(lookup(a, 6, "beta") == 1);
        } break; case 10: {
            assert(lookup(a, 6, "zeta") == -1);
        } break; case 11: {
            assert(positionOfMax(z, -1) == -1);
        } break; case 12: {
            assert(positionOfMax(z, 0) == -1);
        } break; case 13: {
            assert(positionOfMax(a, 1) == 0);
        } break; case 14: {
            assert(positionOfMax(a, 3) == 2);
        } break; case 15: {
            assert(positionOfMax(a, 6) == 2);
        } break; case 16: {
            assert(positionOfMax(a+3, 3) == 0);
        } break; case 17: {
            a[0] = "";
            a[1] = " ";
            a[2] = "";
            assert(positionOfMax(a, 3) == 1);
        } break; case 18: {
            assert(rotateLeft(z, -1, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 19: {
            assert(rotateLeft(a, 6, -1) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 20: {
            assert(rotateLeft(a, 6, 6) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 21: {
            assert(rotateLeft(z, 0, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 22: {
            assert(rotateLeft(a, 1, 0) == 0 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 23: {
            assert(rotateLeft(a, 6, 0) == 0 &&
                   a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
        } break; case 24: {
            assert(rotateLeft(a, 6, 5) == 5 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 25: {
            assert(rotateLeft(a, 6, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
        } break; case 26: {
            assert(rotateLeft(a, 5, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
        } break; case 27: {
            assert(countRuns(z, -1) == -1);
        } break; case 28: {
            assert(countRuns(z, 0) == 0);
        } break; case 29: {
            assert(countRuns(a, 1) == 1);
        } break; case 30: {
            assert(countRuns(a, 3) == 3);
        } break; case 31: {
            assert(countRuns(a, 4) == 3);
        } break; case 32: {
            assert(countRuns(a+2, 4) == 3);
        } break; case 33: {
            assert(countRuns(d, 9) == 5);
        } break; case 34: {
            assert(flip(z, -1) == -1 && a[0] == "alpha");
        } break; case 35: {
            assert(flip(z, 0) == 0 && a[0] == "alpha");
        } break; case 36: {
            assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                   a[1] == "beta");
        } break; case 37: {
            assert(flip(a, 2) == 2 && a[0] == "beta" &&
                   a[1] == "alpha" && a[2] == "gamma");
        } break; case 38: {
            assert(flip(a, 5) == 5 && a[0] == "beta" &&
                   a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
                   a[4] == "alpha" && a[5] == "delta");
        } break; case 39: {
            a[2] = "zeta";
            assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
                   a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
                   a[5] == "alpha");
        } break; case 40: {
            assert(differ(z, -1, b, 6) == -1);
        } break; case 41: {
            assert(differ(a, 6, z, -1) == -1);
        } break; case 42: {
            assert(differ(z, 0, b, 0) == 0);
        } break; case 43: {
            assert(differ(a, 3, b, 3) == 3);
        } break; case 44: {
            assert(differ(a, 3, b, 2) == 2);
        } break; case 45: {
            assert(differ(a, 2, b, 3) == 2);
        } break; case 46: {
            assert(differ(a, 6, b, 6) == 3);
        } break; case 47: {
            assert(subsequence(z, -1, b, 6) == -1);
        } break; case 48: {
            assert(subsequence(a, 6, z, -1) == -1);
        } break; case 49: {
            assert(subsequence(z, 0, b, 6) == -1);
        } break; case 50: {
            assert(subsequence(a, 6, z, 0) == 0);
        } break; case 51: {
            assert(subsequence(a, 6, b, 1) == 0);
        } break; case 52: {
            assert(subsequence(a, 6, b+4, 2) == 4);
        } break; case 53: {
            assert(subsequence(a, 6, b+3, 1) == 5);
        } break; case 54: {
            assert(subsequence(a, 6, b+3, 2) == -1);
        } break; case 55: {
            assert(subsequence(a, 6, b+2, 2) == -1);
        } break; case 56: {
            assert(subsequence(a, 6, a, 6) == 0);
        } break; case 57: {
            assert(lookupAny(a, 6, z, -1) == -1);
        } break; case 58: {
            assert(lookupAny(z, -1, b, 6) == -1);
        } break; case 59: {
            assert(lookupAny(z, 0, b, 1) == -1);
        } break; case 60: {
            assert(lookupAny(a, 6, z, 0) == -1);
        } break; case 61: {
            assert(lookupAny(a, 1, b, 1) == 0);
        } break; case 62: {
            assert(lookupAny(a, 6, b+3, 3) == 1);
        } break; case 63: {
            assert(lookupAny(a, 4, b+3, 3) == 1);
        } break; case 64: {
            assert(lookupAny(a, 2, b+2, 2) == -1);
        } break; case 65: {
            assert(divide(z, -1, "beta") == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 66: {
            assert(divide(z, 0, "beta") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 67: {
            assert(divide(a, 1, "aaa") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 68: {
            assert(divide(a, 1, "alpha") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 69: {
            assert(divide(a, 1, "zeta") == 1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 70: {
            assert(divide(a, 2, "aaa") == 0 &&
                   dividecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 71: {
            assert(divide(a, 2, "alpha") == 0 &&
                   dividecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 72: {
            assert(divide(a, 2, "beta") == 1 &&
                   dividecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 73: {
            assert(divide(a, 2, "zeta") == 2 &&
                   dividecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 74: {
            assert(divide(a, 6, "aaa") == 0 && dividecheck(a, 6, 0, "aaa"));
        } break; case 75: {
            assert(divide(a, 6, "alpha") == 0 &&
                   dividecheck(a, 6, 0, "alpha"));
        } break; case 76: {
            assert(divide(a, 6, "beta") == 1 &&
                   dividecheck(a, 6, 1, "beta"));
        } break; case 77: {
            assert(divide(a, 6, "delta") == 3 &&
                   dividecheck(a, 6, 3, "delta"));
        } break; case 78: {
            assert(divide(a, 6, "gamma") == 4 &&
                   dividecheck(a, 6, 4, "gamma"));
        } break; case 79: {
            assert(divide(a, 6, "zeta") == 6 &&
                   dividecheck(a, 6, 6, "zeta"));
        } break; case 80: {
            a[2] = "mu";
            c[5] = "mu";
            assert(divide(a, 6, "mu") == 5 && dividecheck(a, 6, 5, "mu"));
        } break; case 81: {
            assert(divide(a, 6, "chi") == 3 && dividecheck(a, 6, 3, "chi"));
        } break; case 82: {
            // To earn the bonus point for rotateLeft, this and all other
            // rotateLeft tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            for (int k = 0; k < BIG; k++)
                h[k] = (k % 2 == 0 ? "alpha" : "beta");
            h[BIG-2] = "gamma";
            h[BIG-1] = "delta";
            rotateLeft(h, BIG, 0);
            assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
        } break; case 83: {
            // To earn the bonus point for flip, this and all other
            // flip tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            for (int k = 0; k < BIG; k++)
                h[k] = (k % 2 == 0 ? "alpha" : "beta");
            h[0] = "gamma";
            h[BIG-1] = "delta";
            flip(h, BIG);
            assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
        } break; case 84: {
            // To earn the bonus point for divide, this and all other
            // divide tests must pass, and that function must not
            // use any additional arrays.
            const int BIG = 500;
            string h[BIG];
            string i[3] = { "alpha", "beta", "gamma" };
            for (int k = 0; k < BIG; k++)
                h[k] = i[k % 3];
            divide(h, BIG, "beta");
            int m = 0;
            for (m = 0; m < (BIG+2)/3; m++)
                assert(h[m] == "alpha");
            for ( ; m < (BIG+1)/3; m++)
                assert(h[m] == "beta");
            for ( ; m < BIG/3; m++)
                assert(h[m] == "gamma");
        } break;
    }
    
    new (&a[-1]) string;
    new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 84): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 84)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}
