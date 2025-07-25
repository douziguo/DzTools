#ifndef DAHENGINSTANCE_H
#define DAHENGINSTANCE_H

namespace SpeedCamera {

class DahengInstance
{
private:
    DahengInstance();
    ~DahengInstance();
public:
    static DahengInstance* getInstance() {
        static DahengInstance instance;
        return &instance;
    }
};

}   // namespace SpeedCamera

#endif // DAHENGINSTANCE_H
