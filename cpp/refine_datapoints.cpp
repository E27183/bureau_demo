#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

const char undefined_string_reference[10] = "undefined";

// Returns true if the char array starts with "undefined" as this is how the angle and direction are recorded in the csv if there was no value in the raw data
bool is_undefined(char* token) {
    for (int i = 0; i < 9; i++) {
        if (token[i] != undefined_string_reference[i]) {
            return false;
        };
    };
    return true;
};

int main() {
    // Stores the most recent line read from the input csv
    char buffer[64];
    // Stores the result of fgets to check when the end of file is reached
    char *pointer;
    // Stores the result of strtok to check when there are no more tokens (datapoints) in the line
    char *token;
    const char comma[3] = ",\0";

    FILE *input_file_ptr = fopen("data/output.csv", "r");
    if (input_file_ptr == NULL) {
        printf("Output csv not found\n");
        exit(1);
    };
    FILE *output_file_ptr = fopen("data/model_datapoints.csv", "w");
    fprintf(output_file_ptr, "time,direction,amplitude\n");

    // Stores the most recent recordings of direction and amplitude, as well as the last time they were recorded
    // Times are initiated to be negative and 1 apart to prevent the program trying to form merged datapoints before a value for direction and amplitude is recorded

    float recent_direction_time = -1;
    float recent_direction_value;
    float recent_amplitude_time = -2;
    float recent_amplitude_value;
    float datapoint_time;

    // type_index encodes what the value of a token corresponds to
    // Encoding is 0 = time, 1 = direction, 2 = amplitude

    int type_index;
    bool undefined_event;
    bool immediate_instance_is_undefined;

    // Skip the first line with labels
    fgets(buffer, 64, input_file_ptr);

    do {
        pointer = fgets(buffer, 64, input_file_ptr);
        type_index = 0;
        undefined_event = false;

        if (pointer != NULL) {
            token = strtok(buffer, comma);
            while (token != NULL) {
                immediate_instance_is_undefined = is_undefined(token);
                if (immediate_instance_is_undefined) {
                    undefined_event = true;
                } else {
                    if (type_index == 0) {
                        datapoint_time = atof(token);
                    } else if (type_index == 1) {
                        recent_direction_time = datapoint_time;
                        recent_direction_value = atof(token);
                    } else {
                        recent_amplitude_time = datapoint_time;
                        recent_amplitude_value = atof(token);
                    };
                };
                type_index++;
                token = strtok(NULL, comma);
            };
            // If the data cannot be used as a real datapoint for the model, don't write it to the output file
            if (undefined_event) {
                // If the direction and amplitude are within 0.5s of each other they can be merged and used as a valid datapoint
                if (abs(recent_amplitude_time - recent_direction_time) < 0.5) {
                    fprintf(output_file_ptr, "%f,%f,%f\n", (recent_amplitude_time + recent_direction_time) / 2, recent_direction_value, recent_amplitude_value);
                };
            } else {
                fprintf(output_file_ptr, "%f,%f,%f\n", datapoint_time, recent_direction_value, recent_amplitude_value);
            };
        };
    } while (pointer != NULL);

    fclose(input_file_ptr);
    fclose(output_file_ptr);
    return 0;
};