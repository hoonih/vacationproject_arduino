#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);

int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int tumblr=0;
int isbottom=1;

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("TDS service");
  lcd.setCursor(0, 1);
  lcd.print("App:ple Pi");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                   ");
  lcd.setCursor(0, 1);
  lcd.print("X");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("                   ");
  lcd.setCursor(0, 1);
  lcd.print("EDCAN");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                   ");
  lcd.setCursor(0, 1);
  lcd.print("Vacation Project");
 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Running...3");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Running..2");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Running.1");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tumblr EA");
  
  lcd.setCursor(0, 1);
  lcd.print("Press R button");
  
}

void loop() {                                                   
  if (Serial.available() > 0)
  {
    String input = Serial.readString(); 
    Serial.print(input);
    if (input == "qrscan\n")                                       //주 명령어
    {
      if (tumblr != 0)
      {
        tumblr_up();
        tumblr--;
        lcd_printea();
        if (tumblr == 0)
        {
          isbottom = 0;
          lcd_printerror_requiredown();
        }
      }
      else 
      {
        Serial.println("failed");
      }
    }
    else if (input == "up\n")                                     //기능 명령어(오류나는 경우 제외 사용X)
    {
      tumblr_up();
    }
    else if (input == "down\n")                                  //기능 명령어(오류나는 경우 제외 사용X)
    {
      tumblr_down();
    }
    else if (input == "reset\n")                                 //기능 명령어(텀블러가 없을때 판을 가장 아래로 내리는 코드)
    {
      tumblr_reset();
      isbottom=1;
      lcd_printerror_requirerefill();
    }
    else if (input == "refill\n")                               //기능 명령어(판이 가장 아래일때 텀블러를 채워 놓는 코드)
    {
      if (isbottom == 1)
      {
        
        refill();
        lcd_printea(); 
      }
      else 
        Serial.println("setting linear to bottom (use command: reset or press the button)");
    }
  }
  
}

void refill() {                                                //텀블러 채웠을때 호출 할 함수.
  tumblr = 4;
}


void tumblr_up() {                                                    //위로 한칸 올림
  Serial.println("up...");
  for (int i=0; i<20000; i++)   
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
  }
  digitalWrite(DIR,LOW);
  digitalWrite(ENA,LOW);
  digitalWrite(PUL,LOW);
}
void tumblr_down() {                                                  //아래로 한칸 내림
  Serial.println("down...");
  for (int i=0; i<20000; i++) 
  {
    digitalWrite(DIR,HIGH);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
  }
  digitalWrite(DIR,LOW);
  digitalWrite(ENA,LOW);
  digitalWrite(PUL,LOW);
}
void tumblr_reset()  {                                                 //아래로 4칸 내림
  Serial.println("reset...");
  for(int j=0; j<4; j++)
  {
    for (int i=0; i<20000; i++) 
    {
      digitalWrite(DIR,HIGH);
      digitalWrite(ENA,HIGH);
      digitalWrite(PUL,HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL,LOW);
      delayMicroseconds(100);
    }
  }
  digitalWrite(DIR,LOW);
  digitalWrite(ENA,LOW);
  digitalWrite(PUL,LOW);

}

void lcd_printea() {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tumblr EA");
  
  lcd.setCursor(0, 1);
  lcd.print(tumblr);
}
void lcd_printerror_requiredown() {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tumblr is lack");
  
  lcd.setCursor(0, 1);
  lcd.print("Press Rs button");
}

void lcd_printerror_requirerefill() {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Add Tumblr and");
  
  lcd.setCursor(0, 1);
  lcd.print("Press R button");
}
