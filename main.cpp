
#include "Arduino.h"
#include "application.h"

CApplication Application;

extern "C" int main(void)
{
  while(!Serial && millis() < 4000);
  Application.init();

  while (1)
  {
     Application.run();
  }
	
}

                       
