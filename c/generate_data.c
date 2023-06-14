#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define __USE_XOPEN
#include <math.h>

int main(){

    // Parameters for the generated data. Data is defined as independent sin waves on the x and y axes with user defined amplitudes, frequencies and offsets
    // Data is outputted as a series of 2 line "pairs" where the first line labels what the data is and the second line is a number representing the value
    // Output is given in polar coordinates, the time each angle or direction is recorded is given by the most recently read time value

    const float x_init = 0.22;
    const float x_frequency = 0.15;
    const float x_amplitude = 3;
    const float y_init = 0.44;
    const float y_frequency = 0.2;
    const float y_amplitude = 2;
    const float angular_error = 0.001;
    const float amplitude_error = 0.001;

    // t records the current datapoint time (not real time) at each attempt to record data

    float t = 0;

    FILE *file_ptr = fopen("data/output.demo", "w");
    srand((unsigned int)time(NULL));

    for (short i = 0; i < 1000; i++) {

        t += (float)rand()/(float)RAND_MAX;

        float x = sin(t * x_frequency + x_init) * x_amplitude;
        float y = sin(t * y_frequency + y_init) * y_amplitude;
        float amplitude = sqrt(x * x + y * y) + amplitude_error * (float)rand() / (float)RAND_MAX;
        float direction;

        //atan2 in c doesn't support the edge case of 0, so must manually implement this to avoid errors

        if (x == 0) {
            direction = (float)(y < 0) * M_PI / 2 + angular_error * (float)rand() / (float)RAND_MAX;
        } else {
            direction = atan2(y, x) + angular_error * (float)rand() / (float)RAND_MAX;
        };
        fprintf(file_ptr, "%s", "\ntime\n");
        fprintf(file_ptr, "%4f", t);

        // The direction and amplitude of the wind at each recorded time point has a 50% chance of being recorded

        int to_print_details = rand();
        if (to_print_details > RAND_MAX / 2) {
            fprintf(file_ptr,"%s","\ndirection\n");
            fprintf(file_ptr, "%4f", direction);
        };
        if (to_print_details % 2 == 0) {
            fprintf(file_ptr,"%s","\namplitude\n");
            fprintf(file_ptr, "%4f", amplitude);
        };

    };
    fclose(file_ptr);
};