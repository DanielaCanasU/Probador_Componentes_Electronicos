#include <18f4550.h>
#device ADC = 10
#fuses intrc,nowdt
#use delay(clock=4Mhz)
#include <lcd.c>
#use fast_io(a)
float Lecturaad620;

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
      set_tris_a(0xff);// puerto a entrada
      set_tris_d(0x00);// puerto d salida
      lcd_init();
      setup_adc_ports(0x0e);
      setup_adc(adc_clock_internal);
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
                    printf(lcd_putc," 1>Dañao 3>return");
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
