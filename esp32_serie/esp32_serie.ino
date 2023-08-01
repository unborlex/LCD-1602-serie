#include"LCD1602serie.h"

void setup() 
{
          
                   hardware_init();
                   init_LCD16x2(); 
          

}

void loop() 
{
        
                    display_texto("Hola mundo", 0, 0);
                    display_texto("Probando ", 0, 1);
                    delay(2000);
                    display_texto("Norber    ", 0, 0);
                    display_texto("27/7/2023", 0, 1);
                    delay(2000);




}
