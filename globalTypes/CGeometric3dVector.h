#ifndef CGEOMETRIC3DVECTOR_H
#define CGEOMETRIC3DVECTOR_H

#include "CGlobalTypedef.h"
class CGeometric3dVector
{

public:
    CGeometric3dVector() = default;
    ~CGeometric3dVector() = default;
    CGeometric3dVector(long int x, long int y, long int z) ;
    CGeometric3dVector(std::vector<long int> threeAxisData);
    double lenght() const;

    static double get3DVectorLenght(long int x, long int y, long int z) ;
    static double angleOfVectors(const CGeometric3dVector& first ,const CGeometric3dVector& second) ;
    static double cosToDegree(double angle);


    int operator *(const CGeometric3dVector& vector) const;
    CGeometric3dVector& operator+=(const CGeometric3dVector& right);

    double angleX() const;
    double angleY() const;
    double angleZ() const;

    long int getXAxis() const;
    long int getYAxis() const;
    long int getZAxis() const;

    void setXAxis(long int value) ;
    void setYAxis(long int value) ;
    void setZAxis(long int value) ;

private:
    long int xAxis;
    long int yAxis;
    long int zAxis;

};

inline long int CGeometric3dVector::getXAxis() const { return xAxis;}
inline long int CGeometric3dVector::getYAxis() const { return yAxis;}
inline long int CGeometric3dVector::getZAxis() const { return zAxis;}

inline void CGeometric3dVector::setXAxis(long int value) { xAxis = value ; }
inline void CGeometric3dVector::setYAxis(long int value) { xAxis = value ; }
inline void CGeometric3dVector::setZAxis(long int value) { xAxis = value ; }

#endif // CGEOMETRIC3DVECTOR_H
