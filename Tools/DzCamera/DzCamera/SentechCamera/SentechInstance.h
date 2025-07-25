#ifndef SENTECHINSTANCE_H
#define SENTECHINSTANCE_H

#include <StApi_TL.h>   // Transport Layer function (MUST)
//#include <StApi_IP.h>   // Image Processing function (Optional)
//#include <StApi_GUI.h>  // GUI fucntion (Optional)

#define SENTECH     (SentechInstance::getInstance())

namespace SpeedCamera {

class SentechInstance
{
private:
    StApi::IStSystemReleasable *pIStSystem = nullptr;

private:
    SentechInstance();
    ~SentechInstance();

    void releaseIStSystemPtr();
public:
    static SentechInstance* getInstance() {
        static SentechInstance instance;
        return &instance;
    }

    StApi::IStSystemReleasable *getIStSystemPtr();
};

}   // namespace SpeedCamera

#endif // SENTECHINSTANCE_H
