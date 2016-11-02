#ifndef CPOSITIONHELPER_H
#define CPOSITIONHELPER_H

#include "CGlobalTypedef.h"
#include <cmath>
class CGeometric3dVector
{

public:
    CGeometric3dVector() = default;
    ~CGeometric3dVector() = default;
    CGeometric3dVector(short int x, short int y, short int z) ;
    CGeometric3dVector(std::vector<short int> threeAxisData);
    double lenght() const;

    static double get3DVectorLenght(short int x, short int y, short int z) ;
    static double angleOfVectors(const CGeometric3dVector& first ,const CGeometric3dVector& second) ;
    static double cosToDegree(double angle);


    int operator *(const CGeometric3dVector& vector) const;

    double angleX() const;
    double angleY() const;
    double angleZ() const;

    short int getXAxis() const;
    short int getYAxis() const;
    short int getZAxis() const;

    void setXAxis(short int value) ;
    void setYAxis(short int value) ;
    void setZAxis(short int value) ;

private:
    short int xAxis;
    short int yAxis;
    short int zAxis;

};

inline short int CGeometric3dVector::getXAxis() const { return xAxis;}
inline short int CGeometric3dVector::getYAxis() const { return yAxis;}
inline short int CGeometric3dVector::getZAxis() const { return zAxis;}

inline void CGeometric3dVector::setXAxis(short int value) { xAxis = value ; }
inline void CGeometric3dVector::setYAxis(short int value) { xAxis = value ; }
inline void CGeometric3dVector::setZAxis(short int value) { xAxis = value ; }


#endif // CPOSITIONHELPER_H
