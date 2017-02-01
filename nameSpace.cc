#include <iostream>

//using namespace std;

namespace first
{
  int x = 5;
}

namespace second
{
   double x = 3.1416;
}


int main()
{
  char p;
  // int x;  // this will override any namespace

  std::cin >> p;
  if(p == 'a')
  {
    using namespace first; // this will be valid only within this block
    std::cout << "a" << std::endl;
    std::cout << "Pi = " << x << std::endl;
  }
  else
  {
    using namespace second;
    std::cout << "!a" << std::endl;
    std::cout << "Pi = " << x << std::endl;
  }
  //std::cout << "Pi = " << x << std::endl; // this will never get x of any namespace
/*
  if(p == 'a')
  {
    cout << "Pi = " << first::x << endl;
  }
  else
  {
    cout << "Pi = " << second::x << endl;
  }
*/
}
