# Aircraft-Seat-Allocation-System

This C program can read passengers' data from [WithReserve.dat](/WithReserve.dat/) and [NoReserve.dat](/NoReserve.dat/) and allocate the seats in Airbus A320 accordingly with the goal of achieving smallest moment in both X and Y direction as shown in [[Figure 1](#figure1)] below. The passengers' weight data was extrapolated from their age using mean body weight data for different age groups to calculate the moment of the A320 aircraft. The output of the program will be in .csv file with the title of [PassengerList.csv](/PassengerList.csv/).

Both the .dat files and the code can be modified to suit different needs.

A more detailed description of the tasks is available in [DETAILED_EXPLANATION.md](/DETAILED_EXPLANATION.md/).

## Table of content
| File                                                 | Function                                        |
|:----------------------------------------------------:|:-----------------------------------------------:|
| [DETAILED_EXPLANATION.md](/DETAILED_EXPLANATION.md/) | Detailed description of what the program solves |
| [Figure1.png](/Figure1.png/)                         | Coordinates of seats in A321 aircraft           |
| [Figure2.png](/Figure2.png/)                         | Expected outcome opened in Notepad              |
| [Figure3.png](/Figure3.png/)                         | Expected outcome opened in Excel                |
| [NoReserve.dat](/NoReserve.dat/)                     | Input file for passenger without reservation    |
| [WithReserve.dat](/WithReserve.dat/)                 | Input file for passenger with reservation       |
| [PassengerList.csv](/PassengerList.csv/)             | Sample outcome obtained using project1demo.c    |
| [project1demo.c](/project1demo.c/)                   | Program written in C, to be run in compiler     |

<a name="figure1"></a> ![Figure1](Figure1.png)