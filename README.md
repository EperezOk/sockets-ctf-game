# TP3 SO - README

## Introduction

The aim of this project is to learn about the Socket mechanism in Linux while building a CTF game, which will consist in a server that handles connections and outputs the different questions to the clients.

## Autores

- Baliarda Gonzalo 61490
- Pérez Ezequiel 61475
- Ye Li Valentín 61011

## Entregables

- En la carpeta `src` se encuentra el código de los programas cliente y servidor.
- En el archivo `respuestas.md` se encuentran las respuestas a los desafíos.
- En el archivo `desarrollo.pdf` se encuentra un paso a paso más detallado de los desafíos y respuestas breves a las preguntas de investigación.

## Compilación y ejecución

Para compilar los archivos, se recomienda tener docker instalado con el contenedor `agodio/itba-so:1.0` dado por la cátedra.

1) Ejecutar `make all` en la carpeta base.
2) Correr el servidor con `./server`
3) Correr el cliente con `./client` en otra consola
4) Seguir las instrucciones que imprime el servidor, ingresando las respuestas del lado del cliente.
