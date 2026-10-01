# Pokéball Arduino Simulator

A Pokéball catching-sequence simulator built with Arduino, inspired by Pokémon.

I wanted to combine something I loved—Pokémon—with something I am learning as an engineer: building interactive embedded systems.

## Description

This project simulates the basic logic of a Pokéball catching sequence.

The simulator contains **5 different Pokémon**, each with different:

- Spawn rates
- Catch rates
- Rarity-based result animations

The main challenge of the project was integrating the **spawn-rate system and catch-rate system** into a single catching sequence.

## Features

- OLED-based catching animation using bitmaps
- 5 different Pokémon that can be obtained
- Different Pokémon rarities
- Individual spawn rates for Pokémon
- Individual catch rates
- Catching sequence with multiple states
- Different result sprites depending on the Pokémon obtained
- Button-controlled interaction
- State-based program flow

## Hardware

- Arduino Uno R3 × 1
- SH1106G OLED display × 1
- Push button × 1
- Jumper wires

## How It Works

The simulator uses different states to control the Pokéball sequence.

### 1. Selection State

The Pokéball starts in the selection state.

A visible indicator is shown on the OLED during this stage.

Pressing the button moves the simulator to the next state.

### 2. Ready to Throw State

The Pokéball enters the ready-to-throw state.

Pressing the button again starts the catching sequence.

### 3. Catching Sequence

The Pokéball performs the catching animation.

During this process, the simulator determines which Pokémon is selected based on its **spawn rate** and then determines whether the Pokémon is successfully caught using its **catch rate**.

### 4. Result State

The final result is displayed on the OLED.

Different Pokémon and outcomes have different result sprites.

## The Main Challenge

The hardest part of this project was integrating the **spawn rate and catch rate**.

These two systems serve different purposes:

- **Spawn rate:** Determines which Pokémon appears.
- **Catch rate:** Determines whether the selected Pokémon is successfully caught.

Getting these systems to work together correctly required thinking about the probability logic and how the different states of the Pokéball sequence should interact.

## Completed Improvements

The project has already gone through several improvements:

- Improved the catching animations
- Refactored parts of the code
- Added OLED-based visual interaction
- Improved the overall state-based flow

## Future Improvements

Possible future additions:

- Add a buzzer for a more immersive catching experience
- Add a movable platform to simulate the Pokéball shaking
- Design and 3D-print a physical Pokéball shell
- Further improve the catching animations
- Continue refactoring and improving the code structure

## Why I Built This

I have always liked Pokémon, and I am also interested in engineering and embedded systems.

This project was an experiment in combining the two: taking something familiar from a game and trying to recreate its logic as a physical interactive system.

## Project Status

**Working — Updated Version**