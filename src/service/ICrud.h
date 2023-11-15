#ifndef ICRUD_H
#define ICRUD_H

#endif // ICRUD_H
template <typename T>
class ICrud
{
public:
    virtual bool add(T newObject)=0;
    virtual bool update(T oldObject,T updatedObject)=0;
    virtual bool remove(T objectToDelete)=0;
};
