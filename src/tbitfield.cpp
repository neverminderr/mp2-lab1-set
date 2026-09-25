// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    //if (len <= 0) throw len;
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    //if (n < 0 || n >= BitLen) throw n;
    return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    //if (n < 0 || n >= BitLen) throw n;
    TELEM res = 1;
    int idBit = n % (sizeof(TELEM) * 8);
    res <<= idBit;
    return res;

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    //if (n < 0 || n >= BitLen) throw n;
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[id] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    //if (n < 0 || n >= BitLen) throw n;
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    mask = ~mask;
    pMem[id] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    //if (n < 0 || n >= BitLen) throw n;
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    TELEM res = pMem[id];
    res &= mask;
    if (res == 0) {
        return 0;
    }
    return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        if (MemLen != bf.MemLen) {
            MemLen = bf.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.BitLen!=BitLen){
        return 0;
    }
    for (int i = 0; i < MemLen - 1; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) {
        if (bf.GetBit(i) != GetBit(i)) {
            return 0;
        }
    }
    return true;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf) {
        return 0;
    }
    else {
        return 1;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int MaxLen;
    if (BitLen > bf.BitLen) MaxLen = BitLen;
    else MaxLen = bf.BitLen;
    TBitField res(MaxLen);
    for (int i = BitLen; i < MemLen * sizeof(TELEM) * 8; i++) {
        ClrBit(i);
    }
    TBitField copy_bf(bf);
    for (int i = bf.BitLen; i < bf.MemLen * sizeof(TELEM) * 8; i++) {
        copy_bf.ClrBit(i);
    }
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        res.pMem[i] |= copy_bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MaxLen;
    if (BitLen > bf.BitLen) MaxLen = BitLen;
    else MaxLen = bf.BitLen;
    TBitField res(MaxLen);
    for (int i = BitLen; i < MemLen * sizeof(TELEM) * 8; i++) {
        ClrBit(i);
    }
    TBitField copy_bf(bf);
    for (int i = bf.BitLen; i < bf.MemLen * sizeof(TELEM) * 8; i++) {
        copy_bf.ClrBit(i);
    }
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        res.pMem[i] &= copy_bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res = *this;
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char tmp;
    int i = 0;
    istr >> tmp;
    while ((tmp == '0' || tmp == '1') && i < bf.BitLen) {
        if (tmp == '0') {
            bf.ClrBit(i);
        }
        else {
            bf.SetBit(i);
        }
        i++; 
        istr >> tmp;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
