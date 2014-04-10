/*
Copyright (c) 2014, Giovanni D'Italia
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


//denied 7segment matrix
int matrix[10][7] = {0,0,0,0,0,0,1,
                    1,0,0,1,1,1,1,
                    0,0,1,0,0,1,0,
                    0,0,0,0,1,1,0,
                    1,0,0,1,1,0,0,
                    0,1,0,0,1,0,0,
                    0,1,0,0,0,0,0,
                    0,0,0,1,1,1,1,
                    0,0,0,0,0,0,0,
                    0,0,0,1,1,0,0};

int dig[4]={0,0,0,0}; //mm,hh
int blinker=0,sec_blink=0;
int lp; //in setClock is used to exit from all nested while
unsigned long mill,err=0,varmillis; //time variables
int i,j;

void setup() {
  for(i= 0; i<12; i++)pinMode(i,OUTPUT); //initializes OUTPUT pin 0 -11
  pinMode(12,INPUT); //pins for pushbutton
  pinMode(13,INPUT);
  mill=millis(); //start clock
}

//print dig[4] from 7segment matrix
void printDig(int timing){
  for(i = 7;i<11;i++){
    digitalWrite(i,1);
    for(j=0;j<7;j++){
      digitalWrite(j,matrix[dig[i-7]][j]);
    }
    delay(timing);
    digitalWrite(i,0);

}
}

//add a minute in dig[4]
void aMinute(){
      if(dig[0]<9)dig[0]++;
      else{
        dig[0]=0;
        if(dig[1]<5)dig[1]++;
        else{
          dig[1]=0;
          if(dig[2]<9){
            if(dig[3]<2)dig[2]++;
            if(dig[3]==2)
            if(dig[2]==3){dig[2]=0;dig[3]=0;}
            else dig[2]++;
          }
          else{dig[2]=0;
               dig[3]++;
          }
           }
        }
      }

/*Check pushbutton for set clock
  the minutes to be increased individually
  the hours together
*/
void setClock(){
 lp=1; 
 if(digitalRead(13)==1){
   delay(500);
   while(lp){
     printDig(20);
   
     if(digitalRead(12)==1){
     delay(100);
     dig[0]++;
     if(dig[0]>9)dig[0]=0;
     }
   
     if(digitalRead(13)==1){
       delay(500);
       while(lp){
         printDig(20);
         if(digitalRead(12)==1){
         delay(100);
         dig[1]++;
         if(dig[1]>5)dig[1]=0;
       }
       
     if(digitalRead(13)==1){
       delay(500);
       while(lp){
         printDig(20);
         if(digitalRead(12)==1){
         delay(100);
         if(dig[3]<2){dig[2]++;
         if(dig[2]>9){dig[2]=0;dig[3]++;}}
         else{
           if(dig[2]>3){dig[3]=0;dig[2]=0;}
           else dig[2]++;}
       }
       if(digitalRead(13)==1){lp=0;
       delay(500);
       }
     }
     }
     }
     }
     }mill=millis();
     }
}

void loop() {
  printDig(2);
  setClock();
  varmillis = millis();
  if(varmillis-mill>(60000-err)){ //every minute
    err=(varmillis-mill)-60000; //reduce error in one minute
    aMinute();
    mill=varmillis;
  }
  sec_blink=sec_blink+1; //blink dots on the screen every 200 loop
    if(sec_blink>=200){
    digitalWrite(11,blinker);
    blinker = ~blinker;
    sec_blink=0;
    }
}
