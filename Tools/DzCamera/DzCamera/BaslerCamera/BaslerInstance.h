#ifndef BASLERINSTANCE_H
#define BASLERINSTANCE_H

// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#include <pylon/DeviceInfo.h>

class QImage;

namespace SpeedCamera {

class BaslerInstance
{
public:
    BaslerInstance();
    ~BaslerInstance();

    static void resultToImage(Pylon::CGrabResultPtr pInBuffer, QImage &OutImage);
};

}   // namespace SpeedCamera

#endif // BASLERINSTANCE_H
