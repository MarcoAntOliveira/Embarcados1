// =====================================================
// Projeto: Menu Musical Interativo com LCD e LEDs
// Descrição: Sistema que controla 6 LEDs coloridos através de um menu LCD
//            com 4 músicas diferentes e modo festa
// =====================================================

// Inclui a biblioteca para controle do display LCD
#include <LiquidCrystal.h>

// =====================================================
// DEFINIÇÃO DOS PINOS E CONSTANTES
// =====================================================

// Definição dos pinos dos botões
#define botao_p_baixo   10    // Botão para descer no menu
#define botao_p_cima    9     // Botão para subir no menu
#define botao_seleciona 8     // Botão para selecionar/executar
#define botao_back      13    // Botão para voltar ao menu anterior

// Definição dos pinos dos LEDs
#define L_YE A5  // LED Amarelo
#define L_BU A4  // LED Azul
#define L_RE A3  // LED Vermelho
#define L_GR A2  // LED Verde
#define L_OR A0  // LED Laranja
#define L_WH A1  // LED Branco

// =====================================================
// VARIÁVEIS GLOBAIS
// =====================================================

int menu = 1;                 // Variável para controle do menu atual
int LedVerdePisca = 0;        // Flag para controle do piscar do LED verde

// Variáveis para controle de temporização
unsigned long UltimoMillis;   // Armazena o último tempo de execução do ciclo de 5ms

// Contadores para temporizações escalonadas
int Contador_100ms = 0;   // Contador para ações a cada 100ms
int Contador_500ms = 0;   // Contador para ações a cada 500ms
int Contador_1000ms = 0;  // Contador para ações a cada 1000ms
int Contador_2000ms = 0;  // Contador para ações a cada 2000ms
int Contador_4000ms = 0;  // Contador para ações a cada 4000ms

// Variáveis para controle de velocidade das músicas
int vel_song1 = 300;   // Velocidade da música 1 (Circles)
int vel_song2 = 150;   // Velocidade da música 2 (Baby)
int vel_song31 = 350;  // Velocidade primeira parte da música 3
int vel_song32 = 500;  // Velocidade segunda parte da música 3

// Inicialização do display LCD (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// =====================================================
// FUNÇÃO SETUP - CONFIGURAÇÃO INICIAL
// =====================================================
void setup() {
  // Inicializa comunicação serial para debug
  Serial.begin(9600);

  // Configura o display LCD (16 colunas, 2 linhas)
  lcd.begin(16, 2);

  // Configura os botões com pull-up interno
  pinMode(botao_p_baixo, INPUT_PULLUP);
  pinMode(botao_p_cima, INPUT_PULLUP);
  pinMode(botao_seleciona, INPUT_PULLUP);
  pinMode(botao_back, INPUT_PULLUP);

  // Configura os LEDs como saída
  pinMode(L_YE, OUTPUT);
  pinMode(L_BU, OUTPUT);
  pinMode(L_RE, OUTPUT);
  pinMode(L_GR, OUTPUT);
  pinMode(L_OR, OUTPUT);
  pinMode(L_WH, OUTPUT);

  // Exibe o menu inicial
  AtualizaMenu();
}

// =====================================================
// LOOP PRINCIPAL
// =====================================================
void loop() {
  // Controle do menu - Botão para baixo
  if (!digitalRead(botao_p_baixo)) {
    menu++;
    if (menu > 4) menu = 1;  // Limita o menu até a opção 4
    AtualizaMenu();
    delay(100);  // Debounce
    while (!digitalRead(botao_p_baixo));  // Espera soltar o botão
  }

  // Controle do menu - Botão para cima
  if (!digitalRead(botao_p_cima)) {
    menu--;
    if (menu < 1) menu = 4;  // Limita o menu até a opção 1
    AtualizaMenu();
    delay(100);  // Debounce
    while (!digitalRead(botao_p_cima));  // Espera soltar o botão
  }

  // Controle do menu - Botão seleciona
  if (!digitalRead(botao_seleciona)) {
    ExecutaAcao();
    AtualizaMenu();
    delay(100);  // Debounce
    while (!digitalRead(botao_seleciona));  // Espera soltar o botão
  }

  // Controle do menu - Botão voltar
  if (!digitalRead(botao_back)) {
    // Lógica para voltar ao menu principal
    if (menu == 11) menu = 1;
    else if (menu == 21) menu = 2;
    else if (menu == 31) menu = 3;
    else if (menu == 4) menu = 4;
    AtualizaMenu();
    delay(100);  // Debounce
    while (!digitalRead(botao_back));  // Espera soltar o botão
  }

  // Executa o modo festa se ativo
  if (menu == 4) {
    if ((millis() - UltimoMillis) >= 5) {
      UltimoMillis = millis();
      Coisas_5_mili();
    }
  }
}

// =====================================================
// FUNÇÕES DE CONTROLE DO MENU
// =====================================================

// Atualiza o display LCD com o menu atual
void AtualizaMenu() {
  lcd.clear();
  switch (menu) {
    case 1:
      lcd.print("1.circles - Post");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 11:
      lcd.print("Aumentar?");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 2:
      lcd.print("2.Baby - Justin");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 21:
      lcd.print("Aumentar?");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 3:
      lcd.print("3.Because of you");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 31:
      lcd.print("Aumentar?");
      lcd.setCursor(0, 1);
      lcd.print("Iniciar?");
      break;
    case 4:
      lcd.print("4. Party Mode");
      lcd.setCursor(0, 1);
      lcd.print("lets get started?");
      break;
  }
}

// Executa a ação correspondente ao menu atual
void ExecutaAcao() {
  switch (menu) {
    case 1: acao1(); break;   // Música Circles
    case 2: acao2(); break;   // Música Baby
    case 3: acao3(); break;   // Música Because of you
    case 4: acao4(); break;   // Modo festa
    case 11: acao11(); break; // Ajuste velocidade música 1
    case 21: acao21(); break; // Ajuste velocidade música 2
    case 31: acao31(); break; // Ajuste velocidade música 3
  }
}

// =====================================================
// FUNÇÕES DAS MÚSICAS
// =====================================================

// Música 1: Circles - Sequência de LEDs em círculo
void acao1() {
  lcd.clear();
  lcd.print("iniciando");
  for (int i = 0; i < 3; i++) {
    // Sequência: Amarelo → Laranja → Branco → Azul → Vermelho → Verde
    digitalWrite(L_YE, HIGH); delay(vel_song1); digitalWrite(L_YE, LOW);
    digitalWrite(L_OR, HIGH); delay(vel_song1); digitalWrite(L_OR, LOW);
    digitalWrite(L_WH, HIGH); delay(vel_song1); digitalWrite(L_WH, LOW);
    digitalWrite(L_BU, HIGH); delay(vel_song1); digitalWrite(L_BU, LOW);
    digitalWrite(L_RE, HIGH); delay(vel_song1); digitalWrite(L_RE, LOW);
    digitalWrite(L_GR, HIGH); delay(vel_song1); digitalWrite(L_GR, LOW);
  }
  lcd.print("fim da musica");
  menu = 11;  // Vai para submenu de ajuste de velocidade
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print("Vai p submenu11");
  delay(1500);
}

// Música 2: Baby - Todos os LEDs juntos e vermelho piscando
void acao2() {
  lcd.clear();
  lcd.print("iniciando");
  for (int i = 0; i < 12; i++) {
    // Todos os LEDs acendem juntos
    digitalWrite(L_YE, HIGH); digitalWrite(L_BU, HIGH);
    digitalWrite(L_RE, HIGH); digitalWrite(L_GR, HIGH);
    digitalWrite(L_OR, HIGH); digitalWrite(L_WH, HIGH);
    delay(vel_song2);

    // Todos os LEDs apagam
    digitalWrite(L_YE, LOW); digitalWrite(L_BU, LOW);
    digitalWrite(L_RE, LOW); digitalWrite(L_GR, LOW);
    digitalWrite(L_OR, LOW); digitalWrite(L_WH, LOW);
    delay(vel_song2);

    // Apenas o vermelho pisca
    digitalWrite(L_RE, HIGH); delay(vel_song2);
    digitalWrite(L_RE, LOW); delay(vel_song2);
  }
  lcd.print("fim da musica");
  menu = 21;  // Vai para submenu de ajuste de velocidade
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print("Vai p submenu21");
  delay(1500);
}

// Música 3: Because of you - LEDs em pares e todos juntos
void acao3() {
  lcd.clear();
  lcd.print("iniciando");
  for (int i = 0; i < 3; i++) {
    // Primeiro par: Amarelo e Azul
    digitalWrite(L_YE, HIGH); digitalWrite(L_BU, HIGH);
    delay(vel_song31);
    digitalWrite(L_YE, LOW); digitalWrite(L_BU, LOW);
    delay(vel_song31);

    // Segundo par: Vermelho e Verde
    digitalWrite(L_RE, HIGH); digitalWrite(L_GR, HIGH);
    delay(vel_song31);
    digitalWrite(L_RE, LOW); digitalWrite(L_GR, LOW);
    delay(vel_song31);

    // Terceiro par: Laranja e Branco
    digitalWrite(L_OR, HIGH); digitalWrite(L_WH, HIGH);
    delay(vel_song31);
    digitalWrite(L_OR, LOW); digitalWrite(L_WH, LOW);
    delay(vel_song31);

    // Todos os LEDs juntos
    digitalWrite(L_YE, HIGH); digitalWrite(L_BU, HIGH);
    digitalWrite(L_RE, HIGH); digitalWrite(L_GR, HIGH);
    digitalWrite(L_OR, HIGH); digitalWrite(L_WH, HIGH);
    delay(vel_song32);
    digitalWrite(L_YE, LOW); digitalWrite(L_BU, LOW);
    digitalWrite(L_RE, LOW); digitalWrite(L_GR, LOW);
    digitalWrite(L_OR, LOW); digitalWrite(L_WH, LOW);
    delay(vel_song32);
  }
  lcd.print("fim da musica");
  menu = 31;  // Vai para submenu de ajuste de velocidade
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print("Vai p submenu31");
  delay(1500);
}

// Modo festa: LEDs piscando em diferentes frequências
void acao4() {
  lcd.clear();
  lcd.print("starting the party");
  if ((millis() - UltimoMillis) >= 5) {
    UltimoMillis = millis();
    Coisas_5_mili();
  }
}

// =====================================================
// FUNÇÕES DE AJUSTE DE VELOCIDADE
// =====================================================

// Ajusta velocidade da música 1
void acao11() {
  lcd.clear();
  lcd.print("Executando 11");
  if (vel_song1 >= 50) {  // Limite mínimo de 50ms
    lcd.clear();
    vel_song1 -= 50;  // Aumenta a velocidade
    lcd.print(vel_song1);
  }
  delay(1500);
}

// Ajusta velocidade da música 2
void acao21() {
  lcd.clear();
  lcd.print("Executando 21");
  if (vel_song2 >= 50) {  // Limite mínimo de 50ms
    lcd.clear();
    vel_song2 -= 50;  // Aumenta a velocidade
    lcd.print(vel_song2);
  }
  delay(1500);
}

// Ajusta velocidade da música 3
void acao31() {
  lcd.clear();
  lcd.print("Executando 31");
  if (vel_song31 >= 50) {  // Limite mínimo de 50ms
    lcd.clear();
    vel_song31 -= 50;  // Aumenta a velocidade
    vel_song32 -= 50;  // Aumenta a velocidade
    lcd.print(vel_song31);
    lcd.print(" ");
    lcd.print(vel_song32);
  }
  delay(1500);
}

// =====================================================
// FUNÇÕES DE TEMPORIZAÇÃO (MODO FESTA)
// =====================================================

// Executada a cada 5ms
void Coisas_5_mili() {
  digitalWrite(L_WH, !digitalRead(L_WH));  // Inverte estado do LED branco
  digitalWrite(L_GR, !digitalRead(L_GR));  // Inverte estado do LED verde

  if (++Contador_100ms >= 20) {  // A cada 100ms (20 * 5ms)
    Contador_100ms = 0;
    Coisas_100_mili();
  }
}

// Executada a cada 100ms
void Coisas_100_mili() {
  digitalWrite(L_OR, !digitalRead(L_OR));  // Inverte estado do LED laranja
  digitalWrite(L_RE, !digitalRead(L_RE));  // Inverte estado do LED vermelho

  if (++Contador_500ms >= 5) {  // A cada 500ms (5 * 100ms)
    Contador_500ms = 0;
    Coisas_500_mili();
  }
}

// Executada a cada 500ms
void Coisas_500_mili() {
  digitalWrite(L_YE, !digitalRead(L_YE));  // Inverte estado do LED amarelo
  digitalWrite(L_BU, !digitalRead(L_BU));  // Inverte estado do LED azul

  if (++Contador_1000ms >= 2) {  // A cada 1000ms (2 * 500ms)
    Contador_1000ms = 0;
    Coisas_1000_mili();
  }
}

// Executada a cada 1000ms
void Coisas_1000_mili() {
  digitalWrite(L_YE, !digitalRead(L_YE));  // Inverte estado do LED amarelo
  digitalWrite(L_BU, !digitalRead(L_BU));  // Inverte estado do LED azul

  if (++Contador_2000ms >= 2) {  // A cada 2000ms (2 * 1000ms)
    Contador_2000ms = 0;
    Coisas_2000_mili();
  }
}

// Executada a cada 2000ms
void Coisas_2000_mili() {
  digitalWrite(L_OR, !digitalRead(L_OR));  // Inverte estado do LED laranja
  digitalWrite(L_RE, !digitalRead(L_RE));  // Inverte estado do LED vermelho

  if (++Contador_4000ms >= 2) {  // A cada 4000ms (2 * 2000ms)
    Contador_4000ms = 0;
    Coisas_4000_mili();
  }
}

// Executada a cada 4000ms
void Coisas_4000_mili() {
  digitalWrite(L_WH, !digitalRead(L_WH));  // Inverte estado do LED branco
  digitalWrite(L_GR, !digitalRead(L_GR));  // Inverte estado do LED verde
}


