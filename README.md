# **CONTROLE E SUPERVISÃO DE UM SISTEMA DE CALDEIRA** 🌡️ 
### Trabalho 01 da disciplina de **Software em Tempo Real** 2021.2 como requisito para segunda nota da disciplina.

#### Para execução e compilação dos arquivos:
- Ter instalado na máquina WSL.2 e uma distribuição Linux de sua preferência.
- Abrir a janela do PowerShell no caminho dos arquivos, localizados na pasta **execucao_**.
- Procurar **ip(WSL)** da máquina utilizando o comando: _ipconfig_
- Com o Java instalado, executar o seguinte comando com a porta:
      
      java -jar .\Aquecedor2021.jar 4545

- Utilizando a distribuição Linux instalada no seu computador, e com o compilador **gcc** instalado. 
  Executar o seguinte comando para compitalação dos arquivos utilizados:
       
       gcc -o monitor monitor.c atuadores.c bufduplo.c controles.c sensor.c socket.c tela.c -lpthread
- Executar, ainda no Linux, a main da aplicação utilizando o seguinte comando:
      
      ./monitor ip(WSL) 4545
