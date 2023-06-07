import numpy as np
import os
from sklearn.ensemble import RandomForestRegressor

filepath = '../data/output.demo'
position = None
lastModified = os.stat(filepath).st_mtime
model = RandomForestRegressor()
x = []
y = []


def handleChange():
    file = open(filepath, 'r')
    if position != None:
        file.seek(position)
    while True:
        line = file.readline()
        if line:
            position = file.tell()
        else:
            break
    file.close()


