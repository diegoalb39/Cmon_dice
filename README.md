# CMON DICE

Este proyecto es una simulacion del famoso juego "C_mon_dice", en el que los jugadores deben
seleccionar los colores que vayan en el orden en que aparecieron.
El proyecto fue desarrollado en el lenguaje "C" y se utilizo codeblocks como entorno de desarrollo.

## Comenzando 🚀

_Estas instrucciones te permitirán obtener una copia del proyecto en funcionamiento en tu máquina local para propósitos de desarrollo y pruebas._

### Pre-requisitos 📋
	Lenguaje: C
	Entorno de desarrollo: codeblocks
	API: Random.org
	Libreria utilizada: cURL

### Instalación 🔧

  Instalar Curl en Windows (https://curl.se/windows/). Descargue la misma version que su codeblocks (32/64 bits)
  
	Descomprimir e zip y pasar esa carpeta a una ubicación que no la vayan a borrar
	Agregar dentro de PATH (como variable de entorno) la ubicación a la carpeta
	“bin”
 
	En Codeblocks: Settings > Compiler > Linker Settings: agregar ubicación a
	“lib\libcurl.dll.a"
	En Codeblocks: Settings > Compiler > Search directories > Compiler y Resource
	compiler: agregar ubicación a
	“include"
	En Codeblocks: Settings > Compiler > Search directories > Linker: agregar ubicación a “lib”
Para las funciones multimedia debe colocar el archivo "WinMM.Lib" que se encuentra en la carpeta multimedia en:
Settings > Compiler > Linker Settings.

Compila el proyecto y ejecútalo.
## Ejecutando ⚙️

Ejecute el proyecto y siga las instrucciones del juego para jugar. 
Al inicio de cada juego, se va a:
- Ingresar los nombres de los jugadores
- Elegir la dificultad (fácil, medio, difícil)
- Sortear el orden de los jugadores
- Mostrar las configuraciones del juego (cantidad de vidas para cada
participante, cantidad de segundos en los que tienen que ingresar la
secuencia, cantidad de tiempo que van a poder ver la secuencia)
Luego:
- Empieza el primer jugador sorteado
- El sistema le muestra la primera secuencia al jugador durante X tiempo,
una letra a la vez.
- El jugador tiene Y segundos para ingresar la secuencia, letra por letra.
Cualquier otro caracter ingresado será ignorado a menos que sea el
de usar las vidas
- Si se le acaba el tiempo y no contesta, automáticamente se indicará que
el tiempo finalizó. Si tiene una vida, puede volver para atrás N cantidad
de jugadas (según vidas tenga) y tiene un segundo intento. Si no tiene
vidas, el juego finaliza para esa persona y le toca al siguiente
participante.
- Si ingresa correctamente la secuencia, el programa le muestra al
jugador la siguiente secuencia
- Si ingresa la secuencia, pero es incorrecta, el programa le va a indicar
que puede deshacer los últimos movimientos, según la cantidad de vidas
que tenga.
- Por cada round se van sumando puntos, y el jugador que obtenga la
mayor cantidad de puntos es el ganador.
Los puntos de cada jugador de la siguiente manera:
- Por cada secuencia bien ingresada, sin usar vida, se recibe +3 puntos
- Por cada secuencia bien ingresada, pero usando vida, se recibe +1
punto.
 Ganará la persona con mayor cantidad de puntos. En caso de que hayan 2
personas con la mayor cantidad de puntos (ejemplo: Jugador 1 y jugador 3
hicieron 10 puntos cada uno, mientras que el jugador 2 hizo 7 puntos),
entonces el jugador 1 y 3 serán los ganadores.

Nota 1: Los niveles de dificultad son:
- Fácil
- Medio
- Difícil
Estos niveles de dificultad son configurables mediante un archivo txt.
Ejemplo:
Dificultad elegida: Media. Tiempo que se muestra la secuencia por pantalla: 5
segundos. Cantidad de tiempo que tiene la persona para contestar: 10
segundos. Cantidad de vidas: 1
### Analice las pruebas end-to-end 🔩

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```

### Y las pruebas de estilo de codificación ⌨️

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```
## Construido con 🛠️

Mucho esfuerzo y amor. Codigo en lenguaje C, libreria cURL para trabajar con la API y asincronismo para manejo del tiempo en segundos reales
(no quiero ser redundante especificando lenguaje y cURL otra vez, sino lo dejamos).

## Autores ✒️


## Licencia 📄

Este proyecto está bajo la Licencia (Pipí Cucú y asociados).

## Expresiones de Gratitud 🎁

* Comenta a otros sobre este proyecto 📢
* Si te gustó el juego: Invita una cerveza 🍺 o un café ☕ a alguien del equipo.
* Da las gracias públicamente 🤓.
* Dona con cripto a esta dirección: `calle falsa 123`.
