#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

int main(){
   string myString;
   cout << "WRITE SOMETHING" <<endl;
   getline(cin ,myString);
   int check;
   for (int i = 0; i < myString.size(); i++) {
      check = isdigit(myString[i]);
      if (check) {
         if (isdigit(myString[i-1])){
            cout << myString[i];
         }
         else {
            cout << "\n" << myString[i];
         }
      }     
      else {
         if(isdigit(myString[i-1])){
            cout << "\n" << myString[i];
         }
         else {
            cout << myString[i];
         }
      }
   }
}
