#include "CGeometric3dVector.h"



CGeometric3dVector::
CGeometric3dVector(std::vector<short int> threeAxisData)
{
    if (3 == threeAxisData.size())
    {
        xAxis = threeAxisData[0];
        yAxis = threeAxisData[1];
        zAxis = threeAxisData[2];
    }
}

CGeometric3dVector::
CGeometric3dVector(short int x, short int y, short int z)
    : xAxis(x)
    , yAxis(y)
    , zAxis(z)
{

}

double CGeometric3dVector::
lenght() const
{
    return sqrt(pow(xAxis,2)+pow(yAxis,2)+pow(zAxis,2));
}

double CGeometric3dVector::
get3DVectorLenght(short int x, short int y, short int z)
{
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

double CGeometric3dVector::
cosToDegree(double angle)
{
    return acos( angle ) * 180 / 3.1416 ;
}


double CGeometric3dVector::
angleX() const
{
    CGeometric3dVector vectorAreaProjection(abs( xAxis), 0 , 0);
    return  angleOfVectors(*this, vectorAreaProjection);
}

double CGeometric3dVector::
angleY() const
{
    CGeometric3dVector vectorAreaProjection(0, abs( yAxis) , 0);
    return  angleOfVectors(*this, vectorAreaProjection);
}


double CGeometric3dVector::
angleZ() const
{
    CGeometric3dVector vectorAreaProjection(0, 0 ,abs( zAxis));
    return  angleOfVectors( vectorAreaProjection, *this);
}


double CGeometric3dVector::
angleOfVectors(const CGeometric3dVector& first ,const CGeometric3dVector& second)
{
    double angle = 0;
    if (first.lenght() && second.lenght())
    {
        angle = first * second / (first.lenght() * second.lenght());
    }
    return angle;
}


int CGeometric3dVector::
operator *(const CGeometric3dVector& vector) const
{
    //std::cout<< " \n"<<xAxis<<" * " << vector.getXAxis() <<" + " <<  yAxis <<" * " <<  vector.getYAxis() <<" + " <<  zAxis<< " * " <<  vector.getZAxis()<<"\n" ;
    return xAxis * vector.getXAxis() + yAxis * vector.getYAxis() + zAxis* vector.getZAxis();
}

CGeometric3dVector& CGeometric3dVector::
operator+=( const CGeometric3dVector& right)

{
    xAxis += right.getXAxis();
    yAxis += right.getYAxis();
    zAxis += right.getZAxis();
    return *this;
}
