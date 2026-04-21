import pygame

class Board:
    def __init__(self,position:str='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq – 0 1') -> None:

        '''
        position is written with the FEN method
        starting game position : rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq – 0 1

        majuscule = white
        minuscule = black

        r = rook ; n = knight ; b = bishop ; q = queen ; k = king

        pour plus d'info : https://www.pousseurdebois.fr/cours/notation-fen/#:~:text=Comment%20sauvegarder%20une%20position%20aux,positions%20sur%20une%20interface%20graphique.
        '''

        self.position = self.loadposition(position)

        self.board = 'p'

    def loadposition(self,position):
        load = position.split(' ')
        board = load[0].split('/')

        return board,load[1],load[2],load[3],load[4],load[5]