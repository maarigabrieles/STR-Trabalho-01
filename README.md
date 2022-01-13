# STR-Trabalho-01
Trabalho 01 da disciplina de Software em Tempo Real 2021.2 como requisito para segunda nota da disciplina

Para compilação:
- Abrir janela do powershell na pasta dos arquivos.
- Encontrar ip da maquina utilizando o comando ipconfig > meu pc: 172.21.112.1
- Executar o seguinte comando com a porta:
java -jar .\Aquecedor2021.jar 4545

- Compilar os codigos que serão utilizado
gcc -o monitor monitor.c atuadores.c bufduplo.c controles.c sensor.c socket.c tela.c -lpthread

- Executar a main da aplicação
./controlecaldeira <ip> 4545
