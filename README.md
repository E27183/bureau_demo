The problem:

In this fictional problem, the wind behaviour on the peak of a mountain is being monitored. Each of the two monitoring device creates a record containing the time of the recording, as well as the direction of the wind, the velocity of the wind, or both at regular but inconsistent intervals. These are written to a file.

There is a model that takes in a set of datapoints containing the time, velocity and direction of the wind and models it as a function. Datapoints must have both a velocity and direction, however combining the recorded velocity from one of the monitoring devices with the direction from the other produces a valid datapoint if the recordings were made within 500ms of each other.

The data from the file must be converted to inputs that the model can accept and then passed to the model. This model should be able to be queried at any time to predict the velocity and direction of the wind at a specified time.

New regulations have been implemented which require all scientific code to use at least 20 lines each of c, c++, python and fortran. This also needs to adhere to these regulations.

To run the solution program:

 - Ensure you have gfortran, gcc and python3 compilers installed on your machine
 - Download or clone the repository and navigate to the root directory of the project
 - Run ```make all```
 - Follow the instructions on the terminal to get your predictions

 Note: This is designed to work on linux and doesn't support other operating systems  
 Also note: This was written for a job interview and while you are free to use it for your own projects, most of it will probably not be useful
