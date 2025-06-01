#ifndef OPTISIMERROR_H
#define OPTISIMERROR_H

#include <exception>
#include <string>

using namespace std;

class OptiSimError : public exception{
    private:
        string message;
    public:
        explicit OptiSimError(const string&);
        const char* what() const noexcept override;
};

#endif