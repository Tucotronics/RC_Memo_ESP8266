#include <Arduino.h>
#include <Tucotronics_RC_Memo.h>


Tucotronics_RC_Memo rele(2, 3, 4, 5);
void setup() {
  

}

void loop() {
  for (int canal = 1; canal <= 7; canal++){
    rele.ligar(canal);
    delay(1000);
  }
  for (int canal = 1; canal <= 7; canal++){
    rele.desligar(canal);
    delay(1000);
  }

}
