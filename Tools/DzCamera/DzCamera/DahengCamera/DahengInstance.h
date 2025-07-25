#ifndef DAHENGINSTANCE_H
#define DAHENGINSTANCE_H

namespace DzCamera {

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

}   // namespace DzCamera

#endif // DAHENGINSTANCE_H
