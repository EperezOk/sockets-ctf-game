#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define CHALLENGES 12
#define BUFFER_SIZE 128
#define printPreguntaMsg() printf("----- PREGUNTA PARA INVESTIGAR -----\n")
#define printDesafioMsg() printf("------------- DESAFIO -------------\n");
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static int challenge1();
static int challenge2();
static int challenge3();
static int challenge4();
static int challenge5();
// src: https://stackoverflow.com/questions/3516398/define-a-program-section-in-c-code-gcc
static int challenge6() __attribute__((section(".RUN_ME")));
static int challenge7();
static int challenge8();
static int challenge9();
static int challenge10();
static int challenge11();
static int challenge12();

char buffer[BUFFER_SIZE+1];
int client;

void gameLoop(int fdClient) {
  int (*challenges[CHALLENGES])(void);
  
  client = fdClient;

  challenges[0] = &challenge1;
  challenges[1] = &challenge2;
  challenges[2] = &challenge3;
  challenges[3] = &challenge4;
  challenges[4] = &challenge5;
  challenges[5] = &challenge6;
  challenges[6] = &challenge7;
  challenges[7] = &challenge8;
  challenges[8] = &challenge9;
  challenges[9] = &challenge10;
  challenges[10] = &challenge11;
  challenges[11] = &challenge12;

  srand(getpid());
  int challenge = 0; 
  while(challenge < CHALLENGES) {
    system("clear");
    printDesafioMsg();
    if (challenges[challenge]() == 0)
      challenge++;
    else {
      printf("\nRespuesta incorrecta: %s\n", buffer);
      sleep(2);
    }
  }
  
  system("clear");
  printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n\n");
}

static int checkAnswer(char *answer) {
  int n;
  if ((n = read(client, buffer, BUFFER_SIZE)) == -1)
    handle_error("read");

  if (n > 0)
    buffer[n-1] = 0;
  else
    exit(0);

  return strcmp(answer, buffer);
}

static int challenge1() {
  printf(
    "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
    "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
    "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
    "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos"
    " y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta."
    "Además, deberán implementar otro programa para comunicarse conmigo.\n\n"
    "Deberán estar atentos a los easter eggs.\n\n"
    "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n\n");
  printPreguntaMsg();
  printf("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n\n");

  return checkAnswer("entendido");
}

static int challenge2() {
  printf(
    "The Wire S1E5\n"
    "5295 888 6288\n\n\n");
  printPreguntaMsg();
  printf("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n\n");
  
  return checkAnswer("itba");
}

static int challenge3() {
  printf("https://ibb.co/tc0Hb6w\n\n\n");
  printPreguntaMsg();
  printf("¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n\n");

  return checkAnswer("M4GFKZ289aku");
}

static int challenge4() {
  char *res = "La respuesta es fk3wfLCm3QvS";
  printf("EBADF...\n\n");

  if (write(13, res, strlen(res)) == -1)
    perror("write");

  printf("\n");
  printPreguntaMsg();
  printf(
    "¿Qué útil abstraccion es utilizada para comunicarse con sockets?"
    " ¿se puede utilizar read(2) y write(2) para operar?\n\n");

  return checkAnswer("fk3wfLCm3QvS");
}

char too_easy;

static int challenge5() {
  printf("respuesta = strings:235\n\n\n");
  printPreguntaMsg();
  printf("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n\n");

  return checkAnswer("too_easy");
}

static int challenge6() {
  printf(".init .plt .text ? .fini .rodata .eh_frame_hdr\n\n\n");
  printPreguntaMsg();
  printf(
    "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes."
    "¿Qué conviene más?\n\n");

  return checkAnswer(".RUN_ME");
}

static int challenge7() {
  printf("Filter error\n\n");

  char *ans = "La respuesta es K5n2UFfpFMUN\n";

  for (int i = 0; i < strlen(ans); i++) {
    for (int j = 0; j < rand() % 31; j++) {
      char c = (rand() % (126 - 32 + 1)) + 32;
      write(2, &c, 1);
    }
    printf("%c", ans[i]);
  }
  printf("\n");
  printPreguntaMsg();
  printf("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n\n");

  return checkAnswer("K5n2UFfpFMUN");
}

static int challenge8() {
  printf("¿?\n\n\n");
  printf("\033[30;40mLa respuesta es BUmyYq5XxXGt\033[0m\n");
  printPreguntaMsg();
  printf("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n\n");

  return checkAnswer("BUmyYq5XxXGt");
}

static int challenge9() {
  printf(
    "Latexme\n\n"
    "Si\n"
    "\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\n"
    "entonces\n"
    "y = \n\n");
  printPreguntaMsg();
  printf("sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n\n");

  return checkAnswer("u^v");
}

static int challenge10() {
  printf("quine\n\n");

  if (system("gcc quine.c -o quine") != 0)
    printf("\nENTER para reintentar.\n\n");
  else {
    printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

    if (system("./quine | diff quine.c -") != 0) {
      printf("\n%s\n", "diff encontró diferencias.");
      printf("\nENTER para reintentar.\n\n");
    }
    else
      printf("La respuesta es chin_chu_lan_cha\n\n"); 
  }
  
  printPreguntaMsg();
  printf("¿Cuáles son las características del protocolo SCTP?\n\n");

  return checkAnswer("chin_chu_lan_cha");
}

static void gdbme() {
  if ((long)getpid() == 0x12345678)
    printf("La respuesta es: gdb_rules\n\n");
}

static int challenge11() {
  printf("b gdbme y encontrá el valor mágico\n\n");
  printf("ENTER para reintentar.\n\n");
  gdbme();
  printPreguntaMsg();
  printf("¿Qué es un RFC?\n\n");

  return checkAnswer("gdb_rules");
}

// src: https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/
static double randn(double mu, double sigma) {
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1) {
    call = !call;
    return (mu + sigma * (double) X2);
  }
 
  do {
    U1 = -1 + ((double) rand () / RAND_MAX) * 2;
    U2 = -1 + ((double) rand () / RAND_MAX) * 2;
    W = pow (U1, 2) + pow (U2, 2);
  }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}

static int challenge12() {
  printf("Me conoces\n\n");

  for (int i = 0; i < 1000; i++)
    printf("%.6f ", randn(0, 1));

  printf("\n\n");

  printPreguntaMsg();
  printf("¿Fue divertido?\n\n");

  return checkAnswer("normal");
}
