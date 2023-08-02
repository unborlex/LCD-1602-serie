            //************* Hardware ******************
#define       s1602_dat    32
#define       s1602_sck    33


void          hardware_init();
void          s595_cargar(char cargar_dat);
void          enviar_d(char dato);
void          enviar_c(char dato);
void          init_LCD16x2();
void          enviar_cgram(char dato, char dir);
void          display_clear();
void          display_texto(char* dato, char columna, char linea);
void          display_write(char dato, char columna, char linea);
void          display_backon();
void          display_backoff();

char          back_estado = 0;     // 0 apagado, 1 encendido

void          display_backon()
{
                   back_estado = 1;

}
void          display_backoff()
{
                   back_estado = 0;


}
void         display_write(char dato, char columna, char linea)
{
                char write_memo = 0;
                if((linea == 0)&(columna<=16))
                {
                          write_memo = 0b10000000 + columna ;
                          enviar_c(write_memo);
                }
                if((linea == 1)&(columna <=16))
                {
                          write_memo = 0b11000000 + columna ;
                          enviar_c(write_memo);
                }
                enviar_d(dato);

}
void         display_texto(char* dato, char columna, char linea)
{
                     char indice = 0;
                     char columna_buff = 0;

                     while(dato[indice] != 0 )
                     {

                              columna_buff = columna + indice;
                              display_write(dato[indice], columna_buff, linea);
                              indice++;

                     }

}

void          display_clear()
{
                display_texto("                 ",0,0);
                display_texto("                 ",0,1);
}


void            enviar_cgram(char dato, char dir)
{
                char write_memo;

                write_memo = 0b01000000 + dir;
                enviar_c(write_memo);
                enviar_d(dato);
}
void                init_LCD16x2()
{
                    int  idx = 0;
                    //backlight = 1;
                    enviar_c(0x02);
                    delay(4);
                    enviar_c(0x28);
                    delay(4);
                    enviar_c(0x0C);
                    delay(4);
                    enviar_c(0x01);
                    delay(4);
                    enviar_c(0x80);
                    delay(10);

                    display_clear();

                     //cargar CGRAM
         /*
                    for(idx=0; idx<8; idx++)      //ch 0
                    {
                           enviar_cgram(flecha_d[idx], (idx));
                    }
                    for(idx=0; idx<8; idx++)      //ch 1
                    {
                           enviar_cgram(barra1[idx], (idx + 8));
                    }
                    for(idx=0; idx<8; idx++)      //ch 2
                    {
                           enviar_cgram(barra2[idx], (idx + 16));
                    }
                    for(idx=0; idx<8; idx++)      //ch 3
                    {
                           enviar_cgram(barra3[idx], (idx + 24));
                    }
                    for(idx=0; idx<8; idx++)      //ch4
                    {
                           enviar_cgram(barra4[idx], (idx + 32));
                    }
                    for(idx=0; idx<8; idx++)      //ch4
                    {
                           enviar_cgram(barra5[idx], (idx + 40));
                    }
*/

}


void           enviar_d(char dato)
{
               //nible alto
               char    env_dato = 0;
              
               env_dato  = dato & 0xF0;          //nible alto
          
               env_dato  = env_dato | 0x08;     //R/S=1  E=0  Back=0  xx=0
               s595_cargar(env_dato);
               env_dato  = env_dato | 0x04;      // E=1
               s595_cargar(env_dato);
               env_dato  = env_dato & 0xFB;      // R/S=1 E=0   Back=0  xx=0
               s595_cargar(env_dato);
               
               delayMicroseconds(10);


               //nible bajo

               env_dato  = dato << 4;

               env_dato  = env_dato & 0xF0;          //nible alto
               
               env_dato  = env_dato | 0x08;     //R/S=1  E=0  Back=0  xx=0
               s595_cargar(env_dato);
               env_dato  = env_dato | 0x04;      // E=1
               s595_cargar(env_dato);
               env_dato  = env_dato & 0xFB;      // R/S=1 E=0   Back=0  xx=0
               s595_cargar(env_dato);
               
               delayMicroseconds(10);

}

void           enviar_c(char dato)
{
               //nible alto
               char    env_dato = 0;

               env_dato  = dato & 0xF0;          //nible alto     R/S=0  E=0  Back=0  xx=0

               s595_cargar(env_dato);
               env_dato  = env_dato | 0x04;      // E=1
               s595_cargar(env_dato);
               env_dato  = env_dato & 0xFB;      // R/S=1 E=0   Back=0  xx=0
               s595_cargar(env_dato);
               
               delayMicroseconds(10);


               //nible bajo

               env_dato  = dato << 4;
               env_dato  = env_dato & 0xF0;          //nible alto      R/S=0  E=0  Back=0  xx=0

               s595_cargar(env_dato);
               env_dato  = env_dato | 0x04;      // E=1
               s595_cargar(env_dato);
               env_dato  = env_dato & 0xFB;      // R/S=1 E=0   Back=0  xx=0
               s595_cargar(env_dato);
               
               delayMicroseconds(10);

}



void          s595_cargar(char cargar_dat)
{

                          //  cargar_dat  0x  D7 D6 D5 D4 R/S E Back xx

                          //salida H             salida sin valor
                          digitalWrite(s1602_dat, LOW);
                          if((0b00000001 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);
                          
                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida G     D7
                          digitalWrite(s1602_dat, LOW);
                          if((0b10000000 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida F     D6
                          digitalWrite(s1602_dat, LOW);
                          if((0b01000000 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida E    D5
                          digitalWrite(s1602_dat, LOW);
                          if((0b00100000 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);
                          
                          //salida D    D4
                          digitalWrite(s1602_dat, LOW);
                          if((0b00010000 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida C   E
                          digitalWrite(s1602_dat, LOW);
                          if((0b00000100 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida B  R/S
                          digitalWrite(s1602_dat, LOW);
                          if((0b00001000 & cargar_dat) !=0 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                          digitalWrite(s1602_sck, LOW);
                          delayMicroseconds(5);

                          //salida A   Backligth
                          digitalWrite(s1602_dat, LOW);
                          //if((0b00000010 & cargar_dat) !=0 )
                          if(back_estado == 1 )
                                digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(20);

                          digitalWrite(s1602_sck, HIGH);
                          delayMicroseconds(1);
                      //    digitalWrite(s1602_sck, LOW);       //dejar clk en uno y genero el latch
                          delayMicroseconds(20);
                          
                          // fin de carga, genero el Latch
                          digitalWrite(s1602_dat, LOW);
                          delayMicroseconds(20);
                          digitalWrite(s1602_dat, HIGH);
                          delayMicroseconds(10);
                          digitalWrite(s1602_dat, LOW);
                          digitalWrite(s1602_sck, LOW);
                          
}

void          hardware_init()
{
                   pinMode(s1602_dat, OUTPUT);
                   pinMode(s1602_sck, OUTPUT);  
                   digitalWrite(s1602_dat, LOW);
                   digitalWrite(s1602_sck, LOW);

}
