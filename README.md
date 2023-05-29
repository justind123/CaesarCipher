CaesarCipher
============

A [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher) is an encryption technique in which a message in encoded by shifting indvidual letters by a defined number of letters.
If a letter is shifted off the end of the alphabet, it wraps around to the beginning.

Usage: ./caesarCipher.exe -s numToShift inputFile

numToShift: number in which each letter in the original message is shifted by  
inputFile: file name of the text file containing the original message

Output: output.txt  
output.txt will contain the encrypted message in the same format of the original file.