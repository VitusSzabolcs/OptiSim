#ifndef IMAGINGSUBJECT_H
#define IMAGINGSUBJECT_H

class ImagingSubject{
    protected:
        ImagingSubject(double, double);
        double x;
        double y;
    public:
        double getX();
        void setX(double);
        double getY();
        void setY(double);
};

#endif