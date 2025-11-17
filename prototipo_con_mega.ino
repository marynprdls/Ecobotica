// Definición de pines  
const int pinMotorA1 = 8;  
const int pinMotorA2 = 9;  
const int pinMotorB1 = 10;  
const int pinMotorB2 = 11; 

const int ENA = 7;  
const int ENB = 12;


const int pinAdelante = 3;   
const int pinAtras = 43;   
const int pinDerecha = 30;   
const int pinIzquierda = 33 ;   
const int pinEjecutar = 37;
const int pinReset = 47; // Pin para el botón de reset    

const int pinLEDRojo = 5; // Pin para el LED rojo  
const int pinLEDVerde = 6; // Pin para el LED verde

const int pinLEDIzq = 27; // Pin para el LED boton  izq
const int pinLEDder = 28; // Pin para el LED boton derecha
const int pinLEDAdelante = 4; // Pin para el LED boton arriba
const int pinLEDAtras = 38; // Pin para el LED boton abajo
const int pinLEDEjecutar = 24; // Pin para el LED boton ejecutar
const int pinLEDReset =50 ; // Pin para el LED boton reset

const int pinBuzzer = 13; // Pin para el Buzzer

int movimientos[20];  // Array para guardar hasta 20 movimientos  
int contadorMovimientos = 0;  // Contador para los movimientos  

// Definición de velocidad
const int speed =  110;


// Definición de notas  
#define NOTE_B 494    // La nota B (si)   
#define NOTE_E 330    // La nota E (mi)  
#define NOTE_Fs 740   // La nota F# (fa sostenido)  
#define NOTE_Gs 415   // La nota G# (sol sostenido) 

// Duración de las notas  
#define NOTE_DURATION 500 // 500ms

void setup() {  
  // Inicializa los pines de los motores  
  pinMode(pinMotorA1, OUTPUT);  
  pinMode(pinMotorA2, OUTPUT);  
  pinMode(pinMotorB1, OUTPUT);  
  pinMode(pinMotorB2, OUTPUT);
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  // Inicializa los pines de los motores
  digitalWrite(pinMotorA1, LOW);  
  digitalWrite(pinMotorA2, LOW);  
  digitalWrite(pinMotorB1, LOW);  
  digitalWrite(pinMotorB2, LOW);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
    
  // Inicializa los pines de los botones  
  pinMode(pinAdelante, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinAdelante), moverAdelante, FALLING);  
  pinMode(pinAtras, INPUT); 
  attachInterrupt(digitalPinToInterrupt(pinAtras), moverAtras, FALLING); 
  pinMode(pinDerecha, INPUT);  
  attachInterrupt(digitalPinToInterrupt(pinDerecha), girarDerecha, FALLING);
  pinMode(pinIzquierda, INPUT); 
  attachInterrupt(digitalPinToInterrupt(pinIzquierda), girarIzquierda, FALLING); 
  pinMode(pinEjecutar, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinEjecutar), ejecutarMovimientos, FALLING);
  pinMode(pinReset, INPUT); // Configura el pin de reset
  attachInterrupt(digitalPinToInterrupt(pinReset), resetMovimientos, FALLING);

  // Inicializa los pines del LED y Buzzer  
  pinMode(pinLEDRojo, OUTPUT);  
  pinMode(pinLEDVerde, OUTPUT);
  pinMode(pinLEDIzq, OUTPUT);
  pinMode(pinLEDder, OUTPUT); 
  pinMode(pinLEDAdelante, OUTPUT);
  pinMode(pinLEDAtras, OUTPUT);
  pinMode(pinLEDEjecutar, OUTPUT);
  pinMode(pinLEDReset, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);  
  
  // Reproducir la melodía una vez al inicio  
  // "Day-O"  
  tone(pinBuzzer, NOTE_B);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  delay(100);  
  
  tone(pinBuzzer, NOTE_E);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  delay(100);  
  
  // "Daylight come and me wanna go home"  
  tone(pinBuzzer, NOTE_B);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  delay(100);  
  
  tone(pinBuzzer, NOTE_E);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  delay(100);  
  
  tone(pinBuzzer, NOTE_Fs);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  delay(100);  

  // Finalizar la melodía  
  tone(pinBuzzer, NOTE_Gs);  
  delay(NOTE_DURATION);  
  noTone(pinBuzzer);  
  
  //Parpadeo que ocurre al  iniciar 
  //Indica que ya está listo el  robot para  recibir instrucciones
  // Repetir la secuencia 3 veces  
  for (int i = 0; i < 3; i++) {  
    // Encender el LED rojo  
    digitalWrite(pinLEDRojo, HIGH);  
    delay(500); // Mantiene el LED rojo encendido durante 500 ms  
    digitalWrite(pinLEDRojo, LOW);  
    
    // Encender el LED verde  
    digitalWrite(pinLEDVerde, HIGH);  
    delay(500); // Mantiene el LED verde encendido durante 500 ms  
    digitalWrite(pinLEDVerde, LOW);  
  }  
  
  
  // Apagar los LEDs y el buzzer al inicio  
  digitalWrite(pinLEDRojo, LOW);  
  digitalWrite(pinLEDVerde, LOW);
  digitalWrite(pinLEDIzq, LOW);
  digitalWrite(pinLEDder, LOW); 
  digitalWrite(pinLEDAdelante, LOW);
  digitalWrite(pinLEDAtras, LOW);
  digitalWrite(pinLEDEjecutar, LOW);
  digitalWrite(pinLEDReset, LOW); 
  noTone(pinBuzzer); 
}  

void loop() {  
  // Verificación de botones y registro de movimientos  
  if (digitalRead(pinAdelante) == HIGH) {   
    guardarMovimiento(1);  // 1 representa 'adelante'
    activarBuzzer();  
    activarLEDAdelante();  
  } else if (digitalRead(pinAtras) == HIGH) {   
    guardarMovimiento(2);  // 2 representa 'atras' 
    activarBuzzer();  
    activarLEDAtras(); 
  } else if (digitalRead(pinDerecha) == HIGH) {    
    guardarMovimiento(3);  // 3 representa 'derecha'
    activarBuzzer();  
    activarLEDder();  
  } else if (digitalRead(pinIzquierda) == HIGH) {    
    guardarMovimiento(4);  // 4 representa 'izquierda'
    activarBuzzer();  
    activarLEDizq();  
  } else if (digitalRead(pinEjecutar) == HIGH) {  
    activarLEDEjecutar();  
    activarBuzzer();
    ejecutarMovimientos();
  } else if (digitalRead(pinReset) == HIGH) {  
    activarBuzzer();  
    activarLEDReset();
    resetMovimientos(); // Llama a la función de reset
  } else {  
    // Apagar LED y buzzer si no se presionan botones  
    digitalWrite(pinLEDRojo, LOW);  
    digitalWrite(pinLEDVerde, LOW); 
    digitalWrite(pinLEDIzq, LOW);
    digitalWrite(pinLEDder, LOW); 
    digitalWrite(pinLEDAdelante, LOW); 
    digitalWrite(pinLEDAtras, LOW);
    digitalWrite(pinLEDEjecutar, LOW);
    digitalWrite(pinLEDReset, LOW);
    noTone(pinBuzzer);  
  }  
 
}  

void moverAdelante() {  
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(pinMotorA1, LOW);  
  digitalWrite(pinMotorA2, HIGH);  
  digitalWrite(pinMotorB1, HIGH);  
  digitalWrite(pinMotorB2, LOW);  
  delay(1000);  // Tiempo de avance puede ser ajustado  
  pararMotores();
  delay(200);  
}  

void moverAtras() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);  
  digitalWrite(pinMotorA1, HIGH);  
  digitalWrite(pinMotorA2, LOW);  
  digitalWrite(pinMotorB1, LOW);  
  digitalWrite(pinMotorB2, HIGH);  
  delay(1000);  
  pararMotores();
  delay(200);  
}  

void girarDerecha() { 
  analogWrite(ENA, speed);
  analogWrite(ENB, speed); 
  digitalWrite(pinMotorA1, HIGH);  
  digitalWrite(pinMotorA2, LOW);  
  digitalWrite(pinMotorB1, LOW);  
  digitalWrite(pinMotorB2, HIGH);  
  delay(1000);  
  pararMotores(); 
  delay(200); 
}  

void girarIzquierda() {  
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(pinMotorA1, LOW);  
  digitalWrite(pinMotorA2, HIGH);  
  digitalWrite(pinMotorB1, HIGH);  
  digitalWrite(pinMotorB2, LOW);  
  delay(1000);  
  pararMotores();
  delay(200);  
}  

void pararMotores() {  
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(pinMotorA1, LOW);  
  digitalWrite(pinMotorA2, LOW);  
  digitalWrite(pinMotorB1, LOW);  
  digitalWrite(pinMotorB2, LOW);  
}  

void guardarMovimiento(int movimiento) {  
  if (contadorMovimientos < 20) {  
    movimientos[contadorMovimientos] = movimiento;  
    contadorMovimientos++;  
  }  
}  

void ejecutarMovimientos() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);  
  for (int i = 0; i < contadorMovimientos; i++) {  
    switch (movimientos[i]) {  
      case 1: moverAdelante(); break;  
      case 2: moverAtras(); break;  
      case 3: girarDerecha(); break;  
      case 4: girarIzquierda(); break;  
    }  
  }  
}

void resetMovimientos() {  
  contadorMovimientos = 0; // Reinicia el contador  
  for (int i = 0; i < 20; i++) {  
    movimientos[i] = 0; // Opcional: reinicia el array  
  }  
  Serial.println("Movimientos reiniciados.");  
}

void activarLEDrojo() {  
  digitalWrite(pinLEDRojo, HIGH);
  delay(100); 
  digitalWrite(pinLEDRojo, LOW); 
}  

void activarLEDverde() {  
  digitalWrite(pinLEDVerde, HIGH);
  delay(100);  
  digitalWrite(pinLEDVerde, LOW);
}
void activarLEDizq() {  
  digitalWrite(pinLEDIzq, HIGH);
  delay(100);  
  digitalWrite(pinLEDIzq, LOW);
}

void activarLEDder() {  
  digitalWrite(pinLEDder, HIGH);
  delay(100);  
  digitalWrite(pinLEDder, LOW);
}

void activarLEDAdelante() {  
  digitalWrite(pinLEDAdelante, HIGH);
  delay(100);  
  digitalWrite(pinLEDAdelante, LOW);
}

void activarLEDAtras() {  
  digitalWrite(pinLEDAtras, HIGH);
  delay(100);  
  digitalWrite(pinLEDAtras, LOW);
}

void activarLEDEjecutar() {  
  digitalWrite(pinLEDEjecutar, HIGH);
  delay(100);  
  digitalWrite(pinLEDEjecutar, LOW);
}

void activarLEDReset() {  
  digitalWrite(pinLEDReset, HIGH);
  delay(100);  
  digitalWrite(pinLEDReset, LOW);
}

void activarBuzzer() {  
  tone(pinBuzzer, 1000); // Tono de 1000 Hz
  delay(100);
  noTone(pinBuzzer);  
}  
