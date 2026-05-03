import pygame, pybind11
import numpy as np
import sys
import board
from typing import cast

DEBUG = False


class Board:
    WHITE_PAWN: int
    BLACK_PAWN: int
    WHITE_ROOK: int
    BLACK_ROOK: int
    WHITE_KNIGHT: int
    BLACK_KNIGHT: int
    WHITE_BISHOP: int
    BLACK_BISHOP: int
    WHITE_QUEEN: int
    BLACK_QUEEN: int
    WHITE_KING: int
    BLACK_KING: int

    def __init__(self) -> None: ...
    def printBoard(self) -> None: ...
    def storeBoard(self) -> None: ...
    def possibleMoves(self, PieceCode: int, row: int, column: int) -> None: ...


BOARD = cast(Board, board.Board())
BOARD.printBoard()

pygame.init()

IMAGES = {}
PIECECODE = {
    1: "WHITE_PAWN",
    2: "WHITE_KNIGHT",
    3: "WHITE_BISHOP",
    4: "WHITE_ROOK",
    5: "WHITE_QUEEN",
    6: "WHITE_KING",
    -1: "BLACK_PAWN",
    -2: "BLACK_KNIGHT",
    -3: "BLACK_BISHOP",
    -4: "BLACK_ROOK",
    -5: "BLACK_QUEEN",
    -6: "BLACK_KING",
}
SCREENWIDTH, SCREENHEIGHT = 800, 800

ROWS, COLS = 8, 8

GRIDWIDTH = SCREENHEIGHT // ROWS

WINDOW = pygame.display.set_mode((SCREENWIDTH, SCREENHEIGHT))
CLOCK = pygame.time.Clock()

pygame.display.set_caption("Best Chess")
Running = True


def drawCanvas():
    mouse_x, mouse_y = pygame.mouse.get_pos()

    hover_col = mouse_x // GRIDWIDTH
    hover_row = mouse_y // GRIDWIDTH

    for row in range(ROWS):
        for col in range(COLS):
            if (row + col) % 2 == 0:
                color = (240, 217, 181)
                hover_color = (247, 228, 201)
            else:
                color = (181, 136, 99)
                hover_color = (199, 154, 109)
            if row == hover_row and col == hover_col:
                color = hover_color

            pygame.draw.rect(
                WINDOW,
                color,
                (col * GRIDWIDTH, row * GRIDWIDTH, GRIDWIDTH, GRIDWIDTH),
            )


def LoadImages(IMAGES):
    for ITEM in [
        "WHITE_PAWN",
        "BLACK_PAWN",
        "WHITE_ROOK",
        "BLACK_ROOK",
        "WHITE_KNIGHT",
        "BLACK_KNIGHT",
        "WHITE_BISHOP",
        "BLACK_BISHOP",
        "WHITE_QUEEN",
        "BLACK_QUEEN",
        "WHITE_KING",
        "BLACK_KING",
    ]:
        IMAGES[ITEM] = pygame.image.load(f"./assets/images/{ITEM.lower()}.png")


def blitImages(BOARD: Board):
    boardVector = np.array(BOARD.storeBoard())
    image = None
    x = None
    y = None

    def blitImageOnCell(PieceCode, row, column):
        image = IMAGES[PIECECODE[PieceCode]]
        x = column * GRIDWIDTH + (GRIDWIDTH - image.get_width()) // 2
        y = row * GRIDWIDTH + (GRIDWIDTH - image.get_height()) // 2

        WINDOW.blit(image, (x, y))

    for row in range(8):
        for column in range(8):
            if boardVector[row][column] != 0:
                blitImageOnCell(boardVector[row][column], row, column)


def drawPossibleMoves(BOARD: Board):
    mouse_x, mouse_y = pygame.mouse.get_pos()

    hover_col = mouse_x // GRIDWIDTH
    hover_row = mouse_y // GRIDWIDTH

    boardVector = np.array(BOARD.storeBoard())
    indices = np.where(
        BOARD.possibleMoves(boardVector[hover_row][hover_col], hover_row, hover_col)
    )
    if DEBUG:
        for row in BOARD.possibleMoves(
            boardVector[hover_row][hover_col], hover_row, hover_col
        ):
            print(row)
        print("\n")
    for r, c in zip(indices[0], indices[1]):
        pygame.draw.circle(
            surface=WINDOW,
            color=(0, 255, 0),
            center=((c + 0.5) * GRIDWIDTH, (r + 0.5) * GRIDWIDTH),
            radius=10,
        )


LoadImages(IMAGES=IMAGES)

while Running:
    drawCanvas()
    blitImages(BOARD)
    drawPossibleMoves(BOARD)
    pygame.display.flip()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    if DEBUG:
        CLOCK.tick(1)
    else:
        CLOCK.tick(60)
