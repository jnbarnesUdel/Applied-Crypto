from simon import SimonCipher
from speck import SpeckCipher
from Crypto.Hash import Poly1305
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto.Hash import CMAC
from numpy.polynomial import polynomial as P
import hmac
import math
import random
import time
import string
import os

def breakup(ptxt, l):
  block = []
  temp = ""
  ptxt = ptxt.ljust(math.ceil(len(ptxt)/l)*l, '0') #do padding
  for i in range(int(len(ptxt)/l)):
    temp = ptxt[(i*l) : ((i+1) *l)] #break it up
    block.append(temp)
    #print(block[i])
  return block
  

    

def EaM(ptxt, key1, key2, nonce):
  counter = 0
  temp2 = 0
  NonceCount = nonce ^ counter
  ctxt = 0
  E = SimonCipher(key1) #encryption block default 128 bit
  mac = Poly1305.new(key=key2.encode(), cipher=AES) #Mac block
  block = breakup(ptxt, 16)
  T = mac.update(ptxt.encode()).hexdigest()
  for i in range(len(block)):
    NonceCount = nonce ^ counter
    counter = counter + 1
    temp = E.encrypt(NonceCount)
    for a in block[i]: #shift temp2 by 1 byte each time and or it with a new byte
      temp2 = (temp2 << 8) | ord(a)
    #print(temp2)
    #print(temp)
    ctxt = (ctxt << 128) | (temp ^ temp2) # accumulate onto the ctxt
  print("CTXT: ")
  print(hex(ctxt))
  print("T: ")
  print(T)


def MtE(ptxt, key1, key2):
  ctxt = 0
  T = hmac.new(key1.encode() ,msg=ptxt.encode(), digestmod=SHA256).digest() #was digest before see if this works
  E = SpeckCipher(key2) #encryption block with hmack output as key
  Prev = random.getrandbits(128) #create random IV for first value
  thing = ptxt.encode() + T
  thing = str(thing)
  block = breakup(thing, 16)
  for i in range(len(block)):
    temp2 = 0
    for j in block[i]:#make string into int
      temp2 = (temp2 <<8) | ord(j)

    block[i] = temp2 ^ Prev
    temp = E.encrypt(block[i])
    #print(temp2)
    #print(temp)
    ctxt = (ctxt << 128) | (temp ^ temp2) # accumulate onto the ctxt
  print("CTXT: ")
  print(hex(ctxt))


def EtM(ptxt, key1, key2, nonce):
  counter = 0
  temp2 = 0
  NonceCount = nonce ^ counter
  ctxt = 0
  E = SimonCipher(key1,key_size=256, block_size=128) 
  mac = CMAC.new(key=key2.encode(), ciphermod=AES) #Mac block
  block = breakup(ptxt, 16)
  
  for i in range(len(block)):
    NonceCount = nonce ^ counter
    counter = counter + 1
    temp = E.encrypt(NonceCount)
    for a in block[i]: #shift temp2 by 1 byte each time and or it with a new byte
      temp2 = (temp2 << 8) | ord(a)
    ctxt = (ctxt << 128) | (temp ^ temp2) # accumulate onto the ctxt
    temp2 = 0
  T = mac.update(str(ctxt).encode()).hexdigest()
  print("CTXT: ")
  print(hex(ctxt))
  print("T: ")
  print(T)

def SimCTR(ptxt, key1, nonce):
  counter = 0
  temp2 = 0
  NonceCount = nonce ^ counter
  ctxt = []
  E = SimonCipher(key1,key_size=128, block_size=64) 
  block = breakup(ptxt, 8) #since block size = 64 only 8 chars
  for i in range(len(block)):
    NonceCount = nonce ^ counter
    counter = counter + 1
    temp = E.encrypt(NonceCount)
    for a in block[i]: #shift temp2 by 1 byte each time and or it with a new byte
      temp2 = (temp2 << 8) | ord(a)
    ctxt.append((temp ^ temp2)) # accumulate onto the ctxt
    temp2 = 0
  
  return(ctxt)


def Mult(k, m): #for doing 
  p = 2**64 + 1
  temp = 0
  for n in range(len(m)):
    temp = temp + ord(m[n]) * (k**n)
 
  return (temp % p)

def Bhash(H, A, C):
  prev = A[0]
  for j in range(len(A) -1): #take care of the A blocks
    prev = Mult(H[0], hex(prev)[2:])
    prev = prev ^ A[j+1]
  for i in range((len(C))): #take care of the cipher blocks
    prev = Mult(H[0], hex(prev)[2:])
    prev = prev ^ C[i]
  leng = (len(A) << 32) | (len(C)) #first 32bits are length of A last 32 are lenght of C
  prev = prev ^ leng
  return prev

def CWmac(k, n, a, c):
  h = SimCTR('0', k, 0)
  temp = Bhash(h, a, c)
  temp = n ^ temp
  out = SimCTR('0', k, temp)
  return out[0]
  #it is better to do it this way because the Bhash output will be smaller than the blockcipher output, and it is less secure to xor the larger bit value with the smaller one, in this way we 

def GCMSIV(ptxt, A, key1, key2, nonce):
  C = SimCTR(ptxt, key1, nonce)
  T = CWmac(key2, nonce, A, C)
  print("CTXT: ")
  print(C)
  print("T: ")
  print(T)
  


ptxt = "This is a plaintext. This plaintext will be encrypted"
k1 = random.getrandbits(128)
k2 = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)])
n = random.getrandbits(128)

print("\nMaE: \nPtxt: ", ptxt)
EaM(ptxt, k1, k2, n)

print("\nMtE: \nPtxt: ", ptxt)
MtE(ptxt, k2, k1)

print("\nEtM: \nPtxt: ", ptxt)
k1 = random.getrandbits(256)
EtM(ptxt, k1, k2, n)

print("\nGCM-SIV: \nPtxt: ", ptxt)
A = [random.getrandbits(64)]
#H = SimCTR(ptxt, 0, 0)
#Bhash(H, A, C)
k2 = random.getrandbits(256)
#CWmac(k2, n, A, C)
GCMSIV(ptxt, A, k1, k2, n)