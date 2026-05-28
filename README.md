# 🎮 Genius Arduino

Reimplementação do clássico jogo da memória **Genius** (Simon Says) utilizando Arduino. O jogador deve memorizar e repetir sequências crescentes de LEDs coloridos e sons gerados aleatoriamente pelo sistema.

---

## 📋 Modos de Jogo

| Modo | Descrição | Ativação |
|------|-----------|----------|
| **Memória** | Modo padrão. Repita a sequência de até 13 rodadas para vencer. | Inicialização normal |
---

## 🔌 Hardware Necessário

- Arduino Uno (ou compatível)
- 4x LEDs (Vermelho, Verde, Azul, Amarelo)
- 4x Botões (push button)
- 1x Buzzer passivo
- Resistores (para LEDs e botões)
- Protoboard e jumpers

---

## 🗺️ Pinagem

| Componente | Pino Arduino |
|------------|-------------|
| Botão Vermelho | 8 |
| Botão Verde | 7 |
| Botão Azul | 6 |
| Botão Amarelo | 9 |
| LED Vermelho | 4 |
| LED Verde | 3 |
| LED Azul | 2 |
| LED Amarelo | 5 |
| Buzzer | 10 |

---

## ⚙️ Configurações

No arquivo `geniusArduinoMilenio.ino`, é possível ajustar os parâmetros:

```cpp
#define RODADAS_PARA_VENCER     13    // Número de rodadas para vencer
#define LIMITE_DE_TEMPO_ENTRADA 3000  // Tempo limite para pressionar botão (ms)
```

---

## 🚀 Como Usar

1. Monte o circuito conforme a pinagem acima.
2. Abra o arquivo `geniusArduinoMilenio.ino` na IDE do Arduino.
3. Faça o upload para o seu Arduino.
4. Ao ligar, todos os LEDs acendem e um som de boas-vindas é tocado.
5. Pressione qualquer botão para iniciar o jogo.
6. Repita a sequência apresentada pelos LEDs/sons.
7. A cada rodada certa, uma nova etapa é adicionada à sequência.

---

## 📁 Estrutura do Projeto

```
arduino-genius/
├── geniusArduinoMilenio.ino   # Código principal do projeto
├── esquema.png                # Imagem do esquema
└── README.md                  # Este arquivo
```

---

## 👤 Autor

**Milenio Rocha**

- 🌐 Site: [mileniorocha.com.br](https://mileniorocha.com.br)
- 📸 Instagram: [@mileniorocha](https://instagram.com/mileniorocha)
- 💻 GitHub: [github.com/mileniorocha](https://github.com/mileniorocha)

---

## 📄 Licença

Este projeto é de código aberto. Sinta-se livre para usar, modificar e distribuir.
