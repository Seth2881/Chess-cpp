import arcade

sheet = arcade.load_spritesheet('Chess_Pieces_Sprite.png')

pieces = {

    '''
    pawn   = 00001
    bishop = 00010
    knight = 00011
    rook   = 00100
    queen  = 00101
    king   = 00110
    '''

    'pawn' : 1,
    'bishop' : 2,
    'knight' : 3,
    'rook' : 4,
    'queen' : 5,
    'king' : 6
}

colors = {

    '''
    black = 01000
    white = 10000
    '''

    'black' : 8,
    'white' : 16,
}

'''
exemple : white pawn = 100001 ou 0b100001, black queen = 011000 ou 0b011000
'''

class Pieces:

    def __init__(self,color,pawn) -> None:
        self.piece = bin(color)+bin(pawn)