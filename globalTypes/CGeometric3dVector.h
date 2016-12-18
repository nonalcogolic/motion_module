#ifndef CGEOMETRIC3DVECTOR_H
#define CGEOMETRIC3DVECTOR_H

#include "CGlobalTypedef.h"
class CGeometric3dVector
{

public:
    CGeometric3dVector() = default;
    ~CGeometric3dVector() = default;
    CGeometric3dVector(long long int x, long long int y, long long int z) ;
    CGeometric3dVector(std::vector<long long int> threeAxisData);
    double lenght() const;

    static double get3DVectorLenght(long long int x, long long int y, long long int z) ;
    static double angleOfVectors(const CGeometric3dVector& first ,const CGeometric3dVector& second) ;
    static double cosToDegree(double angle);


    int operator *(const CGeometric3dVector& vector) const;
    CGeometric3dVector& operator+=(const CGeometric3dVector& right);

    double angleX() const;
    double angleY() const;
    double angleZ() const;

    long long int getXAxis() const;
    long long int getYAxis() const;
    long long int getZAxis() const;

    void setXAxis(long long int value) ;
    void setYAxis(long long int value) ;
    void setZAxis(long long int value) ;

private:
    long long int xAxis;
    long long int yAxis;
    long long int zAxis;

};

inline long long int CGeometric3dVector::getXAxis() const { return xAxis;}
inline long long int CGeometric3dVector::getYAxis() const { return yAxis;}
inline long long int CGeometric3dVector::getZAxis() const { return zAxis;}

inline void CGeometric3dVector::setXAxis(long long int value) { xAxis = value ; }
inline void CGeometric3dVector::setYAxis(long long int value) { xAxis = value ; }
inline void CGeometric3dVector::setZAxis(long long int value) { xAxis = value ; }

#endif // CGEOMETRIC3DVECTOR_H
