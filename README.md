# Music-Library

Detailed description of Library and how to use it is located at:
https://www.8bitcoding.com/p/music-player-library-for-basic-programs.html


## Files
#### X16.inc
Contains constants for system registers, VERA addresses and Macro for setting VERA

#### Tables.inc
contains lookup tables for calculating frequencies (VERA values) from Note IDs, Delay loops for ADSR phases and configurations of instruments

#### Variables.inc
all the memory locations used as variables. They are mostly replicated for each voice and many contain precalculated values to speed up the IRQ Player performance

#### Play.asm
is the main program. It first parses the input file, performs necessary calculations to prepare variables for play routine. At the end it inserts the IRQ player address so it is called when the Interrupt is triggered.

#### IRQplayer.asm
Is responsible for actually playing sounds and applying the ADSR envelope to them. It is tracking the phase and taking care of timing. It is called before the system IRQ handler and does not interfere with the operation of the system.

To test and to kickstart your own music, check the sample BASIC programs:

#### PLAY.BAS
Plays Twinkle Twinkle in three voices in 4/4 time signature and displays some graphics running in parallel. To use all of the functionality, you have to also download EFFECTS.PRG binary file.

#### HOUSE.BAS
Plays House of the Rising Sun in four voices in 3/4 time signature but is also une one eighth notes so 6 notes per bar.
