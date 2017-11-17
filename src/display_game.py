#!/usr/bin/python3
import pygame as pg
import os
import fileinput

from math import *

pg.init()                                 # inicialização do sistema

# altura e largura da arena, em células
H, W = 15,15

# largura da célula
L = 20
# altura da célula
l = 2*L/sqrt(3)


# cria a janela
scr = pg.display.set_mode((int(W*L*1.5 + L), int(2*l*H +2*l)))
# só para simplificar, atualização da imagem
atu = pg.display.update

# pasta das imagens
img_folder = "../images/"


# pinta o fundo da janela
scr.fill((0,200,0))
atu()

def convert(i ,j):
    """
    Converte a coordenada (i,j) para a posição em pixels na janela
    """
    x = 1.5*i*L + L
    if (i%2 == 0):
        y = 2*l + 2*j*l
    else:
        y = l + 2*j*l
    return x,y

class Robô(pg.sprite.Sprite):
    """
    Representa um Robô, possui uma imagem
    """
    def __init__(s, img):
        """
        Construtor, img é o nome do arquivo com a imagem
        """
        pg.sprite.Sprite.__init__(s)
        s.image = pg.image.load(img_folder + img)
        s.rect = s.image.get_rect()

    def draw(s, i,j):
        """
        Desenha o robô na célula (i,j)
        """
        x, y = convert(i,j)

        # fronteiras do sprite
        l0,h0,l1,h1 = s.rect

        # corrije a posição de acordo com o tamanho do sprite
        s.rect.topleft = [x-l1/2,y-h1/2]
        # desenha
        scr.blit(s.image, s.rect)

class Cristal(pg.sprite.Sprite):
    """
    Representa um cristal, possui uma imagem
    """
    def __init__(s, img):
        """
        Construtor, img é o nome do arquivo com a imagem
        """
        pg.sprite.Sprite.__init__(s)
        s.image = pg.image.load(img_folder + img)
        s.rect = s.image.get_rect()

    def draw(s, i,j):
        """
        Desenha o cristal na célula (i,j)
        """
        x, y = convert(i,j)

        # fronteiras do sprite
        l0,h0,l1,h1 = s.rect

        # corrije a posição de acordo com o tamanho do sprite
        s.rect.topleft = [x-l1/2,y-h1/2]
        # desenha
        scr.blit(s.image, s.rect)

class Base(pg.sprite.Sprite):
    """
    Representa uma base, possui uma imagem
    """
    def __init__(s, img):
        """
        Construtor, img é o nome do arquivo com a imagem
        """
        pg.sprite.Sprite.__init__(s)
        if (os.path.isfile(img_folder + img)):
            s.image = pg.image.load(img_folder + img)
            s.rect = s.image.get_rect()

    def draw(s, i,j):
        """
        Desenha a base na célula (i,j)
        """
        x, y = convert(i,j)

        # fronteiras do sprite
        l0,h0,l1,h1 = s.rect

        # corrije a posição de acordo com o tamanho do sprite
        s.rect.topleft = [x-l1/2,y-h1/2]
        # desenha
        scr.blit(s.image, s.rect)


class cell:
    """
    Representa uma das células da arena
    """
    def __init__(s,i,j, terreno):
        """
        Construtor, i e j formam a coordenada
        """
        # Posição do centro
        s.cx, s.cy = convert(i,j)
        # Cor (pode ser passada para o construtor no futuro)
        s.terreno = terreno #plano, floresta, rio

        # Vértices do hexágono
        s.pontos = (
            (s.cx - L/2,   s.cy-l),
            (s.cx+L/2, s.cy-l),
            (s.cx+L, s.cy),
            (s.cx+L/2,   s.cy+l),
            (s.cx-L/2, s.cy+l),
            (s.cx-L, s.cy),
            )

    def draw(s) :
        """
        Desenha a célula
        """
        if (s.terreno == "plano"):
         cor = (200, 200, 200)
        elif (s.terreno == "floresta"):
         cor = (34,139,34)
        elif (s.terreno == "rio"):
         cor = (65, 48, 191)
        pg.draw.polygon(scr, cor, s.pontos, 0)
        pg.draw.lines(scr, (0,0,0), True, s.pontos, 2)


# Construção da matriz que representa a arena
arena = []
for i in range(H):
    arena.append([])
    for j in range(W):
        arena[i].append(cell(i,j,"plano"))
        arena[i][j].draw()

# lista dos robôs definidos
robs = []

# lista de bases
bases = [Base("base0.png"), Base("base1.png"), Base("base2.png"), Base("base3.png"), Base("base4.png")]

# Lista de quantidades de cristais
cristais = [Cristal("cristal1.png"), Cristal("cristal2.png"), Cristal("cristal3.png")]

# atualiza a janela
atu()

# Leitura dos comandos pela entrada padrão ou de um arquivo
for line in fileinput.input():
    r = line.split()

    # linha começando com 'fim', termina o programa
    if r[0] == 'fim':
        break

    # linha começando com 'rob', inclui um robô,
    # o segundo argumento na linha é a imagem
    if r[0] == 'robo':
        robs.append(Robô(r[1]))

    elif r[0] == 'cristal':
        cristais[int(r[1]) - 1].draw(int(r[2]), int(r[3]))

    elif r[0] == 'base':
       bases[int(r[1])].draw(int(r[2]), int(r[3]))

    elif r[0] == 'terreno':
        arena[int(r[1])][int(r[2])].terreno = r[3]
        arena[int(r[1])][int(r[2])].draw()

    else:
    # linha de movimentação:
    # robô, corrdenadas originais, coordenadas finais
        ri, oi, oj, di, dj = list(map(int, r))

    # redesenha a célula original (apaga o robô)
        if 0 <= oi  < W and 0 <= oj < H:
            arena[oi][oj].draw()
    # desenha o robô na célula de destino
        if 0 <= di  < W and 0 <= dj < H and ri < len(robs):
            robs[ri].draw(di,dj)

    # tempo de espera para atualização, apenas para testes
    pg.time.wait(100)

    atu()

pg.quit()
# Local variables:
# mode: python
# End:
