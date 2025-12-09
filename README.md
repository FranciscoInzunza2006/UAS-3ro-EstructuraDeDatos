## Paco's File System
Este proyecto es un una suite de consola para trabajar con un sistema de archivos virtual, permite realizar operaciones basicas como crear, eliminar y mover archivos.

### Comandos
El programa usa comandos para su operación.

| Comando | Descripción |
| ------- | ----------- |
| mkdir | Crea una nueva carpeta en la dirección dada. |
| touch | Crea un nuevo archivo en la dirección dada. |
| mv | Mueve un archivo a una nueva dirección. |
| rm | Mueve a la papelera el archivo en la dirección dada. |
| ren | Renombra un archivo. |
| cd | Cambia la dirección de la consola. |
| search | Checa si un archivo existe en la dirección dada. |
| restore | Restaura un archivo de la papelera a su dirección previa. | 
| clear-trash | Vacía la papelera. |
| dir | Muestra los contenidos de la carpeta especificada de forma recursiva. |
| path | La dirección absoluta del archivo especificado. |
| save | Exporta el sistema de archivos en formato JSON. El resultado se guarda en un archivo en la dirección dada (en tu computadora). |
| load | Carga el sistema de archivos guardado formato JSON. El archivo está en tus archivos reales. |
| cls | Limpia la pantalla. |
| help | Muestra los comandos disponibles, también se usa para ver los argumentos de los comandos. |
| exit | Cerrar el programa.|

## Compilación
El proyecto cuenta con archivos **CMakeLists.txt** para automatizar el proceso de compilación. 
El proyecto usa **GTest** para realizar pruebas.
