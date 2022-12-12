#ifndef ASSERVISSEMENT_H
#define ASSERVISSEMENT_H

#include "CAsservissementBase.h"

class CAsservissement : public CAsservissementBase
{
public:
    CAsservissement();

    void asserv();
    /*virtual*/ void Init();
};

#endif // ASSERVISSEMENT_H
