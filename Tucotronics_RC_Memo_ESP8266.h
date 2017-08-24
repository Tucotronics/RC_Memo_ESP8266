#ifndef tucotronics_rc_memo_ESP8266h
#define tucotronics_rc_memo_ESP8266h

class Tucotronics_RC_Memo_ESP8266{
public:
    Tucotronics_RC_Memo_ESP8266(int pinA, int pinB, int pinC, int pinLD); 
    Tucotronics_RC_Memo_ESP8266(int pinA, int pinB, int pinC, int pinD, int pinLD); // Reservado para a placa RC15.
    void ligar(int canal);
    void desligar(int canal);
    void desligarTudo();
private:
    int _pinA;
    int _pinB;
    int _pinC;
    int _pinD; // Reservado para a placa RC15;
    int _pinLD;
    int _canalMaximo;
    void setPinos(int canal);
};
#endif
