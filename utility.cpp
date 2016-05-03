#include "utility.h"

string Utility:: toString(int number){
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

int Utility::dadoUno(){
    int num1;
    for(int c =1;c<=6;c++){
        num1 = 1 +rand()%(7-1);
    }
    return num1;
}

int Utility::dadoDos(){
    int num2;
    for(int h =1;h<=6;h++){
        num2 = 1 +rand()%(7-1);
    }
    return num2;
}

bool Utility::clickSprite(sf::Sprite s, sf::Vector2f mouse)
{
    sf::FloatRect bounds = s.getGlobalBounds();

    if(bounds.contains(mouse))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return true;
        }
    }
    return false;
}
