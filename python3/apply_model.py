import numpy as np
import os
import sys
import math
from sklearn.ensemble import RandomForestRegressor

filepath = '../data/model_datapoints.csv'

# Using RandomForestRegressors as ml isn't the main point of this project and they're easy to implement

xmodel = RandomForestRegressor()
ymodel = RandomForestRegressor()

# Stores the data as it's read from the datapoints file

times = []
xvalues = []
yvalues = []

# Reads the data from the datapoints file, then trains the models on these datapoints

def train_models():
    global xvalues
    global yvalues
    global times
    if os.path.exists('data/model_datapoints.csv'):
        data = open('data/model_datapoints.csv')
        lines = data.readlines()
        data.close()
        for line in lines[1:]:
            values = line.split(",")
            times.append(values[0])
            direction = float(values[1])
            amplitude = float(values[2])
            xvalues.append(amplitude * math.cos(direction))
            yvalues.append(amplitude * math.sin(direction))
        xvalues = np.array(xvalues)
        yvalues = np.array(yvalues)
        times = np.array(times).reshape(-1, 1)
        xmodel.fit(times, xvalues)
        ymodel.fit(times, yvalues)
    else:
        print("Model training points file not found")
        sys.exit(1)

# The main user interface. Allows the user to enter time values at any time once the model is trained and prints a predicted direction and amplitude at this time

def main():
    train_models()
    print('Model trained. To predict the wind at a future time, enter the time in seconds. To quit, type \'quit\' and enter. To update the model with new data, type \'retrain\' and enter.')
    while True:
        user_input = input()
        if user_input == 'quit':
            sys.exit(0)
        elif user_input == 'retrain':
            train_models()
        else:
            time = float(user_input)
            x_prediction = xmodel.predict(np.array(time).reshape(-1, 1))[0]
            y_prediction = ymodel.predict(np.array(time).reshape(-1, 1))[0]
            direction_prediction = math.atan2(y_prediction, x_prediction)
            amplitude_prediction = math.sqrt(x_prediction ** 2 + y_prediction ** 2)
            # Never really specified what the amplitude is measured in so now it gets generic units
            print('Estimated direction: {0} radians\nEstimated amplitude: {1} units'.format(direction_prediction, amplitude_prediction))            

if __name__ == "__main__":
    main()