# Import necessary libraries
import numpy as np
#import pandas as pd
#import matplotlib.pyplot as plt
#import seaborn as sns
from sklearn.datasets import load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, roc_curve, auc

x_train = [
	[0,],
	[1,],
	[2,],
	[3,]
]

y_train = [0,10,20,30]



# Train the Logistic Regression model
model = LinearRegression()
model.fit(x_train, y_train)

X_test = [[0,0]]

# Evaluate the model
y_pred = model.predict(X_test)
print(y_pred)
