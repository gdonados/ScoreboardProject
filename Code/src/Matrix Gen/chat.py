import pygame

# Initialize Pygame
pygame.init()

# Set up the window dimensions
square_size = 10  # Size of each square in pixels
width = 64 * square_size  # Width of the window
height = 32 * square_size  # Height of the window

# Set up the colors
BLACK = (0, 0, 0)

# Create the window
window = pygame.display.set_mode((width, height))
pygame.display.set_caption("Selectable RGB Squares")

# Create the grid
grid = []
# grid[ROW][COLUMN]
for row in range(32):
    grid.append([])
    for col in range(64):
        grid[row].append(BLACK)

# Initialize dragging state variables
is_dragging = False
prev_row, prev_col = None, None

# Main game loop
running = True

# Init color values
r = 0
g = 0
b = 0
while running:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_q:
                # Prompt user for RGB color input
                r = int(input("Enter red value (0-255): "))
                g = int(input("Enter green value (0-255): "))
                b = int(input("Enter blue value (0-255): "))
            if event.key == pygame.K_e:
                # Export color position and information to a file
                f = open("out.txt", "w")
                for i in range(32):
                    for j in range(64):
                        if(grid[i][j] != (0,0,0)):
                            f.write(str(i) + ';' + str(j) + ';' +
                                    str(grid[i][j][0]) + ';' + str(grid[i][j][1]) + ';' + str(grid[i][j][2]) + "\r")
                
                f.close()

            if event.key == pygame.K_p:
                # Read data from in.txt to write to frame to make edits
                f = open("in.txt", "r")

                # Clear entire array to start
                for i in range(32):
                    for j in range(64):
                        grid[i][j] = (0, 0, 0)

                for x in f:
                    split_line = x.split(';')
                    newRow =    int(split_line[0])
                    newCol =    int(split_line[1])
                    newR =      int(split_line[2])
                    newG =      int(split_line[3])
                    newB =      int(split_line[4])
                    grid[newRow][newCol] = (newR, newG, newB)

                f.close()

        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Get the coordinates of the mouse click
            mouse_pos = pygame.mouse.get_pos()
            col = mouse_pos[0] // square_size
            row = mouse_pos[1] // square_size
            
            if event.button == 1:
                # Update the color of the clicked square
                grid[row][col] = (r, g, b)
                # Start dragging
                is_dragging = True
                prev_row, prev_col = row, col

            if event.button == 2:
                print("ROW: " + str(row) + " # COL: " + str(col))

            if event.button == 3:
                # Update the color of the clicked square
                grid[row][col] = (0, 0, 0)
                # Start dragging
                is_dragging = True
                prev_row, prev_col = row, col

        elif event.type == pygame.MOUSEBUTTONUP:
            # Stop dragging
            is_dragging = False

    # Handle dragging
    if is_dragging:
        # Get the coordinates of the mouse position
        mouse_pos = pygame.mouse.get_pos()
        col = mouse_pos[0] // square_size
        row = mouse_pos[1] // square_size
        # Check if the mouse position has changed
        if ((row, col) != (prev_row, prev_col)) and (not row > 31 and not col > 63):
            # Update the color of the current square
            grid[row][col] = grid[prev_row][prev_col]
            # Update the previous square
            prev_row, prev_col = row, col

    # Draw the grid
    for row in range(32):
        for col in range(64):
            pygame.draw.rect(window, grid[row][col], (col * square_size, row * square_size, square_size, square_size))

    # Update the display
    pygame.display.flip()

# Quit the game
pygame.quit()

### NOTES ###
# Try to generate array of arrays that contain the following: [xpos, ypos, r, g, b]
# Then we would only have to generate anything that is ON, so no 0,0,0 pixels