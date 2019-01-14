
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_WORD_COUNT = 125; //in a document that contains 250 characters of letters and spaces, the max number of words that can appear is 125, assuming a word is defined as one or more letters separated by a space

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns); //finds valid patterns and puts them in the front of the array; delete the rest
bool containsOnlyLetters(char c[]); //checks if a C string contains only letters
void setToEmptyPattern(char a[][MAX_WORD_LENGTH+1], char b[][MAX_WORD_LENGTH+1], int arr[], int location); //sets a pattern at location to w1[location] = "", w2[location] = "", separation[location] = -1; using this to mark and get rid of invalid patterns from the array

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);
int countMatches(const char docArray[][MAX_WORD_LENGTH+2], int n, const char word[], int indices[]); //finds all the starting locations of word and stores them in indices, returns the size of indices

int main()
{
    
    //tests for makeProper
    const int MP_TEST_N = 5;
    
    char mPt1w1[][MAX_WORD_LENGTH+1] = {"cat", "dog", "Cat", "dOg", "animals"};
    char mPt1w2[][MAX_WORD_LENGTH+1] = {"cat", "cAt", "doG", "cat", "aNiMaLs"};
    int mPt1s[] = {5, 4, 4, 3, 0};
    assert(makeProper(mPt1w1, mPt1w2, mPt1s, MP_TEST_N) == 3);
    cerr << "test 1: " << endl;
    for (int i = 0; i < MP_TEST_N; i++)
        cerr<< mPt1w1[i] << '\t' << mPt1w2[i] << '\t' << mPt1s[i] << endl;
    
    char mPt2w1[][MAX_WORD_LENGTH+1] = {"c a t", "dog." , "cat", "", "67"};
    char mPt2w2[][MAX_WORD_LENGTH+1] = {"dog", "cat",    "dog", "dog", "cat"};
    int mPt2s[] = {5,      0,           -9,      6,        7};
    assert(makeProper(mPt2w1, mPt2w2, mPt2s, MP_TEST_N) == 0);
    cerr << endl << "test 2: " << endl;
    for (int i = 0; i < MP_TEST_N; i++)
        cerr << mPt2w1[i] << '\t' << mPt2w2[i] << '\t' << mPt2s[i] << endl;

    char mPt3w1[][MAX_WORD_LENGTH+1] = {"cat", "apple", "Math", "alPha", "a"};
    char mPt3w2[][MAX_WORD_LENGTH+1] = {"dog", "banana", "Science", "omeGa", "b"};
    int mPt3s[] = {5, 0, 100, 0, 1};
    assert(makeProper(mPt3w1, mPt3w2, mPt3s, MP_TEST_N) == 5);
    cerr << endl << "test 3: " << endl;
    for (int i = 0; i < MP_TEST_N; i++)
        cerr << mPt3w1[i] << '\t' << mPt3w2[i] << '\t' << mPt3s[i] << endl;
    
    assert(makeProper(mPt3w1, mPt3w2, mPt3s, 0) == 0);
    
    cerr << endl << "All makeProper test cases passed." << endl;
    
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    
    const char rtdoc[] = "    23423   computerscienceismyfavoritesubject 34 435     {{omega a a omega alpha bana6na      is better than apple!!!!   ";
    const char rtw1[][MAX_WORD_LENGTH+1] = {"computer", "omega", "alpha", "banana"};
    const char rtw2[][MAX_WORD_LENGTH+1] = {"science",  "omega", "omega", "apple"};
    const int rts[] = {0,              2,             0,             3};
    assert(rate(rtdoc, rtw1, rtw2, rts, TEST1_NRULES) == 3);
    
    cerr << "All rate tests succeeded" << endl;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns)
{
    if (nPatterns <= 0)
        return 0;
    
    //In this function, invalid patterns will be set-to-empty-pattern which means w1="", w2="", and separation=-1
    for (int row = 0; row < nPatterns; row++) //traverses each "row" of word1, word2, and separation to make all characters lower case then eliminate patterns that contain characters that are not letters and elminate patterns that have negative separation
    {
        //next 4 lines set all characters in a row to lower case
        for(int i = 0; word1[row][i] != '\0'; i++)
            word1[row][i] = tolower(word1[row][i]);
        for(int j = 0; word2[row][j] != '\0'; j++)
            word2[row][j] = tolower(word2[row][j]);
        
        //patterns that contain nonletters, have negative separations, or have a word that contains no characters are set-to-empty-pattern
        if(!containsOnlyLetters(word1[row]) || !containsOnlyLetters(word2[row]) || separation[row] < 0 || strcmp(word1[row], "") == 0 || strcmp(word1[row], "") == 0)
            setToEmptyPattern(word1, word2, separation, row);
    }
    
    //finds patterns that contain the same combination of words in any order and the pattern with the smaller separation is set-to-empty-pattern
    for (int row = 0; row < nPatterns; row++)
    {
        for(int i = row + 1; i < nPatterns; i++)
        {
            if ((strcmp(word1[row], word1[i]) == 0 && strcmp(word2[row], word2[i]) == 0) || (strcmp(word1[row], word2[i]) == 0 && strcmp(word2[row], word1[i]) == 0)) //checks 2 patterns contain the same combination of w1 and w2
            {
                //sets the pattern with the smaller separation to an "empty" pattern
                if (separation[i] <= separation[row])
                    setToEmptyPattern(word1, word2, separation, i);
                else
                    setToEmptyPattern(word1, word2, separation, row);
            }
        }
    }
    
    //sorts the arrays so that valid patterns are placed in the front of the array
    for (int row = 0; row < nPatterns; row++) //traverse all patterns
    {
        if (strcmp(word1[row], "") == 0 && strcmp(word1[row], "") == 0 && separation[row] == -1) //finds a pattern that contains an empty pattern
            for (int i = row + 1; i < nPatterns; i++) //traverse all patterns after the empty pattern
            {
                if(strcmp(word1[i], "") != 0) //swaps the empty pattern with the next valid pattern and breaks to ensure only one swap happens
                {
                    strcpy(word1[row], word1[i]);
                    strcpy(word2[row], word2[i]);
                    separation[row] = separation[i];
                    setToEmptyPattern(word1, word2, separation, i);
                    break;
                }
            }
    }
    
    for(int k = 0; k < nPatterns; k++) //finds the first empty pattern and returns its index, which is the number of valid patterns
    {
        if (strcmp(word1[k], "") == 0)
            return k;
    }
    return nPatterns; //returns the original number of patterns if none of them were invalid and set to the empty pattern
}

bool containsOnlyLetters(char c[]) //helper function
{
    for (int i = 0; c[i] != '\0'; i++)
    {
        if (!isalpha(c[i]))
            return false;
    }
    return true;
}

void setToEmptyPattern(char a[][MAX_WORD_LENGTH+1], char b[][MAX_WORD_LENGTH+1], int arr[], int location) //helper function
{
    strcpy(a[location], "");
    strcpy(b[location], "");
    arr[location] = -1;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns)
{
    if (nPatterns <= 0)
        return 0;
    
    char goodDoc[251]; //will contain all the necessary characters of document: all lower case letters and a single space between each word
    char goodDocArray[MAX_WORD_COUNT][MAX_WORD_LENGTH+2]; //an array of C-strings where each C-string is a single word from goodDoc;
    //MAX_WORD_LENGTH+2 is the second dimension so words in document that contain word1 or word2 as subsequences will not be equal
    
    int rating = 0; //counter for how many patterns match
    int docCounter  = 0; //docCounter is the counter for the document argument
    int goodDocCounter = 0; //goodDocCounter is the counter for the local array
    
    while (document[docCounter] != '\0') //takes only letters and a SINGLE space between each word and copies it into the local array goodDoc; also makes all characters lowercase
    {
        if(isalpha(document[docCounter]) || (document[docCounter] == ' ' && document[docCounter + 1] != ' ' && document[docCounter + 1] != '\0' && goodDocCounter != 0 && goodDoc[goodDocCounter - 1] != ' ')) //ensures that only letters get inputted into goodDoc and that the first and last characters of goodDoc are not spaces
        {
            goodDoc[goodDocCounter] = tolower(document[docCounter]);
            goodDocCounter++;
            docCounter++;
        }
        else docCounter++;
    }
    goodDoc[goodDocCounter] = '\0';

    int wordCount = 0; //counts how many words in goodDoc and how many C strings are in goodDocArray
    int wordLength = 0; //keeps track of how long each C string is in goodDocArray
    goodDocCounter = 0;
    for (goodDocCounter = 0; goodDoc[goodDocCounter] != '\0'; goodDocCounter++) //traverses through goodDoc and splits the string so that each word is placed into its own C string in goodDocArray
    {
        if (wordLength == MAX_WORD_LENGTH+1) //avoids going out of bounds of goodDocArray; when a word in goodDoc is too long, after the first 21 letters are inputted, set position 21 to null byte and then reset to move on to the next row and advance goodDocCounter to where the next word begins
        {
            goodDocArray[wordCount][wordLength] = '\0';
            wordCount++;
            wordLength = 0;
            while (goodDoc[goodDocCounter] != ' ') //advances goodDocCounter to the index of a space so that the next iteration of the loop reads a character
            {
                goodDocCounter++;
            }
            continue;
        }
        
        if(isalpha(goodDoc[goodDocCounter]))
        {
            goodDocArray[wordCount][wordLength] = goodDoc[goodDocCounter];
            wordLength++;
        }
        else //i.e. when a space is encountered, place a zero byte at the end of the current word and move onto the next row
        {
            goodDocArray[wordCount][wordLength] = '\0';
            wordCount++;
            wordLength = 0;
        }
    }
    goodDocArray[wordCount][wordLength] = '\0'; //the last word in goodDoc is not followed by a space, a zero byte must be placed at the end
    wordCount++; //wordCount is only incremented when there is a space, so increment once more for an accurate word count
    
    for(int i = 0; i < nPatterns; i++)
    {
        int wordIndices1[MAX_WORD_COUNT]; //will store all the locations in goodDocArray that match word1; there can only be as many matches as there are words
        int wordIndices2[MAX_WORD_COUNT]; //will store all the locations in goodDocArray that match word2; there can only be as many matches as there are words
        
        int wordIndices1size = countMatches(goodDocArray, wordCount, word1[i], wordIndices1);
        int wordIndices2size = countMatches(goodDocArray, wordCount, word2[i], wordIndices2);
        bool flag = false;
        
        for (int k = 0; k < wordIndices1size; k++) //counter for wordIndices1
        {
            for (int x = 0; x < wordIndices2size; x++) //counter for wordIndices2
            {
                if ( ((wordIndices2[x]-wordIndices1[k]) <= (separation[i] + 1)) && ((wordIndices2[x]-wordIndices1[k]) >= -(separation[i] + 1)) && ((wordIndices2[x]-wordIndices1[k]) != 0) ) //finds the distance between all combinations of the indices of word1 and word2 and checks if they are within "separation" and not the same index
                {
                    rating++;
                    flag = true;
                    break; //break after finding one match because each pattern can only be counted once
                }
            }
            if (flag)
                break; //break out of the this loop as well so the outermost loop can move on to the next pattern
        }
    }
    return rating;
}

int countMatches(const char docArray[][MAX_WORD_LENGTH+2], int n, const char word[], int indices[]) //helper function
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(docArray[i], word) == 0)
        {
            indices[k] = i;
            k++;
        }
    }
    return k;
}
