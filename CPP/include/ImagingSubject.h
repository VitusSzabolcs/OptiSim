#ifndef IMAGINGSUBJECT_H
#define IMAGINGSUBJECT_H

class ImagingSubject{
    private:
        double x;
        double y;
    protected:
        ImagingSubject(double, double);
    public:
        double getX();
        void setX(double);
        double getY();
        void setY(double);
};

#endif