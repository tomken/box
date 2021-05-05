#!/usr/bin/env python
# -*- coding: UTF-8 -*-

dict = {}

def loadFile(path):
    global dict
    f=open(path,'r+')
    for line in f:
        ss = line.split()
        if len(ss) > 1:
            dict[ss[0]] = ss[1]

        if len(ss) > 2:
            print str(ss)

    f.close()

loadFile('english0.txt')
loadFile('english1.txt')
loadFile('english2.txt')
loadFile('english3.txt')

f = open('e.txt', 'w')
for key in dict:
    info = '{:<16}  {}\n'.format(key, dict[key]);
    f.write(info)

f.close()