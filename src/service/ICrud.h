#ifndef ICRUD_H
#define ICRUD_H


template <typename S, typename T>
class ICrud
{
public:
    virtual bool add(T newObject)=0;
    virtual bool update(S key ,T updatedObject)=0;
    virtual bool remove(T objectToDelete)=0;
};
#endif // ICRUD_H
