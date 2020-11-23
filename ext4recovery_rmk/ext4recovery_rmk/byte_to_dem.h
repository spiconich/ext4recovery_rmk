#pragma once
#include <iostream>
#include <Windows.h>
unsigned long long eithtBytesToULONGLONG(byte* buffer, byte* bufferHigh)
{
	unsigned long long resultingULONGLONG =
		unsigned long long(
			(unsigned char)(buffer[3]) << 56 |
			(unsigned char)(buffer[2]) << 48 |
			(unsigned char)(buffer[1]) << 40 |
			(unsigned char)(buffer[0]) << 32 |
			(unsigned char)(bufferHigh[3]) << 24 |
			(unsigned char)(bufferHigh[2]) << 16 |
			(unsigned char)(bufferHigh[1]) << 8 |
			(unsigned char)(bufferHigh[0])
			);
	return  resultingULONGLONG;
}
ULONGLONG sixBytesToIntx(byte* buffer)
{
	ULONGLONG resultingInt = ULONGLONG(
		(unsigned char)(buffer[5]) << 40 |
		(unsigned char)(buffer[4]) << 32 |
		(unsigned char)(buffer[3]) << 24 |
		(unsigned char)(buffer[2]) << 16 |
		(unsigned char)(buffer[1]) << 8 |
		(unsigned char)(buffer[0]));
	return resultingInt;
}
unsigned int foursBytesToIntx(byte* buffer)
{
	unsigned int resultingInt = unsigned int((unsigned char)(buffer[3]) << 24 |
		(unsigned char)(buffer[2]) << 16 |
		(unsigned char)(buffer[1]) << 8 |
		(unsigned char)(buffer[0]));
	return resultingInt;
}