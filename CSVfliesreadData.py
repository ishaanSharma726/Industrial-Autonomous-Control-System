# -*- coding: utf-8 -*-
"""
Created on Wed Jul 22 12:46:33 2020

@author: Ishaan
"""

import glob
import pandas as pd
import numpy as np
import emailAlerts as email

humidityThreshold = 65
temperatureThreshold = 29.5

                                                                                                                   
path = r'C:\Users\Ishaan\OneDrive\Desktop\ishaan 4th sem\Capstone project\Arduino code for initial software creation\arduino test csv files'
file = r'\*.csv'

testPath = r'C:\Users\Ishaan\OneDrive\Desktop\ishaan 4th sem\Capstone project\Arduino code for initial software creation\python test csv files'
testFilePath = r'\test_date.csv'

allfiles = glob.glob(path + file)
testDataFiles = pd.read_csv(testPath + testFilePath)

testDates = testDataFiles['Date'].values
# print("testdate"+str(testDates))
testdateLength = len(testDates)

filedate = [None]*(len(allfiles))

print("length of filedate = "+str(len(filedate)))
print("length of testDates = "+str(testdateLength))

#print(testDataFiles)
countnull = 0


arrayLen = 0
arrayLen2 = 0
count = 0
counter = 0

for i in range(0,len(allfiles)):
    datafile = pd.read_csv(allfiles[i])

    humidity = datafile['humidity'].values
    temperature = datafile['temp'].values
    
    countnull2 = 0
    H_len = 0
    T_len = 0
    for H in humidity:
        H_len += 1
    # print("H_len = "+str(H_len))
    for T in temperature:
        T_len += 1
    # print("T_len = "+str(T_len))
    filedate[i] = (allfiles[i][allfiles[i].find('-')+2:-18])
    
    for j in range(0,testdateLength):
        if(filedate[i] == testDates[j]):
            countnull =1
            break
        else:
            countnull = 0
            
    if(countnull == 0):
        print("filedate = "+str(filedate[i]))
        for lun in range(0,H_len):
            if(humidity[lun] > humidityThreshold):
                count = count + 1
            else:
                arrayLen += 1
        for len in range(T_len):
            if(temperature[len] > temperatureThreshold):
                counter = counter + 1
            else:
                 arrayLen2 += 1            
        print("count = " +str(count))
        print(" counter = " +str(counter))
        print("sending e-mail")
        email.main(filedate[i],count,counter)
        print("e-mail sent")
        countnull2 = 1
    else:
        countnull2 = 0
           
# print("filedate = "+str(filedate))
if(countnull2 == 0):
    print("No New e-mails")

fileName = 'test_Date'
dict = {'Date': filedate}

df = pd.DataFrame(dict)
df.to_csv(testPath + r'\{0}.csv'.format(fileName), index = False)