#include <LiquidCrystal.h> //Importamos la librería que trae la clase para el LCD "LiquidCrystal" con sus métodos nos será mucho más fácil operar con la pantalla. 

//Datasheet 74HC595 : https://www.hwlibre.com/wp-content/uploads/2019/06/registro-74hc595.jpg
//Display 7 Segmentos: http://www.circuitstoday.com/wp-content/uploads/2016/03/7_segment_display_pin_outs.png

const int latchPin = 8;     // Pin 12 74HC595(Latch)-OUTPUT
const int dataPin  = 9;     // Pin 14 74HC595(Data)-OUTPUT
const int clockPin = 10;    // Pin 11 74HC595(Clock)-OUTPUT

const int botonENTER = 1;   // Pin para la entrada del botón "ENTER"-INPUT
const int botonUP = 2;      // Pin para la entrada del botón "UP"-INPUT
const int botonDWN = 3;     // Pin para la entrada del botón "DOWN"-INPUT
const int rs = 11;          // Pin para RS en la pantalla LCD (RW lo conectaremos a tierra)
const int en = 12;          // Pin para E(enable) en la pantalla LCD
const int d4 = 4;           // Pin para D4 en la pantalla LCD
const int d5 = 5;           // Pin para D5 en la pantalla LCD
const int d6 = 6;           // Pin para D6 en la pantalla LCD
const int d7 = 7;           // Pin para D7 en la pantalla LCD
const byte numeros[10] = {  //Vector de bytes con números [0-9] (con ésto conseguimos 8 salidas para los 8 segmentos(contanto el punto del display) usando solo un byte)
                0b11111100, //0
                0b01100000, //1
                0b11011010, //2
                0b11110010, //3
                0b01100110, //4
                0b10110110, //5
                0b10111110, //6
                0b11100000, //7
                0b11111110, //8
                0b11100110, //9
                };
int i = 0;                  //Esta variable controlará la posición en el vector
int j= 0,k= 0;              //Estas variables controlarán la posición del cursosr en la pantalla LCD resultará similar a movernos entre los elementos de una matriz.
bool borrar= false;         //Esta variable la usaremos como FLAG para saber cuando queremos borrar todo en la pantalla LCD, en nuestro caso cuando esté totalmente escrita.
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);  //Incializamos un objeto "LiquidCrystal" el cual será nuestra pantalla. Usaremos el constructor que tiene como parámtreos [RS,EN,D4,D5,D6,D7],aunque según la necesidad tiene varios más. 

//============================================================================================================================================================//
//                  La función "setup()" se ejecuta una sola vez al iniciar la placa por primera vez y cuando pulsamos el botón de RESET(se reinicia),aún     //
//                  así las variables que aparecen arriba están declaradas como globales(por eso es muy recomendable ponerle valores iniciales) ya que        //
//                  si las declaramos en el setup(),que sería lo más intuitivo,cuando queramos usarlas en otra parte del código no estarán definidas en ese   //
//                  scope.En esta función declararemos muy pocas cosas y casi siempre la usaremos para usar otras funciones o métodos que son necesarios al   //
//                  inicio del programa.                                                                                                                      //
//============================================================================================================================================================//

void setup() {
                                 //======================================================================================================//
  pinMode(latchPin, OUTPUT);     // pinMode(PIN,MODE) nos permite establecer para qué se va usar cada pin                                //
  pinMode(dataPin,OUTPUT);       //   pin->(int) Número de pin que vamos a establecer                                                    //
  pinMode(clockPin,OUTPUT);      //   mode->(constante) Modo que va a estar el pin                                                       //
  pinMode(botonUP,INPUT);        //             OUTPUT == SALIDA                                                                         //
  pinMode(botonDWN,INPUT);       //             INPUT == ENTRADA                                                                         //
  pinMode(botonENTER,INPUT);     // como se puede ver no hemos establecido la finalidad de todos los pines que hemos declarado antes ya  //
                                 // que algunos como RS,E,D4,D5... ya los establecen en las funciones que se usan(el constructor deL CD) //
                                 //======================================================================================================//
  
  
  lcd.begin(16,2);  //begin(colum,filas) es un método de LiquidCrystal para darle atributos iniciales al objeto, en este caso le damos las dimensiones de la pantalla(16x2 es mi caso) 
  //lcd.noAutoscroll(); noAutoscroll() es un método para no desplazar todo el texto escrito a la izquierda cada vez que se introduzca un carácter,es así por defecto y solo es útil si se usa el método autoscroll() antes(no es útil en nuestro caso)
    
}

//============================================================================================================================================================//
//                  La función "loop()" es la que se va a estar constantemente ejecutando en bucle mientras la placa esté encendida, si declaramos variables  //
//                  aquí se redefinirán con cada bucle,por eso cuando queramos declarar una variable con valor incial es mejor hacerla globlal.               //
//============================================================================================================================================================//
void loop() {
 lcd.setCursor(0,0); //el método setCursor(column,fila) pone el cursor de la pantalla(donde va a introducirse el siguiente carácter) en la coordenada deseada(se trabaja igual que con una matriz)
 
                    //======================================================================================================//
                    //     La función digitalRead(pin) nos permite leer estado [LOW-HIGH] del pin pasado como parámetro,    //
                    //     comparando con el estado contrario al que se encuentra por defecto nos permite crear una lógica  //
                    //     con la que dirigir el programa dependiendo que botón se pulsa.No olvidar que el pin debe haber   //
                    //     iniciado como INPUT.                                                                             //
                    //======================================================================================================//                                                               

  if( digitalRead(botonUP) ==  LOW){
    i ++;
    delay(500);                          
    if(i>9) i=0;                        //======================================================================================================//  
  }                                     //  Estas dos condicionales nos permiten incrementar o reducir la variable i , la cual vamos a usar     //
 if( digitalRead(botonDWN) ==  LOW){    //                           para recorrer el vector "numeros".                                         //
    i--;                                //  La función delay(n) para el código durante n milisegundos, esto se está usando para que al pulsar   //
    delay(500);                         //  el boton se haga más natural y que solo lo lea una vez,si no lo leería todas la veces que se        //
    if(i<0) i=9;                        // repitió loop() mientras lo teníamos pulsado(demasiadas veces).                                       //
  }                                     //======================================================================================================//




 if (digitalRead(botonENTER )== LOW){
   if(borrar){
     lcd.clear();
     borrar = false;                  //==============================================================================================================//
   }                                  // Esta condicional es la encargada de que se ecriba en la pantalla LCD,usaremos el método print(n) para        //
    lcd.setCursor(j,k);               // que se escriba en la pantalla.Usamos la  variable i ya que i==posición en el vector==número en esa posición. //
    lcd.print(i);                     // Para controlar donde se va escribiendo usamos las coordenadas j,k similar a como lo haríamos en una matriz.  //
    delay(300);                       // El método clear() borra todo en la pantalla,en este caso se usa cuadno borrar=true, y eso pasa cuando con j,k//
    j++;                              // alcanzamos el límite de la pantalla, es decir la coordenada [15][1].                                         // 
    if(j>15){                         //==============================================================================================================//
      j=0;
      k++;
      if(k>1){
        k=0;
        borrar=true;
      }
    } 
  }
  EscribirDigito(numeros[i]);   //función declarada y definida  más abajo
}

void EscribirDigito(byte numer){                 //============================================================================================================================//
  digitalWrite(latchPin, LOW);                   // digitalWrite(pin,estado) permite a un pin de salida digital(pin) dar una de las dos salidas digitales[LOW/HIGH]            //
  shiftOut(dataPin, clockPin, MSBFIRST, numer);  // shiftOut(pin1,pin2,orden,data) permite dar salida a datos de forma que un registro de desplazamiento pueda interpretar     //
  digitalWrite(latchPin, HIGH);                  //   pin1->pin de datos|pin2->pin del reloj|data->byte a pasar                                                                //
}                                                // según el orden del cableado entre las salidas del registro[Q0-Q7] y las entradas del display de 7 segmentos[A-dp] será un  //
                                                 // orden u otro.                                                                                                              //
                                                 //   orden->MSBFIRST == Most Significant Bit FIRST                                                                            //
                                                 //          LSBFIRST == Less Significant Bit FIRST                                                                            //
                                                 // El fin de la función EscribirDigito() es satisfacer el orden en el que funciona el resgistro de desplazamiento para dar 8  //
                                                 // salidas de una sola entrada(1 byte->8 bits). Cronograma explicativo:                                                       //
                                                 // Cronograma explicativo: https://programarfacil.com/wp-content/uploads/2016/02/Cronograma74HC595.jpg                        //
                                                 //============================================================================================================================//
                                                                                                                                                                //~@FabEwe57204//