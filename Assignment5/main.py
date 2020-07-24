#Jonathan Barnes
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from speck import SpeckCipher
import string
import random
import os
import math
import sys


iv = os.urandom(16)

def Hprime(ptxt):
  temp = SHA256.new()
  c = ptxt.encode()
  temp.update(c)
  temp = temp.hexdigest()[:8] #get first 32 bits or 8 4-bit charactors
  return temp

def dm(key, h):
  #add padding for (128-bit, 256-bit, 512-bit)
  if(len(key) > 64):
    key = key.ljust(128,hex((128-len(key))%0xF)[2:])
  elif(len(key) > 32):
    key = key.ljust(64,hex((64-len(key))%0xF)[2:])
  else:
    key = key.ljust(32,hex((32-len(key))%0xF)[2:])
  
  E = AES.new(key.encode(), AES.MODE_CBC, iv=iv)
  if(type(h) != bytearray):
    h = bytearray(ord(_a) ^ _b for _a, _b in zip(h, E.encrypt(h.encode())))#xor the input h with output of Encryption block
  else:
    h = bytearray(_a ^ _b for _a, _b in zip(h, E.encrypt(h)))#xor the input h with output of Encryption block
  return h

def md(ptxt):
  h = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)])
  for i in range(int(math.ceil(len(ptxt)/32))):
    h = dm(ptxt[i*32:(i + 1) * 32], h)
  #print(h)
  return h

def mac(k, m):
  inp = k + m #concatinate the two strings
  out = md(inp)
  return out

def hack(m1):
  m2 = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)]).encode()
  h = dm(m2, m1) #send in output m1 as input h
  return h

def colisions(ctxt):
  cprime = Hprime(ctxt)
  count = 0
  while(ctxt != cprime):
    ctxt = Hprime(ctxt)
    cprime = Hprime(Hprime(cprime))
    count = count +1
  print(count)

def sponge(m):
  key = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)])#128 bit static key
  P = AES.new(key.encode(), AES.MODE_CBC, iv=iv)
  H = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
  H = list(hex(H)[2:])
  #absorbing phase takes in blocks of size 64bits of message
  for i in range(math.ceil(len(m)/16)):
    #if its on the first go it's a string otherwise its an int
    if(type(H[1]) != int):
      H[:16] = bytearray(ord(_a) ^ ord(_b) for _a, _b in zip(H[:16], m[:(16*(i+1))]))
      temp = list(a for a in H[16:])
      H = list(chr(a) for a in H[:16])  #turn it into a list of chars so I can join them then encode to encrypt
      #print(H)
      H = ''.join(H) + ''.join(temp)
      H = P.encrypt(H.encode())
    else:
      H = list(a for a in H)
      H[:16] = bytearray(_a ^ ord(_b) for _a, _b in zip(H[:16], m[:(16*(i+1))]))
      H = bytes(a for a in H)  #turn it into a list of chars so I can join them then encode to encrypt
      H = P.encrypt(H)
  
  #squeze phase
  H2 = P.encrypt(H)
  H = list(chr(a) for a in H) #get into a list of chars
  H2 = list(chr(a) for a in H2)
  Hash = ''.join(H) + ''.join(H2) #concat the two in one string
  return Hash

def cbcmac(m, key):
  iv = "0000000000000000"
  iv = iv.encode()
  E = AES.new(key.encode(),AES.MODE_CBC, iv=iv)
  if(len(m)%16 != 0):
    m.ljust(math.ceil(len(m)/16)*16, '0') #do padding
  Tag = E.encrypt(m.encode())
  return Tag

def cbcmacforge(m1, m2, T1, T2):
  temp = list(ord(_a) ^ _b for _a, _b in zip(m2, T1)) #xor
  temp = (chr(a) for a in temp)
  temp = ''.join(temp) #turn backt to a string 
  m3 = m1 + temp #concatinate
  print("message 3")
  print(m3)
  print("Tag 3")
  print(T2) #will have the same tag as m2

def UH(k, m):
  p = 2**66 - 5
  temp = 0
  print(len(m))
  for n in range(len(m)):
    temp = temp + ord(m[n]) * (k**n)
 
  return (temp % p)

def CWMAC(k1, k2, N, M):
  B = SpeckCipher(k1, key_size=128, block_size=64)
  P = UH(k2, M)
  ciphertext = B.encrypt(N)
  ciphertext = ciphertext ^ P #xor
  return ciphertext


print("This is The number of itterations till a colision:")
c = Hprime("Hello")
colisions(c)

print("\nthis is the output of M-D hash")
out = md(c)
print (out)

m = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)])
k = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(32)])

print("\nthis is the output of The MAC")
out = mac(k, m)
print(out)

m = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(64)])
print("\nThis is the output of the sponge")
out = sponge(m)
print(out)

m = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(16)])
key = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(16)])
print("\nthis is the output of the cbc mac:")
print("message 1:")
print(m)
print("tag 1")
out = cbcmac(m, key)
print(out)
print("message 2:")
m2 = ''.join([random.choice(string.ascii_letters + string.digits) for n in range(16)])
print(m2)
print("tag 2")
out2 = cbcmac(m2, key)
print(out2)
cbcmacforge(m, m2, out, out2)

key1 = random.getrandbits(128)
key2 = random.getrandbits(64)
m = random.getrandbits(128)
out = CWMAC(key1, key2, m, m2)
print("\nthis is the output of the W-C MAC:")
print(out)