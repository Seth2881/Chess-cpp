import pygame

sheet = pygame.image.load('pieces/Chess_Pieces_Sprite.png')
width, height = sheet.get_size()
sheetrect = sheet.get_rect()
slicewidth, sliceheight = width//6, height//2

sprites = []

print(sheetrect)

for y in range(0, height, sliceheight):
        for x in range(0, width, slicewidth):
            rect = pygame.Rect(x,y,slicewidth,sliceheight)
            sprite = sheet.subsurface(rect)

pygame.display.set_mode(size=(height, width))

# for sprite in sprites:
#      pygame.display

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

    def __init__(self,color,pawn,img) -> None:
        self.piece = bin(color)+bin(pawn)
        self.img = img