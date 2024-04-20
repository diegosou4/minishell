# Minishell 2024



¡Bienvenido al fascinante mundo de Bash! Nuestro proyecto es bastante complejo por sí solo, pero hoy explicaremos un poco sobre lo que hicimos, lo que nos ayudó a lograr el resultado y, por supuesto, el camino que recorrimos para llegar allí. Desde ya, vale la pena señalar que nuestro minishell está lejos de ser el mejor que verás, pero lo que realmente importa es el aprendizaje adquirido a lo largo de este desafiante proceso.

La comunicación con tu compañero será clave, ya que el ejecutor necesita crear una estructura que el analizador pueda entender y trabajar en paralelo para proporcionar la estructura solicitada. Este paso es crucial en el proyecto: separar las responsabilidades de cada uno.

## Ejecución

Después de completar el análisis y entregar las estructuras necesarias, el primer paso es manejar el heredoc. Ejecutamos todos los heredocs antes de comenzar la ejecución, ya que los usamos con tuberías. A continuación, tenemos nuestra rutina de ejecución que siempre verifica si es un comando interno o un ejecutable. Vale la pena señalar un caso específico: cuando tenemos solo un comando y es un comando interno. Sin embargo, centrémonos en la rutina de ejecución general.

Dentro de esta rutina, verificamos si es necesario crear tuberías, es decir, si hay más de un comando. Creamos un proceso hijo y, dentro de él, manejamos las estructuras de redirección y sus comandos. Es crucial entender que estos pasos deben realizarse dentro del proceso hijo. Después de eso, determinamos de dónde leeremos y dónde escribiremos y luego ejecutamos nuestro comando. Debemos tener cuidado con las fugas de descriptores de archivo o con el cierre incorrecto de descriptores de archivo en momentos inapropiados.

## Comandos internos

Creo que el comando interno más complejo de implementar es `export`, ya que se utiliza en varios escenarios. Optamos por crear una copia del entorno, junto con una estructura que contenga tres tokens diferentes. Esto nos ayuda a mostrar el entorno de manera diferente, incluso consumiendo la misma estructura. La parte más desafiante fue crear la rutina que verifica si la clave existe y, dependiendo del caso, si agregamos un valor o simplemente concatenamos. Confieso que, debido a la complejidad de varios casos específicos, algunos no se manejaron correctamente. Los otros comandos internos son más simples, ya que dependen de funciones externas. Por ejemplo, `cd` ya tiene una función para redirigir a otra ubicación según la ruta proporcionada, `pwd` es una función que devuelve el directorio actual y `exit` solo requiere la conversión del número proporcionado, ya que los estados de salida van de 0 a 255.

## Reflexiones Finales

En mi opinión, la ejecución de nuestro proyecto fue muy buena. A pesar de algunas fallas, logramos cumplir los aspectos más importantes: compromiso con el proyecto, cumplimiento de plazos definidos y organización. Estos fueron los elementos clave que nos permitieron completar el proyecto con un sentido de logro.

## Resultado

![RESULTADO](https://i.imgur.com/0twltqs.png)

### Enlaces Útiles

[Presentación en Video](https://youtu.be/yHDzFRWmLGA?si=WkXmLU5iD3UsIq9r)

[Mind map- Minishell](https://github.com/zstenger93/minishell/blob/master/mindmap.png)

¡Gracias a todos, y mucha suerte! :)

Diegmore y Juan-pma  
42 Lisboa
