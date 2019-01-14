
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool hasProperSyntax(string pollData);
int tallySeats (string pollData, char party, int& seatTally);

int main()
{
    string pollDataString;
    char partyCode;
    int numSeats;
    while (true) //use a while true loop to continuously check different test cases
    {
        numSeats = -999;
        cout << "enter a poll data string: ";
        getline (cin, pollDataString);
        if (pollDataString == "exit")
            break;
        
        cout << "enter a party code: ";
        cin >> partyCode;
        cin.ignore(10000, '\n');
        
        if (hasProperSyntax(pollDataString))
            cout << "Has Proper Syntax" << endl;
        else
            cout << "Does not have Proper Syntax" << endl;
        
        cout << "return value of int tallySeats: " << tallySeats(pollDataString, partyCode , numSeats) << endl;
        cout << "value of numSeats: " << numSeats << endl << endl;
    }
}

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool hasProperSyntax(string pollData)
{
    string stateCode = "";
    string stateForecast;
    int startIndex=0; //will represent the starting index of each state forecast in the pollData string
    int commaIndex; //will represent the indices of the commas, which marks the separates the state forecasts
    
    pollData += ',';
    
    for (int i=0; i != pollData.size(); i++)
    {
        if (pollData[i] == ',')
        {
            commaIndex = i;
            stateForecast = pollData.substr(startIndex, commaIndex-startIndex); //creates a substring from the pollData string that contains a single state forecast
            
            //next portion checks that the the first two letters of the state forecast are a valid state code
            stateCode += toupper(stateForecast[0]);
            stateCode += toupper(stateForecast[1]);
            if (!isValidUppercaseStateCode(stateCode))
            {
                //cerr << "Error 1 "; debugging line
                return false;
            }
            
            //while loop checks that after the state code, the state forecast consists only of valid party results (either digit-digit-partycode or digit-partycode)
            int j = 2;
            while (j < stateForecast.size())
            {
                if (isdigit(stateForecast[j]) && isdigit(stateForecast[j+1]) && isalpha(stateForecast[j+2])) //checks if the next party result is in the format digit-digit-partycode
                {
                    j+=3; //advances to where the next party code is expected to start
                    continue;
                }
                else if (isdigit(stateForecast[j]) && isalpha(stateForecast[j+1])) //if the party result is not in digit-digit-partycode, then it must be in the format digit-partycode
                {
                    j+=2; //advances to where the next party code is expected to start
                    continue;
                }
                else //any other format is invalid, return false
                {
                    //cerr << "Error 2 "; debugging line
                    return false;
                }
            }
            
            startIndex = commaIndex + 1; //sets the startIndex to the first character of the next state forecast
            stateCode = "";
        }
    }
    return true;
}

int tallySeats (string pollData, char party, int& seatTally)
{
    //next 4 lines reads invalid inputs and returns appropriate values
    if (!hasProperSyntax(pollData))
        return 1;
    if (!isalpha(party))
        return 2;
    
    int counter = 0; //stores number of seats for the party
    for (int i = 2; i < pollData.size(); i++)
    {
        if (toupper(pollData[i]) == toupper(party))
        {
            //converts the one or two digits characters before the party code to an int value and adds it to the counter
            if (isdigit(pollData[i-1])) //still need to check if character before the party code character is a digit because a party code character may be in a state code
            {
                counter += (pollData[i-1] - '0');
                if (isdigit(pollData[i-2])) //nested in previous if statement because we only want to check for a digit 2 indices before a party code if there is a digit 1 index before a party code
                    counter += (pollData[i-2] - '0') * 10;
            }
        }
    }
    seatTally = counter;
    return 0;
}
