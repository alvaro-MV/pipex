./pipex infile cat -e "" ""
./pipex here\_doc DEL "cat -e" "" ""

Si resulta que el 

ft_printf --> Donde se sacan los errores de los ejecutables
ft_printf --> Donde se sacan los errores de los arhivos.

Ponerlos en checker_pipe

--------------------
## Caso 1: mirar el código de status.

exit: errores en función del status: imitar a bash.

Note the word "immediately"! I point this out because we who use Bash for casual scripting tend to think of our commands as synchronous, our scripts as completely sequential. We expect pipes to execute the left command, and pass it's output into the following command. But pipes use forking, and the commands are actually executed in parallel. For many commands this fact is functionally inconsequential, but sometimes it matters. For example, check out the output of: ps | cat. 


## Caso 2: Expandir $.

cat << $PATH | cat -e liliput :--> resultado: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/FireDaemon OpenSSL 3/bin/:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files/Git/cmd:/mnt/c/Program Files (x86)/Certbot/bin:/mnt/c/Python/Scripts/:/mnt/c/Python/:/mnt/c/Users/alvar/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/alvar/AppData/Local/Programs/Microsoft VS Code/bin$

## Caso 3: sleep

sleep 2 | sleep 2: solo pasan dos segundos.


## Caso 4: sleep | echo $?

	Primero saca 0 y luego espera dos segundos. El 0 asumimos que es del anterior proceso, como se demuestra poniendo antes un comando que no existe. Pero claro, puede ser que sleep se haya ido a sobar, pero sobar significa.

## Caso 5: cat << l infile | wc >> outfile
	Este caso ejecuta el heredoc, para posteriormente sudarle la polla y utilizar el contenido de infile que es el que traslada a la pipe. En este comportamiento, la pipe que se usa para implementar el heredoc puede salir en desventaja frente a usar un archivo, aunque en realidad da igual, porque en vez de leer de una pipe lee del archivo temporal y a tomar por el culo.


## Caso 6: parseo: ./pipex_bonus infile "ls" "cat" out

## Caso 7: parseo:  ./pipex_bonus infile "" cat out 
	zsh: no such file or directory: ./pipex_bonus. Saca sisgev con fsanitize.

## Caso 8: parseo: ./pipex_bonus infile "" cat out
	No hace nada, mirar fsanize.

## Caso 9: parseo: ./pipex_bonus 11 11 11 11 hola
	No crea el archivo hola, no crea el archivo hola, no saca un log para cada directorio.

## Caso 10: env -i bash ./pipex infile "ps aux" "grep cron" outi
	Segmentation fault en zsh. Mirar otros comandos, si es en general en el caso de zsh o solo en este comando y no
en otros.

## Caso 10: ./pipex osuddbfef "ps aux" "grep cron" outi
	En este caso bash no ejecuta el "ps aux" en la pipe, y por lo tanto, no escribe nada.
	En mi caso, si ejecuto el "ps aux".	

## Caso 11: cat | ls
	tiene que printar ls y despues quedarse esperando, y para salir de la espera hayq que pulsar enter, no ctr+D.
