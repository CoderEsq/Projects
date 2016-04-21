#!/usr/bin/env python

#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 10/19/2015
#   Last Modification Date:       10/19/2015
#   Filename:                     mypython.py
#
#   Overview:   This program creates 3 files and writes 10 lowercase letters to those
#				files. It then prints the contents of those files to the screen and 
#				creates two random digits between 1 and 42 and prints the product to
#				the screen.
#			
#   Input:  There is no input.
#
#   Output: The output of the program will be a display of the contents within each of
#			the created files as well as the random numbers generated and their product.
#
#***************************************************************************************/

import string
import random

#Generates random seed
random.seed()

#Creates 3 files in read+write mode
file1 = open('file1', 'w+')
file2 = open('file2', 'w+')
file3 = open('file3', 'w+')

#Creates random 10 character strings of lowercase letters
random1 = ''.join([random.choice(string.ascii_lowercase) for n in range(10)])
random2 = ''.join([random.choice(string.ascii_lowercase) for n in range(10)])
random3 = ''.join([random.choice(string.ascii_lowercase) for n in range(10)])

#Writes strings to files
file1.write(random1)
file2.write(random2)
file3.write(random3)

#Prints strings to screen
print("\n")
print "Contents of file1: %s" % random1 
print "Contents of file2: %s" % random2 
print "Contents of file3: %s" % random3 

#Closes files
file1.close()
file2.close()
file3.close()

#Generates random integers between 1 and 42
random4 = random.randint(1, 42)
random5 = random.randint(1, 42)

product = random4 * random5

print "Random integer #1 is: %d" % random4
print "Random integer #2 is: %d" % random5
print "The product of #1 and #2 is: %d" % product
print("\n")