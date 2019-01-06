#include <ostream>
#include <istream>
#include "MyTestClientHandler.h"

template <class Type>
MyTestClientHandler<Type>::MyTestClientHandler(Solver<Type> solverToSet, CacheManager<Type> cacheManagerToSet) {
    this->solver = solverToSet;
    this->cacheManager = cacheManagerToSet;
}

template <class Type>
MyTestClientHandler<Type>::~MyTestClientHandler() {

}

template <class Type>
void MyTestClientHandler<Type>::handleClient(std::istream inputStream, std::ostream outputStream) {

}