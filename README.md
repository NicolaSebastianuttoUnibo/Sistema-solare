# SOLAR SYSTEM SIMULATION

In this project, we create a simulation of the solar system. The initial interactive window allows users to customize parameters for the Sun and planets, including mass, position, velocity, radius, and texture. A second window simulates the evolution of the solar system based on these chosen parameters.

## Implementive Choices

In this paragraph, we explore the implementation of Newton's laws. Specifically, the formula
$$
F = \frac{G \cdot m_1 \cdot m_2}{d^2}
$$
, representing gravitational force, is used. For each iteration of the simulation, all gravitational forces acting on every planet are calculated, summed, and meticulously considered individually. This precise approach ensures accurate modeling of the motion and interactions of each planet within the system. The simulation also checks  potential collisions. When a collision is detected, a certain amount of energy is dissipated in the form of heat and deformation. This approach allows tracking of energy dissipation and verifies energy conservation within the system. During a collision event, it was decided that the two planets involved undergo a completely inelastic collision, merging and moving together as one entity.

To maintain a practical scale, it was chosen that 1 pixel represents 1 million kilometers, ensuring most planetary orbits fit within the interface. Given that distances between planets are orders of magnitude greater than their sizes, users are advised to input radii greater than 1 (even if less than 10^9 meters). Additionally, a time scale of 1 time unit equals to 1 hour was selected, allowing planets to complete their orbits within reasonable timeframes. Masses were scaled to 10^27 kg to prevent numerical underflow or overflow issues during calculations, ensuring results remain within a reasonable range.

## Instructions for Compilation, Libraries, and Running

To access the project repository on GitHub, ensure Git is installed on your system, and then clone the repository with the following command:

```bash
git clone git@github.com:NicolaSebastianuttoUnibo/Sistema-solare.git
```

Next, to download the necessary libraries SFML and MPFR, you can use the following command with sudo apt install:

```bash
sudo apt install libsfml-dev libmpfr-dev
```

After successfully installing the required libraries, you can proceed to compile the program. For debugging, execute the following command:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

For a release build, use this command:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

Once the compilation phase is complete, you can build the program using:

```bash
cmake --build build
```

Finally, to run the program, use:

```bash
./build/main
```

## First window instruction

- You can interact with the buttons with the mouse left click

- You can move the camera with <kbd>WASD</kbd>

- Instruction to change planets' or suns' parameters:

    - Click on 'SELECT BUTTON' (one planet will be surounded by a white side)
    - Press on the planet you want to change parameters (if it is too small, click on 'NEXT BUTTON' unttil you find it and then press <kbd>SPACE</kbd>)
    - The planet you select will have a yellow side and it will appear a new button in the right corner
    - Use the mouse right click to change the parameter
    - Use the mouse left click to change the value
    - Mass, radius and texture: it will open the terminal and you have to insert the value in the console (press <kbd>ENTER</kbd> to set the new value)
    - Position and velocity: you have to change manually with the mouse left click

- Instruction to see animation:

    - Save the configurations with the 'SAVE BUTTON'
    - Click on 'EVOLVE BUTTON' (a new window will appear)

## Shortcuts

- <kbd>M</kbd>: changes the mass
- <kbd>P</kbd>: changes the position
- <kbd>V</kbd>: changes the speed
- <kbd>R</kbd>: changes the radius
- <kbd>T</kbd>: changes the texture
- <kbd>X</kbd>: cancels the planet

## Second window commands

- <kbd>WASD</kbd>: move camera
- <kbd>&uarr;</kbd>: see next planet when following a planet
- <kbd>&darr;</kbd>: see previuos planet when following a planet


- <kbd>SPACE</kbd>: pauses or plays the simulation

- <kbd>P</kbd>: follows a planet

- <kbd>O</kbd>: start creating a planets' set
- <kbd>&uarr;</kbd>: setting another planet (the next planet of the universe)
- <kbd>&darr;</kbd>: setting another  planet (the previous planet of the universe)
- <kbd>&rarr;</kbd>: seeing the next planet of the planets' set
- <kbd>&larr;</kbd>: seeing the previous planet of the planets' set
- <kbd>B</kbd>: remove the planet from the planets' set
- <kbd>ENTER</kbd>: finish creating the planets' set

- <kbd>C</kbd>: follows the planets' set

**Note:** here planet is used as synonym of celestial body

# Credits

Nicola Sebastianutto, Marco Silvi, Lorenzo Statello

September 2023