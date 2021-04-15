#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

char pulsacion;       // almacena la tecla pulsada
int  contador = 1;    // cuenta el nivel del menu en el que se esta
const byte ROWS = 4;  //Cuatro Filas
const byte COLS = 4;  //Cuatro Columnas 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6}; //Puntos de conexion del teclado al arduino FILAS
byte colPins[COLS] = {5,4,3,2}; //Puntos de conexion del teclado al arduino COLUMNAS
Keypad Teclado1 = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Configura el teclado
LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del I2C el codigo 0x27 cambiar a
                                  // 0x3F , 0x20 , 0x38 , 

////////////////////////Prototipo de funciones//////////////
void intro_0();
void menu_1();
void accion_1();
void menu_2();
void accion_2();
void intermitente(); 

////////////////////////////////// Void Setup() ///////////
void setup () { 
 lcd.init();
 lcd.backlight();
 pinMode(12, OUTPUT);
 intro_0();             // muestra el intro de  bienvenida
} 

////////////////////////// Void loop() ///////////////////////
void loop(){
 pulsacion = Teclado1.getKey() ;  // Lee la tecla pulsada
 if (pulsacion != 0) {      
    lcd.clear();
    delay(100);
 } 
 if(contador == 2){ menu_2();accion_2();}
 if(contador == 1){ menu_1();accion_1();}
 
}  
///////// Fin del void loop(), inician las Funciones///////////////

/////////////////////Intro_0 //////////////////////////////
void intro_0(){ 
 lcd.clear();  // Borra el  LCD
 lcd.setCursor(3,0);         // Se posiciona en la Columna 3, Fila 0
 lcd.print("BIENVENIDO ");
 lcd.setCursor(1,1);
 lcd.print("PRUEBA DE MENU");
 delay(4000);                // espera 4 segundos mostrando el intro
 lcd.clear();
}

/////////////////////Menu_1  //////////////////////////////////
void menu_1(){ 
   lcd.setCursor(0,0);
   lcd.print("ON    >1  ");
   lcd.setCursor(10,0);
   lcd.print("OFF >2");   
   lcd.setCursor(0,1);
   lcd.print("INTER >3  "); 
   lcd.setCursor(10,1);
   lcd.print("MAS >*");
}

/////////////////////Accion 1 //////////////////////////////
void accion_1(){ 
  if(pulsacion == '1') digitalWrite(12,HIGH);
  if(pulsacion == '2') digitalWrite(12,LOW);
  if(pulsacion == '3') intermitente();
  if(pulsacion == '*') contador=2;
}

/////////////////////Menu_2  //////////////////////////////////
void menu_2(){ 
   lcd.setCursor(0,0);
   lcd.print("LUZ  >1   ");
   lcd.setCursor(8,0);
   lcd.print("TIEMPO>2");
   lcd.setCursor(0,1);
   lcd.print("MENU >#          ");
}

/////////////////////accion_2  //////////////////////////////////
void accion_2(){ 
  if(pulsacion == '1') contador=3;
  if(pulsacion == '2') contador=4;
  if(pulsacion == '#') contador=1;
}

/////////////////////intermitente  //////////////////////////////////
void intermitente(){ 
  digitalWrite(12,HIGH);
  delay(300);
  digitalWrite(12,LOW);
  delay(300);
  digitalWrite(12,HIGH);
  delay(300);
  digitalWrite(12,LOW);
  delay(300);
}