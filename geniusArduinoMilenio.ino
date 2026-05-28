/******************************************************************
 *                                                                *
 * Projeto: Genius Arduino                                        *
 * Descrição: Jogo da memória Genius implementado com Arduino.    *
 *            O jogador deve repetir a sequência de LEDs e sons   *
 *            gerada aleatoriamente pelo sistema.                 *
 *                                                                *
 * Autor  : Milenio Rocha                                         *
 * Site   : mileniorocha.com.br                                   *
 * Instagram: @mileniorocha                                       *
 * GitHub : github.com/mileniorocha                               *
 *                                                                *
 * DEFINIÇÃO DAS NOTAS                                            *
 * https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody  *
 *                                                                *
 *****************************************************************/

#define NOTE_B0  31 
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978



/*--------------------------------
-                                -
- DEFININDO AS VARIAVEIS         -
-                                -
---------------------------------*/
// CONTROLA LED SELECIONADO
#define LED_SELECIONADO 0

// VERIFICA BOTÃO SELECIONADO
#define FLAG_BOTAO 0
#define FLAG_BOTAO_VERMELHO  (1 << 0)
#define FLAG_BOTAO_VERDE    (1 << 1)
#define FLAG_BOTAO_AZUL (1 << 2)
#define FLAG_BOTAO_AMARELO   (1 << 3)

// Definições dos pinos dos Botões
#define BOTAO_VERMELHO 8
#define BOTAO_VERDE 7
#define BOTAO_AZUL 6
#define BOTAO_AMARELO 9

// Definições dos pinos dos LEDs
#define LED_VERMELHO 4
#define LED_VERDE 3
#define LED_AZUL 2
#define LED_AMARELO 5

// Definição do pino do Buzzer
#define BUZZER 10

// Parâmetros do jogo
#define RODADAS_PARA_VENCER      13 // Número de rodadas para vencer o Jogo.
#define LIMITE_DE_TEMPO_ENTRADA   3000 // Tempo para pressionar um botão antes que o jogo acabe. 3000ms = 3 seg

#define MODO_MEMORIA 0
#define MODO_BATALHA 1
#define MODO_BEEGEES 2

// Variáveis de estado do jogo
byte modoJogo = MODO_MEMORIA; //Por padrão, vamos jogar o jogo da memória
byte tabuleiroJogo[32]; //Salva a combinação de botões à medida que avançamos
byte rodadaJogo = 0; //Conta o número de rodadas de sucesso que o jogador fez

void setup(){
  // Configuração dos pinos de entradas e saídas
  // Ativa pullup nas entradas
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  pinMode(LED_AMARELO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Verificação de modo
  modoJogo = MODO_MEMORIA; // Por padrãp inicia como Jogo da Memória

  // Verifique se o botão  amarelo está pressionado
  if (verificarBotao() == FLAG_BOTAO_AMARELO) tocar_musica_beegees();
  // Verifique se o botão verde está pressionado
  if (verificarBotao() == FLAG_BOTAO_VERDE){
    modoJogo = MODO_BATALHA; // Coloque o jogo no modo de batalha
    //Ligue o LED superior direito (verde)
    acenderLEDs(FLAG_BOTAO_VERDE);
    tocarTom(FLAG_BOTAO_VERDE, 150);
    acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_AZUL | FLAG_BOTAO_AMARELO); // Ligue os outros LEDs até você soltar o botão
    while(verificarBotao() != FLAG_BOTAO) ; // Aguarde até que o usuário pare de pressionar o botão
    //Agora não faça nada. O modo de batalha esta ativado
  }
  tocar_vencedor(); // Após a conclusão da configuração, diga olá ao mundo
}

void loop(){
  modoAtracao(); // Pisca luzes enquanto aguarda o usuário apertar um botão
  // Indique o início do jogo
  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_VERDE | FLAG_BOTAO_AZUL | FLAG_BOTAO_AMARELO); // Ativar todos os LEDs
  delay(1000);
  acenderLEDs(LED_SELECIONADO); // Desligue os LEDs
  delay(250);
  if (modoJogo == MODO_MEMORIA)
  {
    // Play no jogo de memória e recebe com resultado
    if (jogar_memoria() == true) 
      tocar_vencedor(); // Ganhou, toca som vitória
    else 
      tocar_perdedor(); // Perdeu, toca som derrota
  }
  if (modoJogo == MODO_BATALHA){
    jogar_batalha(); // Jogue o jogo até que alguém perca
    tocar_perdedor(); // Perdeu, toca som derrota
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//As seguintes funções estão relacionadas apenas ao jogo
// Jogue o jogo regular da memória
// Retorna 0 se o jogador perde ou 1 se o jogador ganhar
boolean jogar_memoria(void){
  randomSeed(millis()); // Gerador aleatório
  rodadaJogo = 0; // Redefinir o jogo para o começo
  while (rodadaJogo < RODADAS_PARA_VENCER) {
    adicionar_jogada(); // Adicione um botão aos movimentos atuais e reproduza-os
    reproduzirJogadas(); // Jogue de volta o tabuleiro do jogo atual
    // Em seguida, solicite ao jogador que repita a sequência.
    for (byte jogadaAtual = 0 ; jogadaAtual < rodadaJogo ; jogadaAtual++){
      byte escolha = esperar_botao(); // Veja o botão que o usuário pressiona
      if (escolha == 0) return false; // Se a espera expirar, o jogador perde
      if (escolha != tabuleiroJogo[jogadaAtual]) return false; // Se a escolha estiver incorreta, o jogador perde
    }
    delay(1000); // O jogador estava correto, espera antes de jogar
  }
  return true; // O jogador cumpriu todas as rodadas para ganhar!
}
// Jogue o modo de batalha especial de 2 jogadores
// Um jogador começa pressionando um botão e entregando ao outro jogador
// Esse jogador repete o botão e adiciona um, depois passa de volta.
// Esta função retorna quando alguém perde
boolean jogar_batalha(void){
  rodadaJogo = 0; // Redefinir o quadro do jogo de volta para um quadro
// Loop até alguém falhar
  while (1) {
    byte newButton = esperar_botao(); // Aguarde até que o usuário insira o próximo passo
    tabuleiroJogo[rodadaJogo++] = newButton; // Adicionar este novo botão ao array do jogo
    // Em seguida, solicite ao jogador que repita a sequência.
    for (byte jogadaAtual = 0 ; jogadaAtual < rodadaJogo ; jogadaAtual++){
      byte escolha = esperar_botao();
      if (escolha == 0) return false; // Se a espera expirar, o jogador perde.
      if (escolha != tabuleiroJogo[jogadaAtual]) return false; // Se a escolha estiver incorreta, o jogador perde.
    }
    delay(100); // Dê ao usuário 100ms extras para entregar o jogo ao outro jogador
  }
  return true; // Nós nunca devemos chegar aqui
}
// Reproduz o conteúdo atual dos movimentos do jogo
void reproduzirJogadas(void){
  for (byte jogadaAtual = 0 ; jogadaAtual < rodadaJogo ; jogadaAtual++){
    tocarTom(tabuleiroJogo[jogadaAtual], 150);
    delay(150); // 150 funciona bem. 75 fica rápido.
  }
}
// Adiciona um novo botão aleatório à sequência do jogo
void adicionar_jogada(void){
  byte newButton = random(0, 4); //min (incluido), max (excluido)
  // Temos que converter esse número, 0 até 3, para CHOICEs
  if(newButton == 0) newButton = FLAG_BOTAO_VERMELHO;
  else if(newButton == 1) newButton = FLAG_BOTAO_VERDE;
  else if(newButton == 2) newButton = FLAG_BOTAO_AZUL;
  else if(newButton == 3) newButton = FLAG_BOTAO_AMARELO;
  tabuleiroJogo[rodadaJogo++] = newButton; // Adicionar este novo botão ao array do jogo
}
//-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções controlam o hardware
// ilumina um determinado LEDs
// Passar em um byte composto de FLAG_BOTAO_VERMELHO, FLAG_BOTAO_AMARELO, etc
void acenderLEDs(byte leds){
  if ((leds & FLAG_BOTAO_VERMELHO) != 0)
    digitalWrite(LED_VERMELHO, HIGH);
  else
    digitalWrite(LED_VERMELHO, LOW);
  if ((leds & FLAG_BOTAO_VERDE) != 0)
    digitalWrite(LED_VERDE, HIGH);
  else
    digitalWrite(LED_VERDE, LOW);
  if ((leds & FLAG_BOTAO_AZUL) != 0)
    digitalWrite(LED_AZUL, HIGH);
  else
    digitalWrite(LED_AZUL, LOW);
  if ((leds & FLAG_BOTAO_AMARELO) != 0)

    digitalWrite(LED_AMARELO, HIGH);
  else
    digitalWrite(LED_AMARELO, LOW);
}
// Aguarde até que um botão seja pressionado.
// Retorna uma das cores do LED (LED_VERMELHO, etc.) se for bem-sucedida, 0 se expirar
byte esperar_botao(void){
  long startTime = millis(); // Lembre-se da hora em que começamos o loop

// Faz um loop até que passe muito tempo
  while ( (millis() - startTime) < LIMITE_DE_TEMPO_ENTRADA) {
    byte button = verificarBotao();

    if (button != FLAG_BOTAO){ 
      tocarTom(button, 150); // Reproduzir o botão que o usuário acabou de pressionar
      while(verificarBotao() != FLAG_BOTAO) ;  // Agora vamos esperar que o usuário libere o botão
      delay(10); // Isso ajuda com toques duplos acidentais
      return button;
    }
  }
  return FLAG_BOTAO; // Se chegarmos aqui, expiramos!
}

// Retorna um bit '1' na posição correspondente a FLAG_BOTAO_VERMELHO, FLAG_BOTAO_VERDE, etc.
byte verificarBotao(void){
  if (digitalRead(BOTAO_VERMELHO) == 0) return(FLAG_BOTAO_VERMELHO); 

  else if (digitalRead(BOTAO_VERDE) == 0) return(FLAG_BOTAO_VERDE); 

  else if (digitalRead(BOTAO_AZUL) == 0) return(FLAG_BOTAO_AZUL); 

  else if (digitalRead(BOTAO_AMARELO) == 0) return(FLAG_BOTAO_AMARELO);

  return(FLAG_BOTAO); // Se nenhum botão for pressionado, não retorne nenhum

}
// Acenda um LED e toque o tom

// Vermelho, superior esquerdo: 440Hz - 2.272ms - 1.136ms de pulso

// Verde, superior direito: 880Hz - 1.136ms - pulso de 0.568ms

// Azul, inferior esquerdo: pulso de 587.33Hz - 1.702ms - 0.851ms

// Amarelo, inferior direito: 784Hz - 1,276ms - pulso de 0,638ms

void tocarTom(byte which, int duracao_tom_ms){
  acenderLEDs(which); // Ligue um dado LED
  
  // Reproduz o som associado ao LED fornecido
  switch(which){

  case FLAG_BOTAO_VERMELHO:

    tocar_som(duracao_tom_ms, 1136); 

    break;

  case FLAG_BOTAO_VERDE:

    tocar_som(duracao_tom_ms, 568); 

    break;

  case FLAG_BOTAO_AZUL:

    tocar_som(duracao_tom_ms, 851); 

    break;

  case FLAG_BOTAO_AMARELO:

    tocar_som(duracao_tom_ms, 638); 

    break;
  }
  acenderLEDs(LED_SELECIONADO); // Desligue todos os LEDs
}

// Alterna o buzzer a cada buzz_delay_us, por uma duração de duracao_tom_ms.
void tocar_som(int duracao_tom_ms, int buzz_delay_us){
  // Converter tempo total de reprodução de milissegundos para microssegundos
  long duracao_tom_us = duracao_tom_ms * (long)1000;

  // Faz um loop até que o tempo restante de reprodução seja menor que um único buzz_delay_us
  while (duracao_tom_us > (buzz_delay_us * 2)){
    duracao_tom_us -= buzz_delay_us * 2; // Diminui o tempo de jogo restante
    // Alterna a campainha em várias velocidades

    digitalWrite(BUZZER, HIGH);

    delayMicroseconds(buzz_delay_us);


    digitalWrite(BUZZER, LOW);

    delayMicroseconds(buzz_delay_us);
  }
}

// Reproduzir o som e as luzes do vencedor
void tocar_vencedor(void){
  acenderLEDs(FLAG_BOTAO_VERDE | FLAG_BOTAO_AZUL);

  som_vencedor();

  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_AMARELO);

  som_vencedor();

  acenderLEDs(FLAG_BOTAO_VERDE | FLAG_BOTAO_AZUL);

  som_vencedor();

  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_AMARELO);

  som_vencedor();
}

// Som vencedor
// Este é apenas um som (chato) único que criamos, não há mágica nisso
void som_vencedor(void){
  // Alterna a campainha em várias velocidades
  for (byte x = 250 ; x > 70 ; x--){
    for (byte y = 0 ; y < 3 ; y++){
      digitalWrite(BUZZER, HIGH);

      delayMicroseconds(x);

      digitalWrite(BUZZER, LOW);

      delayMicroseconds(x);
    }
  }
}

// Jogue o som perdedor / luzes

void tocar_perdedor(void){
  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_VERDE);

  tocar_som(255, 1500);

  acenderLEDs(FLAG_BOTAO_AZUL | FLAG_BOTAO_AMARELO);

  tocar_som(255, 1500);

  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_VERDE);

  tocar_som(255, 1500);

  acenderLEDs(FLAG_BOTAO_AZUL | FLAG_BOTAO_AMARELO);

  tocar_som(255, 1500);

}

// Mostra uma tela de "modo de atração" enquanto aguarda o usuário pressionar o botão.
void modoAtracao(void){
  while(1){

    acenderLEDs(FLAG_BOTAO_VERMELHO);

    delay(100);

    if (verificarBotao() != FLAG_BOTAO) return;

    acenderLEDs(FLAG_BOTAO_AZUL);

    delay(100);

    if (verificarBotao() != FLAG_BOTAO) return;

    acenderLEDs(FLAG_BOTAO_VERDE);

    delay(100);

    if (verificarBotao() != FLAG_BOTAO) return;

    acenderLEDs(FLAG_BOTAO_AMARELO);

    delay(100);

    if (verificarBotao() != FLAG_BOTAO) return;
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções estão relacionadas apenas ao Easter Egg de Beegees
// Notas na melodia. Cada nota é sobre uma nota 1/8, "0" são descansos.

int melody[] = {

  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,

  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,

  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,

  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0};

int noteDuration = 115; // Isso essencialmente define o ritmo, 115 é quase certo para um groove disco :)

int LEDnumber = 0; // Mantém o controle de qual LED estamos ligados durante o ciclo de beegees

// Não faça nada além de tocar beegees ruins

// Esta função é ativada quando o usuário segura o botão inferior direito durante a energização

void tocar_musica_beegees(){
  // Ligue o LED inferior direito (amarelo)

  acenderLEDs(FLAG_BOTAO_AMARELO);

  tocarTom(FLAG_BOTAO_AMARELO, 150);

  acenderLEDs(FLAG_BOTAO_VERMELHO | FLAG_BOTAO_VERDE | FLAG_BOTAO_AZUL); // Ligue os outros LEDs até você soltar o botão

  while(verificarBotao() != FLAG_BOTAO) ; // Aguarde até que o usuário pare de pressionar o botão

  acenderLEDs(FLAG_BOTAO); // Desligue os LEDs

  delay(1000); // Espere um segundo antes de tocar música

 // Reproduzir música até você pressionar um botão
  while(verificarBotao() == FLAG_BOTAO) {
    // iterar sobre as notas da melodia:

    for (int thisNote = 0; thisNote < 32; thisNote++) {

      changeLED();

      tone(BUZZER, melody[thisNote],noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;

      delay(pauseBetweenNotes);

      // pare o tom tocando:
      noTone(BUZZER);
    }
  }
}

// Cada vez que esta função é chamada, a placa se move para o próximo LED

void changeLED(void){

  acenderLEDs(1 << LEDnumber); // Mude o LED

  LEDnumber++; // Ir para o próximo LED

  if(LEDnumber > 3) LEDnumber = 0; // Enrole o balcão, se necessário
}