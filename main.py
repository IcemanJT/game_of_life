import subprocess
from time import sleep
import pygame

BOARD_SIZE = 100
START_PAIRS = "custom_points/glider_gun.txt" 
CELL_SIZE = 8
FPS = 30

def compile_and_run_cpp(size, start_pairs_file):
    cpp_program = "GameOfLife"

    # comiles the cpp program
    compile_command = ["g++", cpp_program + ".cpp", "-o", cpp_program]
    subprocess.run(compile_command, check=True)

    # runs the cpp program as a subprocess
    run_command = ["./"+cpp_program, str(size), start_pairs_file]
    process = subprocess.Popen(run_command, stdout=subprocess.PIPE, stdin=subprocess.PIPE, text=True)

    return process

# draws the board from lines reaf from pipe
def draw_board(screen, lines):
    for y, line in enumerate(lines):
        for x, cell in enumerate(line.strip()):
            color = (255, 105, 180) if cell == 'X' else (0, 0, 0)
            pygame.draw.rect(screen, color, (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))

# main function
def main():
    gen = 0
    run = False
    prev_state = []
    lines = []
    try:
        pygame.init()
        screen = pygame.display.set_mode((BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE))
        pygame.display.set_caption(f"Game of Life - Generation {gen}")

        cpp_process = compile_and_run_cpp(BOARD_SIZE, START_PAIRS)
        
        clock = pygame.time.Clock()

        while True:        
            for event in pygame.event.get():
                # when x is clicked on the window
                if event.type == pygame.QUIT:
                    pygame.quit()
                    cpp_process.kill()
                    return
                #key bindings
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
                        cpp_process.stdin.write("next\n")
                        cpp_process.stdin.flush()
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

                

                prev_state = lines.copy()
                lines = []
                for i in range(BOARD_SIZE+1):
                    line = cpp_process.stdout.readline()
                    lines.append(line)
                
                if prev_state == lines:
                    run = False

                draw_board(screen, lines)
                pygame.display.set_caption(f"Game of Life - Generation {gen}")
                pygame.display.flip()
                
                cpp_process.stdin.write("next\n")
                cpp_process.stdin.flush()
                clock.tick(FPS)

    except KeyboardInterrupt:
        print("Visualization script terminated.")

if __name__ == "__main__":
    main()
