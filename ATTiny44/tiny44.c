

#include      "LCD1602serie.h"



void main()
{
           delay_ms(500);
           hardware_init();
           init_LCD16x2();
           display_backon();
           while(1)
           {
                    display_texto("Hola mundo", 0, 0);
                    display_texto("Probando ", 0, 1);
                    delay_ms(2000);
                    display_texto("12345     ", 0, 0);
                    display_texto("27/7/2023", 0, 1);
                    delay_ms(2000);

           }
}