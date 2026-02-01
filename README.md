
*Este projeto foi criado como parte do currículo da 42 por Pepinhei.*

# Minitalk

## Descrição
O **Minitalk** é um projeto de comunicação entre processos (IPC - Inter-Process Communication) desenvolvido no ambiente UNIX. O objetivo central é criar um sistema de troca de mensagens entre um programa **cliente** e um **servidor** utilizando exclusivamente sinais UNIX (`SIGUSR1` e `SIGUSR2`).

O projeto desafia o estudante a manipular operações bit-a-bit (bitwise operations) para transmitir dados de forma serializada, garantindo a integridade da mensagem e a sincronização entre os dois processos distintos.

## Instruções

### Compilação
O projeto utiliza um `Makefile` para gerenciar a compilação. Para gerar os executáveis, utilize os comandos abaixo:

```bash
# Compila o cliente e o servidor
make

Como Executar
Inicie o servidor:

Bash
./server
O servidor será iniciado e exibirá seu PID (Process ID). Mantenha este terminal aberto.

Inicie o cliente em outro terminal:

Bash
./client [PID_DO_SERVIDOR] "Sua mensagem aqui"
Substitua [PID_DO_SERVIDOR] pelo número exibido no passo anterior.

Recursos
Referências Relacionadas
Man signal (7): Visão geral sobre sinais no Linux.

struct sigaction {
               void (*sa_handler)(int);
               void (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t sa_mask;
               int sa_flags;
           };

Man sigaction (2): Documentação sobre o tratamento avançado de sinais.

Beej's Guide to Unix IPC: Guia clássico sobre comunicação entre processos.

Bitwise Operations em C: Tutorial sobre manipulação de bits.

Uso de Inteligência Artificial
Neste projeto, a IA (Gemini 2.0 Flash) foi utilizada para as seguintes tarefas:

Estruturação de Documentação: Organização e formatação deste arquivo README conforme as diretrizes da 42.

Revisão de Lógica: Auxílio na compreensão teórica do funcionamento dos sinais SIGUSR1 e SIGUSR2 para transmissão binária.

Refinamento de Código: Sugestão de boas práticas para garantir que o código fosse resiliente a race conditions leves durante o recebimento de bits.

Escolhas Técnicas
Protocolo Binário: Utilizei o sinal SIGUSR1 para representar o bit 0 e o SIGUSR2 para o bit 1.

Manipulação de Caracteres: A mensagem é decomposta em 8 bits por caractere, enviados do bit mais significativo (MSB) para o menos significativo (LSB).

Sincronização: (Se você implementou o bônus) Foi implementado um sistema de handshake onde o servidor confirma o recebimento de cada bit antes de o cliente enviar o próximo, evitando a perda de dados.

Markdown
## Recursos

### Referências Relacionadas
* [Man sigaction (2)](https://man7.org/linux/man-pages/man2/sigaction.2.html): Documentação oficial sobre o tratamento de sinais com sigaction.
* [Unix Signal Handling](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html): Guia da GNU C Library sobre sinais.

### Uso de Inteligência Artificial
Neste projeto, a IA (Gemini) foi utilizada para:
* **Estruturação de Documentação:** Organização e formatação deste arquivo README.
* **Explicação Técnica:** Detalhamento do funcionamento da `struct sigaction` e das flags `sa_sigaction` e `sa_mask`.
* **Depuração:** Auxílio na identificação de problemas de concorrência e recepção de sinais em alta velocidade.

## Escolhas Técnicas

### Manipulação de Sinais com `sigaction`
Em vez da função simplificada `signal`, utilizei a `struct sigaction` pelos seguintes motivos:
* **Acesso ao PID do Remetente:** Ao configurar a flag `SA_SIGINFO`, o servidor ganha acesso à estrutura `siginfo_t`, permitindo identificar exatamente qual PID (o cliente) enviou o sinal. Isso é essencial para o envio de confirmações (handshake).
* **Bloqueio de Sinais:** O uso de `sa_mask` permite bloquear outros sinais enquanto um sinal está sendo processado, prevenindo condições de corrida (*race conditions*) e corrupção de dados durante a reconstrução dos bits.
* **Persistência:** Diferente de algumas implementações de `signal`, o `sigaction` não precisa ser reestabelecido após cada sinal recebido.