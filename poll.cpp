//
//  main.cpp
//  Poll
//
//  Created by Simon Fahmy on 10/24/22.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cassert>
#include <string.h>
using namespace std;

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode) // given StateCode
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

// first required function, determines if it is a valid poll string
bool isValidPollString(string pollData) { //since an empty string is valid, this checks for that
    if (pollData == "") {
        return true;
    }
    
    for (int k = 0; k < pollData.size(); k++) { // makes all of the characters uppercase
        pollData.at(k) = toupper(pollData.at(k));
    }

    //repeating after a comma
    string word = "";
    for (int i=0; i < pollData.size(); i++) {
        if (pollData.at(i) == (' ')) { //determine if there are any spaces in the string
            return false;
        }
        
        //this function creates a new string that appends all of the letters which precede a comma
        if (pollData.at(i) == ',' || i == pollData.size() - 1) { //state forecast always end with either a comma or the last letter
            if (i == pollData.size() - 1) {
                word = word + pollData.at(i);
            }
            // determine if first two letters are state codes
            if (!isValidUppercaseStateCode(word.substr(0, 2))) {
                return false; //checks if its a valid state code
            }

            if (word.size() == 2) {
                continue; // validates state forecasts that are just state codes
            }
            
            if (!isalpha(word.at(word.size()-1))) { //last character can only be a letter
                return false;
            }
            
            //check for digits after the state code, since the only char after a state code can be a comma or digit
            for (int p = 2; p < word.size(); p++) {
                while (isdigit(word.at(p))) {
                    p++;
                }
                if (!isalpha(word.at(p)) && !isdigit(word.at(p)) && word.at(p)!= ',') { //characters can onle be a digit, letter, or a comma
                    return false;
                }
            }
            word = ""; //refreshes the string "word" since there is a comma, and then repeats the loop for a new state forecast
        }
        else {
            word = word + pollData.at(i); //appends all the characters that aren't digits or letters to "word" so they can be tested
        }
    }
    return true;
}

    
int countSeats(string pollData, char party, int& seatCount) {
    party = toupper(party);
    
    for (int k = 0; k < pollData.size(); k++) { // makes all of the characters uppercase
        pollData.at(k) = toupper(pollData.at(k));
    }
        
    if (!isValidPollString(pollData)) {
        return 1;
    }
    else if (!isalpha(party)) {
        return 2;
    }
//int& seatcount
    string votes = "";
    seatCount = 0;
    for (int x = 0; x < pollData.size(); x++) {
        if (isdigit(pollData.at(x))) {
            votes = votes + pollData.at(x); //appends all the integers into a string, until they hit the given letter
        }
        else if (pollData.at(x) == party) {
            seatCount = seatCount + stoi(votes); //makes the string called "votes" an integer, so it can add the votes together from diff forecasts
            votes = "";
            continue; //might cut the whole thing
        }
        else {
            votes = ""; //refreshes the string "votes" if the character is not a digit before 'party' or 'party' itself, since the only desired characters in "votes" should be numbers
        }
    }
    return 0;
}
    
    
int main() //tests
{
    cout << "type: ";
    int seats = 0;
    string dad;
    getline(cin, dad);
    if (isValidPollString(dad))
        cout << "passed test 1\n";
    else
        cout << "failed test 1\n";
    if (countSeats(dad, 'd', seats) == 0)
        cout << seats;
    else
        cout << "failed test 2\n";
    return 0;
}


//ca5555t3d,az555t9y0p
