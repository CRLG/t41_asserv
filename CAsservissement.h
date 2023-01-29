#ifndef ASSERVISSEMENT_H
#define ASSERVISSEMENT_H

#include "CAsservissementBase.h"

class CAsservissement : public CAsservissementBase
{
public:
    CAsservissement();

    /*virtual*/ void Init();
    /*virtual*/ void CalculsMouvementsRobots(void);

    /*virtual*/ void CommandeMouvementXY(float x, float y);
    /*virtual*/ void CommandeMouvementDistanceAngle(float distance, float angle);
    /*virtual*/ void CommandeMouvementXY_A(float x, float y);
    /*virtual*/ void CommandeMouvementXY_B(float x, float y);
    /*virtual*/ void CommandeMouvementXY_TETA(float x, float y, float teta);
    /*virtual*/ void CommandeVitesseMouvement(float vit_avance, float vit_angle);


    bool m_automatic_start_logger;

};

#endif // ASSERVISSEMENT_H
