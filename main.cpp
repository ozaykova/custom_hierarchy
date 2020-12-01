#include <iostream>
#include <typeinfo>


using namespace std;


struct Nulltype{
    using Head = Nulltype;
    using Tail = Nulltype;
};

template <typename ...a>
struct TypeList {
    using Head = Nulltype;
    using Tail = Nulltype;
};

template <typename H, typename ...T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyList;

template <typename H>
struct TypeList<H> {
    using Head = H;
    using Tail = EmptyList;
};

template <typename T>
struct Holder {
    T _obj;
    size_t sz = sizeof(T);
};

template <typename T, class Base, int count>
struct CountHolder : public Base {
    T _obj;
    size_t sz = sizeof(T);
};

template <class TList, template <class T, class Base, int c> class Unit, int count>
struct GenCustomHierarchy{};

template <class ...TList, template <class T, class Base, int c> class Unit, int count>
struct GenCustomHierarchy<TypeList<TList...>, Unit, count>
        : Unit<typename TypeList<TList...>::Head, Holder<typename TypeList<TList...>::Tail::Tail::Tail::Head>, count>
                , Unit<typename TypeList<TList...>::Tail::Head, Holder<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Head>, count + 1>
                , Unit<typename TypeList<TList...>::Tail::Tail::Head, Holder<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Tail::Head>, count + 2>
                , GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail, Unit, count + 1>
                , GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Tail::Tail, Unit, count * 2 + 1>
                , GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail, Unit, count * 3 + 1>{
    using leftBase = GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail, Unit, count + 1>;
    using middleBase = GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Tail::Tail, Unit, count * 2 + 1>;
    using rightBase = GenCustomHierarchy<typename TypeList<TList...>::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail, Unit, count * 3 + 1>;
};

template <class TList, template <class T, class Base, int c> class Unit, int count>
struct GenCustomHierarchy<TypeList<TList>, Unit, count>{
    using leftBase = Nulltype;
    using middleBase = Nulltype;
    using rightBase = Nulltype;
};

int main() {
    // simple test
    GenCustomHierarchy<TypeList<int, double>, CountHolder, 1> gch;

    // GenCustomHierarchy<TypeList<int [10], int [11], int [12]>, CountHolder, 3 + 1> as expected
    GenCustomHierarchy<TypeList<int, int[2], int[3], int[4], int[5], int[6], int[7], int[8], int[9], int[10], int[11], int[12]>, CountHolder, 1>::middleBase::leftBase a;

    // GenCustomHierarchy<TypeList<int [7], int [8]>, CountHolder, 2 + 1> as expected
    GenCustomHierarchy<TypeList<int, int[2], int[3], int[4], int[5], int[6], int[7], int[8]>, CountHolder, 1>::leftBase::leftBase b;

    // GenCustomHierarchy<TypeList<int [13]>, CountHolder, 4 + 1> as expected
    GenCustomHierarchy<TypeList<int, int[2], int[3], int[4], int[5], int[6], int[7], int[8], int[9], int[10], int[11], int[12], int[13]>, CountHolder, 1>::rightBase::leftBase c;

    return 0;
}