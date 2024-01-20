import subprocess
from time import sleep
import pygame

BOARD_SIZE = 40
START_PAIRS = "custom_points/eaters.txt"
CELL_SIZE = 10
FPS = 2

def compile_and_run_cpp(size, start_pairs_file):
    cpp_program = "GameOfLife"

    compile_command = ["g++", cpp_program + ".cpp", "-o", cpp_program]
    subprocess.run(compile_command, check=True)

    # Run the compiled C++ program
    run_command = ["./"+cpp_program, str(size), start_pairs_file]
    process = subprocess.Popen(run_command, stdout=subprocess.PIPE, stdin=subprocess.PIPE, text=True)

    return process

def draw_board(screen, lines):
    for y, line in enumerate(lines):
        for x, cell in enumerate(line.strip()):
            color = (255, 255, 255) if cell == 'X' else (0, 0, 0)
            pygame.draw.rect(screen, color, (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))

def main():
    gen = 0
    run = False
    try:
        pygame.init()
        screen = pygame.display.set_mode((BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE))
        pygame.display.set_caption(f"Game of Life - Generation {gen}")

        cpp_process = compile_and_run_cpp(BOARD_SIZE, START_PAIRS)
        
        clock = pygame.time.Clock()

        while True:        
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    cpp_process.kill()
                    return
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_n:
                        cpp_process.stdin.write("board\n")
                        gen += 1
                        cpp_process.stdin.flush()

                        lines = []
                        for i in range(BOARD_SIZE+1):
                            line = cpp_process.stdout.readline()
                            lines.append(line)

                        draw_board(screen, lines)
                        pygame.display.set_caption(f"Game of Life - Generation {gen}")
                        pygame.display.flip()
                    elif event.key == pygame.K_SPACE:
                        run = True

                    elif event.key == pygame.K_ESCAPE:
                        pygame.quit()
                        cpp_process.kill()
                        return

            # while that runs when space is pressed
            while run:
                for event in pygame.event.get():
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_SPACE:
                            run = False
                        elif event.key == pygame.K_ESCAPE:
                            pygame.quit()
                            cpp_process.kill()
                            return
                    elif event.type == pygame.QUIT:
                        pygame.quit()
                        cpp_process.kill()
                        return

                cpp_process.stdin.write("board\n")
                gen += 1
                cpp_process.stdin.flush()

                lines = []
                for i in range(BOARD_SIZE+1):
                    line = cpp_process.stdout.readline()
                    lines.append(line)

                draw_board(screen, lines)
                pygame.display.set_caption(f"Game of Life - Generation {gen}")
                pygame.display.flip()
                
                clock.tick(FPS)

    except KeyboardInterrupt:
        print("Visualization script terminated.")

if __name__ == "__main__":
    main()
