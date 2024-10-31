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
Ingrese el nombre d elos jugadores, la dificultad y cuando este listo presione 'Y' para comenzar.
Las letras deben ingresarse 1 a 1 (ej: secuencia AR: respuesta A, enter, R, enter, y asi con todas las letra que tenga).

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
