/*
  Tucotronics_RC_Memo.cpp - Biblioteca para uso da placa de comando de relês RC-Memo com microcontroladores baseados no ESP8266.
  
*/

#if defined(ARDUINO_ARCH_ESP8266)
#include <Arduino.h>

#include <Tucotronics_RC_Memo_ESP8266.h>
#else
#error "Plataforma não suportada."
#endif

//extern volatile uint32_t PIN_OUT;
/**
* @brief Construtor para a placa RC7.
* @param pinA Número do pino da saída digital do ESP8266 (LSB).
* @param pinB Número do pino da saída digital do ESP8266.
* @param pinC Número do pino da saída digital do ESP8266 (MSB).
* @param pinLD Número do pino da saída digital do ESP8266 usado para ligar ou desligar os canais.
* @comment Pode-se usar os numeros definidos como D0, D1, D2, etc...
*/
Tucotronics_RC_Memo_ESP8266::Tucotronics_RC_Memo_ESP8266(int pinA, int pinB, int pinC, int pinLD){
    _canalMaximo = 7;
    _pinA = pinA;
    _pinB = pinB;
    _pinC = pinC;
    _pinLD = pinLD;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinLD, OUTPUT);
}

Tucotronics_RC_Memo_ESP8266::Tucotronics_RC_Memo_ESP8266(int pinA, int pinB, int pinC, int pinD, int pinLD){
    _canalMaximo = 15;
    _pinA = pinA;
    _pinB = pinB;
    _pinC = pinC;
    _pinD = pinD;
    _pinLD = pinLD;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinLD, OUTPUT);
}

/**
* @brief Desliga todos os canais.
* @comment Pode-se usar este metodo no setup() para evitar canais ligados quando a placa é energizada.
*/
void Tucotronics_RC_Memo_ESP8266::desligarTudo(){
    for (int canal = 1; canal <= _canalMaximo; canal++){
        desligar(canal);
    }
}

/**
* @brief Liga um canal.
* @param canal Numero do canal para ligar.
*/
void Tucotronics_RC_Memo_ESP8266::ligar(int canal){
    
    digitalWrite(_pinLD, HIGH);
    setPinos(canal);
}

/**
* @brief Desliga um canal.
* @param canal Numero do canal para desligar.
*/
void Tucotronics_RC_Memo_ESP8266::desligar(int canal){
    
    digitalWrite(_pinLD, LOW);
    setPinos(canal);
}

/**
* @brief Define os pinos de saída A, B e C.
* @param canal Canal selecionado.
* @remark O artigo do Pete em https://tech.scargill.net/ws2812b-success-on-the-esp-12/ pode ajudar a entender melhor os obscuros registradores do ESP8266.
*/
void Tucotronics_RC_Memo_ESP8266::setPinos(int canal){

    if (canal <= _canalMaximo){
        int reg;

        reg  = READ_PERI_REG(PERIPHS_GPIO_BASEADDR);
        reg &= ~(1 << _pinA);
        reg &= ~(1 << _pinB);
        reg &= ~(1 << _pinC);
        WRITE_PERI_REG( PERIPHS_GPIO_BASEADDR, reg );

        reg  = READ_PERI_REG(PERIPHS_GPIO_BASEADDR);
        reg |= (((canal >> 0) & 1) << _pinA);
        reg |= (((canal >> 1) & 1) << _pinB);
        reg |= (((canal >> 2) & 1) << _pinC);
        WRITE_PERI_REG( PERIPHS_GPIO_BASEADDR, reg );

    }
}