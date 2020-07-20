# -*- coding: utf-8 -*-
"""
Created on Thu Apr  9 13:18:03 2020

@author: 
"""

from keras.models import model_from_json
import pickle
from keras.models import load_model
import librosa
import librosa.display
import numpy as np
import sklearn.preprocessing
from sklearn.preprocessing import LabelEncoder
import time
import matplotlib.pyplot as plt
import IPython.display as ipd

path = r'C:\Users\kamal\Downloads\IOT-Robotic-Programming\Robot_ICP2\Documentation\sound\siren_1.wav'
plt.figure(figsize=(12,4))
data,sample_rate = librosa.load(path)
_ = librosa.display.waveplot(data,sr=sample_rate)
ipd.Audio(path)

def extract_feature(file_name):
    try:
        audio_data, sample_rate = librosa.load(file_name, res_type='kaiser_fast')
        mfccs = librosa.feature.mfcc(y=audio_data, sr=sample_rate, n_mfcc=40)
        mfccsscaled = np.mean(mfccs.T, axis=0)

    except Exception as e:
        print("Error encountered while parsing file: ", file_name)
        return None, None

    return np.array([mfccsscaled])

def print_prediction(file_name):
    prediction_feature = extract_feature(file_name)

    predicted_vector = model.predict_classes(prediction_feature)

    predicted_class = le.inverse_transform(predicted_vector)
    print("The predicted class is:", predicted_class[0], '\n')

    predicted_proba_vector = model.predict_proba(prediction_feature)
    predicted_proba = predicted_proba_vector[0]
    for i in range(len(predicted_proba)):
        category = le.inverse_transform(np.array([i]))
        print(category[0], "\t\t : ", format(predicted_proba[i], '.3f'))


model = load_model('model2.h5')
y = pickle.load(open("y.p", "rb"))
le = LabelEncoder()
le.fit(y)

start_time = time.time()
print_prediction(path)
print("--- %s seconds ---" % (time.time() - start_time))