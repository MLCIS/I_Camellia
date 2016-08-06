from ctypes import *
from pandas import Series
import matplotlib.pylab as plt

lib = cdll.LoadLibrary("libaptx4869.so")

u_char_p = POINTER(c_ubyte)

aptx4869_init = lib.aptx4869_init
aptx4869_en = lib.aptx4869_en
aptx4869_de = lib.aptx4869_de

aptx4869_file = lib.aptx4869_file
aptx4869_kg = lib.aptx4869_kg


def setAR(func,arg,res):
    func.argtypes = arg
    func.restype = res
    return func


def c_u_array(arr,type=c_char):
    c_array = (len(arr) * type)()
    for i,v in enumerate(arr):
        c_array[i] = v
    return c_array,c_long(len(arr))

aptx4869_en = setAR(aptx4869_en,[POINTER(c_ubyte),c_long,c_double],POINTER(c_ubyte))

aptx4869_de = setAR(aptx4869_de,[POINTER(c_ubyte),c_long,c_double],POINTER(c_ubyte))

def encrypt(plaintext_bytes,key,rank):
    aptx4869_init(key)

    c_p ,c_len = c_u_array(plaintext_bytes,type=c_ubyte)
    c_rank = c_int(rank)
    all_len = rank * len(plaintext_bytes)
    encry =  aptx4869_en(c_p,c_len,c_rank) 
    res = []
    for i in range(all_len):
        try:
            res.append( encry[i])
        except :
            print (i)
    return res



def decrypt(cipher_bytes,key,rank):
    aptx4869_init(key)

    c_p ,c_len = c_u_array(cipher_bytes,type=c_ubyte)
    c_rank = c_int(rank)

    plain =  aptx4869_de(c_p,c_len,c_rank)
    res = []
    l = len(cipher_bytes) /rank
    for i in range(int(l) ):
        res.append( plain[i])

    return res
    

def plot_data(data):
    if isinstance(data,str):
        data = data.strip()
        data = [int(i) for i in data.split()]
    m_data = dict.fromkeys(range(256),0)
    for i in data:
        m_data[i] += 1
    s = Series(m_data)
    s.plot(kind="line")
    return s

def aptx4869(file_name,key,rank,mode="en"):
    c_file_name  = c_char_p(file_name)
    c_key = c_char_p(key)
    c_mode = c_int(0)
    c_rank = c_int(rank)

    aptx4869_init(c_key)

    if (mode == "de"):
        c_mode = c_int(1)

    aptx4869_file(c_file_name,c_key,c_rank,c_mode)
