#include "utility.h"

string toString(int number){
    if (number == 0)
          return "0";
      if(number < 0)
          return "-"+toString(-number);

    string temp="";
    string returnvalue="";
      while (number>0)
      {
          temp+=number%10+48;
          number/=10;
      }
      for (int i=0;i<(int)temp.length();i++)
          returnvalue+=temp[temp.length()-i-1];
      return returnvalue;
}

