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
