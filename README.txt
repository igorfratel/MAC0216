Membros do grupo:
	Igor Fratel Santana 9793565
	Renan Costa Laíz 9779089
	Renan Tiago dos Santos Silva 9793606

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
PRIMEIRA FASE:
Detalhes importantes:
 >No comando SAVE, o novo rbp vai apontar para a posição da pilha onde o antigo rbp está guardado (topo - 1)
 >A ordem esperada de comandos rotineiros para chamar uma função com variáveis locais seria: CALL -> SAVE -> ALC -> FRE -> REST -> RET
 	*No entanto, como a função fatorial recursiva passada para nós como teste não utiliza os comandos SAVE e REST, incluímos o SAVE no CALL e o REST no RET.
 	*Portanto, a ordem fica CALL -> ALC -> FRE -> RET.
 >Estavamos usando o numero de intruções a serem executadas pela maquina virtual como o numero de instruções no programa recebido.
  Isso não é o suficiente para programas com loop, portanto fixamos o número 100000

Como executar:
	python montador < programa.txt > motor.c
	make
	./motor
--------------------------------------------------------------------------------------------------------------------------------------------------------------------



SEGUNDA FASE:

Nosso programa ainda não está executável. Apenas escrevemos as funções pedidas e pretendemos organizar tudo até a terceira fase.


--------------------------------------------------------------------------------------------------------------------------------------------------------------------
TERCEIRA FASE:

>Como executar:

./montador prog0.txt...progN.txt <--- Recebe como argumento os arquivos .txt contendo os programas em linguagem de montagem a serem
																	  	executados pelos robôs do jogo. Gera um arquivo "programas.c" que contém os vetores de programas
																			de todos os programas passados como parâmetro e uma função que retorna esses vetores dado um índice.
																			Será usado pelo nosso programa para criar os robôs com seus devidos programas.

./make                           <--- Compilará os arquivos .c e gerará o executável "jogo", que é o principal do nosso EP

./gerador_terreno      					 <--- Gera o arquivo Terreno.txt que será usado pelo programa

./jogo                           <--- Executa a batalha de robôs

>jogo:
	O arquivo principal do nosso programa é o jogo.c, que de fato gera a simulação do jogo, chamando as funções que criam a arena,
	inserem os robôs, etc.
 	Por esse motivo, o executável gerado pelo comando make do nosso EP será "jogo"

>gerador_terreno.c:
	Programa criado com o intuito de inicializar os atributos da arena, de forma randômica, especificando localização das bases dos exércitos,
	dos repositórios de cristais (e quantidade de cada repositório), de cada robô e do tipo de terreno que cada célula deve ter.
	O mapa é inicializado a partir de um arquivo gerado pelo gerador_terreno, mas as posições dos robôs são aleatórias
	Quando executado o comando "./gerador_terreno", será gerado um arquivo Terreno.txt que será lido pelo nosso programa "jogo".

>montador:
	Versão alterada do montador das fases anteriores, para que mais de um programa seja montado.
	Recebe os arquivos de programas em linguagem de montagem e gera um arquivo programas.c conténdo os vetores dos programas,
	semelhante ao motor.c das fases anteriores. No entanto, ele não executa as instruções dos vetores, apenas contém uma função
	que os retorna (será chamada no jogo.c). Por exemplo, se a função "devolve_programa" for chamada com parâmetro 0, ela retornará
	o primeiro vetor de programa a ser montado.

>types.h
  Para evitar problemas de dependência circular nos #include espalhados pelo nosso programa, decidimos mover todas as structs,
	unions e etc para o arquivo types.h, que é incluido por quase todos os programas.

>macros.txt
  Arquivo contendo os "macros" usados para certas instruções e como enxergamos as coordenadas na matriz
	Por exemplo, ao invés de escrevermos um prog0.txt contendo:
		PUSH 0
		SYS 0
	Podemos escrever:
		PUSH CIMA
		SYS MOV
	Isso torna os programas mais claros

>display_game.py
	Fizemos algumas modificações nas instruções recebidas por esse programa, de forma a facilitar o desenvolvimento.
	Ele já conhece os arquivos de imagem das bases e as desenha com a instrução "base numero_arquivo x y".
	A instrução "cristal quantidade x y", desenha até 3 cristais em uma posição especificada
	A instrução "terreno x y tipo", desenha um terreno especificado na posição especificada, sendo que "tipo" pode ser
	"plano", "floresta" ou "rio". Células não especificadas recebem automaticamente o tipo "plano"
	O resto das instruções são iguais à versão anterior, "ri, oi, oj, di, dj".

>PUSHCELL
	Adicionamos uma nova instrução de máquin, chamada PUSHCELL que:
	"Recebe como argumento uma direção, empilha a célula adjacente ao robô que corresponde a essa direção.
	 Caso a célula não exista(por exemplo, se o robô estiver em uma borda), empilha -1."
	Ela foi escrita para ser usada em conjunto com ATR, para empilhar a célula desejada e depois
	receber algum atributo dela.
