//Thomas Ng

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main () {
    
    int guessercount=1, closestguesser=1;
    double sumguess=0,guess,closestguess=1,averageguess,averageincome=35324;
    
    cout << "\t\t\tHello and welcome to the program" << endl << endl
         << "Please enter your guess below, then let the next person" << endl ;
    cin >> guess;
    
    while (guess > 0) {          
          if (abs(guess - averageincome) < abs(closestguess - averageincome)){
           closestguess = guess;
           closestguesser = guessercount;
           cout << "Guesser #" << guessercount << " is the cloest guess" << endl;
           }
          sumguess += guess;
          guessercount++;
          cout << endl << "please enter the next guess: " << endl;
          cin >> guess;
          }
    guessercount--;
          
    cout << "Total guessers: " << guessercount << endl
         << "Average guess: " << sumguess / guessercount << endl
         << "Guesser number: " << closestguesser << endl << "With a guess of: "
         << closestguess << endl;
         
         return 0;
}    
