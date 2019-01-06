#include "CacheManager.h"

template <class Type>
class FileCacheManager : public CacheManager<Type> {

    virtual bool isSolution(Type problem);

    virtual Type getSolution(Type problem);

    virtual void saveSolution(Type problem, Type solution);
};