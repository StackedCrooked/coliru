#pragma once

struct IKontext
{
    virtual int VratVysku() const = 0;
    virtual int VratSirku() const = 0;
    virtual void Zobraz() const = 0;
    virtual void Zapis(const int x, const int y) = 0;
    virtual void Vymaz() = 0;
}