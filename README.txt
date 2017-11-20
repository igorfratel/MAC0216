Membros do grupo:
	Igor Fratel Santana 9793565
	Renan Costa Laiz 9779089
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

 make                           <--- Compilará os arquivos .c e gerará o executável "jogo", que é o principal do nosso EP

./gerador_terreno      					 <--- Gera o arquivo Terreno.txt que será usado pelo programa

./jogo                           <--- Executa a batalha de robôs

>jogo:
	O arquivo principal do nosso programa é o jogo.c, que de fato gera a simulação do jogo, chamando as funções que criam a arena,
	inserem os robôs, etc.
 	Por esse motivo, o executável gerado pelo comando make do nosso EP será "jogo"

>gerador_terreno.c:
	Programa criado com o intuito de inicializar os atributos da arena, de forma randômica, especificando localização das bases dos exércitos, dos repositórios de cristais (e quantidade de cada repositório), de cada robô e do tipo de terreno que cada célula deve ter. O mapa é inicializado a partir de um arquivo gerado pelo gerador_terreno, mas as posições dos robôs são aleatórias
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

Vida: Cada robô começa com 10 pontos de vida, sempre que for atacado, perde um ponto. Ao zerar sua vida, o robô é eliminado da arena. 
Se não houverem mais robôs, o exército é eliminado da arena.

Obs 1: Os robôs podem passar em cima dos cristais, uma vez que eles poderiam servir de "barreiras" quando os robôs já estivessem
carregados com um número de cristais suficiente.
Obs 2: O nosso programa não permite receber programas dos jogadores no meio da partida, pelo motivo de que os cristais estão visíveis
após o início do jogo, e mudar o programa já sabendo aonde estão os cristais perderia a graça do jogo, assim como não mostrar os
cristais para os jogadores.
Obs 3: Pergunta-se ao usuário duas vezes o número de exércitos quanto o número de robôs, tais perguntas servem para rodar o
gerador_terreno.c e o jogo.c. Decidimos por não unificar as perguntas em um único código pois pretendemos deixar a comunicação com o
jogador a mais claro possível na quarta e última fase do projeto.
Obs 4: Por definição, decidimos que a arena será de 15 x 15, sendo o número mínimo de exércitos igual
a 2 e o máximo igual a 5, para permitir a boa fluidez e jogabilidade do jogo. Mais do que isso, definiu-se que os exércitos devem ter
entre 1 e 5 robôs.
Obs 5: O que define um robô pertencer a um exército é a cor do hexágono que aparece abaixo do robô, e não os personagens (pokemons) em si.

PARA TESTAR:
Dentro da pasta "programasteste" foram definidos alguns programas a serem inputados junto com um terreno apropriado para o teste.
Vale ressaltar que, os terrenos gerados nessa seção foram gerados apenas para visualização, não possuem aleatoriedade de atributos
como cristais e terrenos, são apenas programas de teste. Para rodá-los, basta colocá-los na pasta "src" e compilar o programa como
especificado acima (não sendo necessário criação de uma arena, uma vez que o Terreno.txt para ambos os testes já está feito).

cristais_e_robos: Dois exércitos, um robô em cada exército. Teste que visa mostrar como os robôs interagem com os cristais quando ambos
dividem a mesma célula.

recolhe_cristal: Dois exércitos, um robô em cada exército. Teste que visa mostrar como os robôs colhem os cristais.

Os arquivos prog0.txt e prog1.txt também representam um teste simples, em que os robôs ficam em loop, não importando em qual arena eles
estão.