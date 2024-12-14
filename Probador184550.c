#include <18f4550.h>
#device ADC = 10
#use i2c(Master,Fast=100000, sda=PIN_B0, scl=PIN_B1,force_sw)
#include <i2c_Flex_LCD.c>
#fuses intrc,nowdt
#use delay(clock=4Mhz)
//#include <lcd.c>
#use fast_io(a)
float Lecturaad620;
int32 valor_recarga = 59285;
//int32 valor_recarga = 0;
int direccionI2C = 0x4E;
int filas = 2;
int columnas = 16;
int pulsos_555 =  0;
int1 bandera_prueba_555;
int1 bandera_estado_555;
int32 value;

#INT_EXT2
void pulsos() {
   pulsos_555 = pulsos_555 + 1;
   CLEAR_INTERRUPT(INT_EXT2);
}

#INT_RTCC 
void tiempo_final_555() {
   DISABLE_INTERRUPTS(INT_EXT2);// Inhabilitar las interrupciones del timer0
   DISABLE_INTERRUPTS(INT_RTCC);
   bandera_prueba_555 = 0;
   if (pulsos_555 > 9) {
      bandera_estado_555 = 1;
   }
   
   else {
      bandera_estado_555 = 0;
   }
   
   CLEAR_INTERRUPT(INT_RTCC);
   printf(lcd_putc,"\f");
   lcd_gotoxy(5,1);
   printf(lcd_putc," UNEXPO");
   DISABLE_INTERRUPTS(INT_RTCC);
}

int Boton(){
         if(input(PIN_A3)) {
            return 1;
            } else if(input(PIN_A4)) {
            return 2;
            } else if(input(PIN_A5 )) {
            return 3;
            } else if (input(PIN_C0)){
            return 4;
            }
            return 0;
         }
void main(){
   while(true){ 
      setup_oscillator(OSC_4MHZ);
      set_tris_a(0xff);// puerto a entrada
      set_tris_d(0x00);// puerto d salida
      SETUP_COUNTERS(RTCC_INTERNAL,RTCC_DIV_256);
      ENABLE_INTERRUPTS(GLOBAL);// Habilita las interrupciones globales
      ext_int_edge(H_TO_L); //Inicia el flanco de la interruccion de alto abajo
      lcd_init(direccionI2C,filas,columnas);
      setup_adc_ports(0x0e);
      setup_adc(adc_clock_internal);
            /**
      printf(lcd_putc,"\f");
      lcd_gotoxy(5,1);
      printf(lcd_putc," UNEXPO");
      lcd_gotoxy(2,2);
      printf(lcd_putc," BARQUISIMETO");
      delay_ms(3000);
      printf(lcd_putc,"\f");
      lcd_gotoxy(0,1);
      printf(lcd_putc," Daniela Canas");
      lcd_gotoxy(0,2);
      printf(lcd_putc," [Developer]");
      delay_ms(1000);
      printf(lcd_putc,"\f");
      lcd_gotoxy(0,1);
      printf(lcd_putc," Gabriel Gimenez");
      lcd_gotoxy(0,2);
      printf(lcd_putc," [Developer]");
      delay_ms(1000);
      printf(lcd_putc,"\f");
      lcd_gotoxy(0,1);
      printf(lcd_putc," Carlos Guedez");
      lcd_gotoxy(0,2);
      printf(lcd_putc," [Developer]");
      delay_ms(1000);
      printf(lcd_putc,"\f");
      lcd_gotoxy(0,1);
      printf(lcd_putc," Carlos Zambrano");
      lcd_gotoxy(0,2);
      printf(lcd_putc," [Tutor]");
      delay_ms(1000);
      **/
      
MENUPRINCIPAL:
      while(true){
          printf(lcd_putc,"\f");
          lcd_gotoxy(0,1);
          printf(lcd_putc," MENU PRINCIPAL");
          lcd_gotoxy(0,2);
          printf(lcd_putc," 1>AD620 3>NEXT");
          delay_ms(3000);
          if(Boton()==1){
               while(1){
                set_adc_channel(0);
                delay_us(20);
                float valor_adc = read_adc();
                float lectura= valor_adc*0.004886; 
                float Lecturaad620=lectura;
                output_high(PIN_B0); // Colocar en alto pin B0 
                //output_high(PIN_B1);
                printf(lcd_putc,"\f"); //Limpiar la pantalla
                lcd_gotoxy(0,1);
                printf(lcd_putc," AD620 Testing..."); //  escribir eso
                lcd_gotoxy(0,2);
                //printf(lcd_putc,"\f");
                printf(lcd_putc," V:%0.2f. 2>Ret",Lecturaad620);
                delay_ms(1000);
                /**
                if(ad620Bueno==1){
                    lcd_gotoxy(0,2);
                    printf(lcd_putc," 1>Buenardo 3>return");
                    delay_ms(3000);
                    }
                else {
                    lcd_gotoxy(0,2);
                    printf(lcd_putc," 1>Da�ao 3>return");
                    delay_ms(3000);
                    }
                **/
                if(Boton()==2){
                        break;
                    }
                }     
             }
           if(Boton()==3){
               while(1){
                  printf(lcd_putc,"\f");
                  lcd_gotoxy(0,1);
                  printf(lcd_putc," 1>555 2>LM224");
                  lcd_gotoxy(0,2);
                  printf(lcd_putc," 4>741 3>Pag.Sig.");
                  if(Boton()==1){
                        bandera_prueba_555 = 1;
                        SET_TIMER0(valor_recarga);
                        value=get_timer0();
                        ENABLE_INTERRUPTS(INT_RTCC);
                        ENABLE_INTERRUPTS(INT_EXT2);// Habilita las interrupciones externas
                        printf(lcd_putc,"\f"); //Limpiar la pantalla
                        lcd_gotoxy(0,1);
                        printf(lcd_putc," 555 Testing..."); //  escribir eso
                        lcd_gotoxy(0,2);
                        printf(lcd_putc," 2>Volver");
                            
                        while(bandera_prueba_555 == 1) {
                           if (Boton() == 2) {
                              break;
                           }
                        }
                        
                        if (bandera_prueba_555 == 0) {
                           if (bandera_estado_555 == 0) {
                              printf(lcd_putc,"\f"); //Limpiar la pantalla
                              lcd_gotoxy(0,1);
                              printf(lcd_putc,"Malo %i", pulsos_555); //  escribir eso
                              lcd_gotoxy(0,2);
                              printf(lcd_putc," 2>Volver");
                              while(1) {
                                 if(Boton() == 2) {
                                    break;
                                 }
                              }
                           }
                           
                           if (bandera_estado_555 == 1) {
                              printf(lcd_putc,"\f"); //Limpiar la pantalla
                              lcd_gotoxy(0,1);
                              printf(lcd_putc,"Bueno %i", pulsos_555); //  escribir eso
                              lcd_gotoxy(0,2);
                              printf(lcd_putc," 2>Volver");
                              while(1) {
                                 if(Boton() == 2) {
                                    break;
                                 }
                              }
                           }
                        }
                        printf(lcd_putc,"\f"); //Limpiar la pantalla
                        lcd_gotoxy(0,2);
                        printf(lcd_putc," Regresando...");
                        delay_ms(1000);
                     }
                     
                 
                  
                  if(Boton()==2){
                        while(1){
                            output_high(PIN_B2); // Colocar en alto pin B0 
                            printf(lcd_putc,"\f"); //Limpiar la pantalla
                            lcd_gotoxy(0,1);
                            printf(lcd_putc," LM224 Testing..."); //  escribir eso
                            lcd_gotoxy(0,2);
                            printf(lcd_putc," 2>Volver");
                            delay_ms(1000);
                            if(Boton()==2){
                                output_low(PIN_B2); // Colocar en bajo pin B0
                                printf(lcd_putc,"\f"); //Limpiar la pantalla
                                lcd_gotoxy(0,2);
                                printf(lcd_putc," Regresando...");
                                delay_ms(1000);
                                break;
                            }
                        } 
                  }  
                  delay_ms(3000);
                  if(Boton()==4){
                        while(1){
                        output_high(PIN_B1); // Colocar en alto pin B0 
                        printf(lcd_putc,"\f"); //Limpiar la pantalla
                        lcd_gotoxy(0,1);
                        printf(lcd_putc," 741 Testing..."); //  escribir eso
                        lcd_gotoxy(0,2);
                        printf(lcd_putc," 2>Volver");
                        delay_ms(1000);
                            if(Boton()==2){
                                output_low(PIN_B1); // Colocar en bajo pin B0
                                printf(lcd_putc,"\f"); //Limpiar la pantalla
                                lcd_gotoxy(0,2);
                                printf(lcd_putc," Regresando...");
                                delay_ms(1000);
                                break;
                            }
                        }   
                    }
                  if(Boton()==3){
                        while(1){
                        printf(lcd_putc,"\f");
                        lcd_gotoxy(0,1);
                        printf(lcd_putc," 1>LM358 2>LM348");
                        lcd_gotoxy(0,2);
                        printf(lcd_putc," 4>LM324 3>RETURN");
                        delay_ms(3000);
                        if(Boton()==4){
                            while(1){
                            output_high(PIN_B2); // Colocar en alto pin B0 
                            printf(lcd_putc,"\f"); //Limpiar la pantalla
                            lcd_gotoxy(0,1);
                            printf(lcd_putc," LM324 Testing..."); //  escribir eso
                            lcd_gotoxy(0,2);
                            printf(lcd_putc," 2>Volver");
                            delay_ms(1000);
                                    if(Boton()==2){
                                        output_low(PIN_B2); // Colocar en bajo pin B0
                                        printf(lcd_putc,"\f"); //Limpiar la pantalla
                                        lcd_gotoxy(0,2);
                                        printf(lcd_putc," Regresando...");
                                        delay_ms(1000);
                                        break;
                                    }
                            }   
                        }
                        if(Boton()==3){
                            goto MENUPRINCIPAL;
                        }
                    }
                }           
            }
         }
      }           
   }
}
