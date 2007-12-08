#include "TurretCollisionResponse.h"
#include "VitalsHealth.h"
#include "Object.h"
using tlib::Object;
using tlib::OCVitalsHealth;

void TurretCollisionResponse::respond()
{
    OCVitalsHealth *cVitals = (OCVitalsHealth*)getOwner()->getComponent("vitals");
    cVitals->hit( 1 );
}