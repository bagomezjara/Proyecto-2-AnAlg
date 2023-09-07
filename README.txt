El codigo presente crea un perfect hashing utilizando una estructura llamada tabla el cual contiene 3 enteros que serviran de informacion y un vector de
strings donde se almacenaran los datos. Se utiliza un vector de tablas para poder almacenar todos los k-mers. El funcionamiento de las funciones está especificado en el código
Para ejecutar el código, asegúrese que están en la misma carpeta el PerfectHashing.cpp y el input.txt, luego en su terminal de ubuntu compile el main usando el commando
g++ PerferctHashing.cpp -o PerfectHashing posterior a esto le debería aparecer un archivo .o en la carpeta, entonces ejecute ahora el comando ./PerfectHashing y el
programa debería comenzar a ejecutarse.
Inicialmente el programa tomará todo el texto de input.txt y lo separará en kmers y introducirá a un set, cuando termine con este proceso le pedirá a usted que ingrese una 
cota para los buckets esta cota se utilizará durante el primer hashing para que el espacio utilizado por los vectores de las tablas sea menor a la cota * n, como se 
especificó en el informe, el codigo loopea infinitamente para cotas menores o iguales a 2, por lo que se recomienda usar 4 como cota.
Una vez ingresada la cota, se realizarán todos los pasos para crear el perfect hashing y una vez terminado eso aparecerá un mensaje en consola pidiendo un genoma a buscar,
en este momento se puede ingresar un genoma a buscar dentro de la estructura o si desea cerrar el programa ingresar "0".
Ejemplo de input:
4
GCTTGCCATCGATCG
TGCGTGAAGAATTTC
0
para lo cual obtendrá el output:
No encontrado
Encontrado
