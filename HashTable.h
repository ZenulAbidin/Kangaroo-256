/*
 * This file is part of the BSGS distribution (https://github.com/JeanLucPons/Kangaroo).
 * Copyright (c) 2020 Jean Luc PONS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HASHTABLEH
#define HASHTABLEH

#include <string>
#include <vector>
#include "SECPK1/Point.h"
#ifdef WIN64
#include <Windows.h>
#endif

#define HASH_SIZE_BIT 18
#define HASH_SIZE (1<<HASH_SIZE_BIT)
#define HASH_MASK (HASH_SIZE-1)

#define ADD_OK        0
#define ADD_DUPLICATE 1
#define ADD_COLLISION 2

union int128_s {

  uint8_t  i8[16];
  uint16_t i16[8];
  uint32_t i32[4];
  uint64_t i64[2];

};

union int256_s {
	uint8_t  i8[32];
	uint16_t i16[16];
	uint32_t i32[8];
	uint64_t i64[4];
};

typedef union int128_s int128_t;
typedef union int256_s int256_t;

#define safe_free(x) if(x) {free(x);x=NULL;}

typedef struct {

  int256_t  x;    // Position of kangaroo (256bit LSB)
  int256_t  d;    // Travelled distance (b255..b0 distance)
  uint32_t  kType; //  Kangaroo type

} ENTRY;

typedef struct {

  uint32_t   nbItem;
  uint32_t   maxItem;
  ENTRY    **items;

} HASH_ENTRY;

class HashTable {

public:

  HashTable();
  int Add(Int *x,Int *d, uint32_t type);
  int Add(int256_t *x,int256_t *d, uint32_t type);
  int Add(uint64_t h,ENTRY *e);
  uint64_t GetNbItem();
  void Reset();
  std::string GetSizeInfo();
  void PrintInfo();
  void SaveTable(FILE *f);
  void SaveTable(FILE* f,uint32_t from,uint32_t to,bool printPoint=true);
  void LoadTable(FILE *f);
  void LoadTable(FILE* f,uint32_t from,uint32_t to);
  void ReAllocate(uint64_t h,uint32_t add);
  void SeekNbItem(FILE* f,bool restorePos = false);
  void SeekNbItem(FILE* f,uint32_t from,uint32_t to);

  HASH_ENTRY    E[HASH_SIZE];
  // Collision info
  Int      kDist;
  uint32_t kType;

  static void Convert(Int *x,Int *d,int256_t *X,int256_t *D);
  static int MergeH(uint32_t h,FILE* f1,FILE* f2,FILE* fd,uint32_t *nbDP,uint32_t* duplicate,
                    Int* d1,uint32_t* k1,Int* d2,uint32_t* k2);
  static void CalcDist(int256_t *d,Int* kDist);
  static void toint256t(Int *a, int256_t *b);
  static void toInt(int256_t *a, Int *b);
private:

  ENTRY *CreateEntry(int256_t *x,int256_t *d, uint32_t kType);
  static int compare(int256_t *i1,int256_t *i2);
  std::string GetStr(int256_t *i);
};

#endif // HASHTABLEH
