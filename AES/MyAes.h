#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
using namespace std; 
typedef bitset<8> Mybyte;
typedef bitset<32> word;
#define Nr  10  // AES-128需要 10 轮加密
#define Nk   4  // Nk 表示输入密钥的 word 个数
class MyAes
{
public:
	MyAes(void);
	~MyAes(void);
public:
	void decrypt(Mybyte in[4*4], word w[4*(Nr+1)]);
	void encrypt(Mybyte in[4*4], word w[4*(Nr+1)]);
	void KeyExpansion(Mybyte key[4*Nk], word w[4*(Nr+1)]);
	word SubWord(word& sw);
	word RotWord(word& rw);
	word Word(Mybyte& k1, Mybyte& k2, Mybyte& k3, Mybyte& k4);
	void InvMixColumns(Mybyte mtx[4*4]);
	void InvShiftRows(Mybyte mtx[4*4]);
	void InvSubBytes(Mybyte mtx[4*4]);
	void AddRoundKey(Mybyte mtx[4*4], word k[4]);
	void MixColumns(Mybyte mtx[4*4]);
	void ShiftRows(Mybyte mtx[4*4]);
	void SubBytes(Mybyte mtx[4*4]);


};

