#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define __USE_XOPEN
#include <math.h>

int main(){
    const float x_init = 0.22;
    const float x_frequency = 0.15;
    const float x_amplitude = 3;
    const float y_init = 0.44;
    const float y_frequency = 0.2;
    const float y_amplitude = 2;
    const float angular_error = 0.001;
    const float amplitude_error = 0.001;
    FILE *file_ptr = fopen("data/raw_output.demo", "w");
    srand((unsigned int)time(NULL));
    float t = 0;
    for (short i = 0; i < 1000; i++) {
        t += (float)rand()/(float)RAND_MAX;
        float x = sin(t * x_frequency + x_init) * x_amplitude;
        float y = sin(t * y_frequency + y_init) * y_amplitude;
        float amplitude = sqrt(x * x + y * y) + amplitude_error * (float)rand() / (float)RAND_MAX;
        float direction;
        if (x == 0) { //atan2 doesn't support x values of 0
            direction = (float)(y < 0) * M_PI / 2 + angular_error * (float)rand() / (float)RAND_MAX;
        } else {
            direction = atan2(y, x) + angular_error * (float)rand() / (float)RAND_MAX;
        };
        fprintf(file_ptr, "%s", "\ntime\n");
        fprintf(file_ptr, "%4f", t);
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