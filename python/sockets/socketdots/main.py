import pygame as pg
from typing import Tuple
from sock import ServSocket

WINDOW_SIZE = (900, 800)
MOVE_CONST = 10
PLAYER_SIZE_CONST = 40
BG = pg.image.load('images/bg.png')


class Game:
    running: bool
    clock: pg.time.Clock
    screen: pg.Surface
    comm_channel: ServSocket

    def __enter__(self):
        pg.init()
        pg.display.set_caption("Dotter")
        self.screen = pg.display.set_mode(WINDOW_SIZE)
        self.clock = pg.time.Clock()
        self.running = True
        self.screen.blit(BG, (0, 0))
        return self


    def __exit__(self, exc_type, exc_val, exc_tb):
        self.running = False
        pg.quit()

    def run(self):
        player1 = PlayerCircle((PLAYER_SIZE_CONST, PLAYER_SIZE_CONST), "red")
        player2 = PlayerCircle((PLAYER_SIZE_CONST, PLAYER_SIZE_CONST), "blue")

        while self.running:
            self.clock.tick(120)
            player1.move()

            player2.move()
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    self.running = False
            self.screen.blit(BG, (0, 0))
            player1.draw(self.screen)
            player2.draw(self.screen)
            pg.display.flip()

class PlayerCircle:
    x: int
    y: int
    color: str
    
    def __init__(self, position: Tuple[int, int], color) -> None:
        self.x = position[0]
        self.y = position[1]
        self.color = color

    def move(self):
        keys = pg.key.get_pressed()
        if keys[pg.K_UP]:
            if self.y - PLAYER_SIZE_CONST > 0:
                self.y -= MOVE_CONST
        if keys[pg.K_DOWN]:
            if self.y + PLAYER_SIZE_CONST < WINDOW_SIZE[1]:
                self.y += MOVE_CONST
        if keys[pg.K_RIGHT]:
            if self.x + PLAYER_SIZE_CONST < WINDOW_SIZE[0]:
                self.x += MOVE_CONST
        if keys[pg.K_LEFT]:
            if self.x - PLAYER_SIZE_CONST > 0:
                self.x -= MOVE_CONST

    def draw(self, screen: pg.Surface):
        pg.draw.circle(screen, self.color, (self.x, self.y), PLAYER_SIZE_CONST)


if __name__ == '__main__':
    with Game() as game:
        game.run()
