
template <class Type>
class CacheManager {

public:

    virtual bool isSolution(Type problem);

    virtual Type getSolution(Type problem);

    virtual void saveSolution(Type problem, Type solution);
};