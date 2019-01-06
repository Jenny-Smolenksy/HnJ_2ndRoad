#include "FileCacheManager.h"

template <class Type>
class ReverseFileCache : FileCacheManager<Type> {


    virtual bool isSolution(Type problem);

    virtual Type getSolution(Type problem);

    virtual void saveSolution(Type problem, Type solution);

};