
#define motorPin 2
#define trigPin 4
#define echoPin 3

long previousMillis;  
long tempoAntes;
long interval = 30000; 
int degrau;
/*********** Propriedades do Tanque **************/
//em centimetros
float LadoMaior = 19.5;
float LadoMenor = 14.7;
float Altura    = 30.0;
float altura    = 0.0f;
float Nivel    = 0.0f;
float Volume    = LadoMaior*LadoMenor*Altura;
float VolumeAgora;
float VolumeAntes;
float Diferenca = 29.5;

long VazaoVolumetrica;
float porcento;
 int nivel;
float segundos;

float d=10.0;//comprimento.
float AreaSTCircValv = (PI*d*d)/4;
float VolumeValula = AreaSTCircValv*d; 
  
/****SENSRO DISTANCIA****/
float duration;
float distance;



void ondaDegrau(int val);
void alturaMedia(void);
void switchDegra(int degrau);
void imprimir(void);

void setup() {
  Serial.begin (9600);
  
  previousMillis   = 0;
  VazaoVolumetrica = 0;
  degrau           = 2;
  VolumeAntes      = 0;
  nivel            = NIVEL_21;
  segundos         = 0.0f;
  switchDegra(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  Serial.begin(9600);  
}

void loop() {
  unsigned long currentMillis;
  for(;;){
   currentMillis = millis();
  ondaDegrau(255);
  previousMillis = currentMillis;
   
   while((currentMillis-previousMillis) < interval){
       currentMillis = millis();
       alturaMedia();
       imprimir();
   }
  }
  
}


void alturaMedia(void){
  distance = 0;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = distance + (duration/2) / 29.1;
  
  if (distance >= 40 || distance <= 0){
    //Serial.println("Out of range");
    return;
  }else {
    Nivel = Diferenca-distance;
   // Nivel = distance;
    //Nivel = distance;
    VolumeAgora    = LadoMaior*LadoMenor*(Nivel);
    if(VolumeAgora > 0){
      porcento = (VolumeAgora/Volume)*100;  
    }else{
      porcento =0;
    }
    
    unsigned long currentMillis = millis();
    segundos = (float)currentMillis/1000;
    delay(100);
    
  }
  
}

void ondaDegrau(int val){
  analogWrite(motorPin, val);
  //Serial.println(val);
  delay(500);
}

void imprimir(void){
    Serial.print(Nivel,2);
    //Serial.print(";cm;");
    Serial.print(";");
    Serial.print(segundos);
    //Serial.print(";s;");
    Serial.print(";");
    Serial.print(VolumeAgora);
    //Serial.print(";cm3;");
    Serial.print(";");
    Serial.print(porcento);
    Serial.print(";");
    //Serial.print(";%;");
    Serial.print(degrau);
    //Serial.print(";V;");
    Serial.print(";");
    Serial.println(nivel);
    //Serial.println(";cm"); 
}

