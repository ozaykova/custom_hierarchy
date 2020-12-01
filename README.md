# custom_hierarchy

Тестировала при помощи создания переменной типа GenCustomHierarchy<some args> и присваивала ей неверное значение - компилятор писал тип перемнной. /
К примеру, GenCustomHierarchy<TypeList<int, int[2], int[3], int[4], int[5], int[6], int[7], int[8], int[9], int[10], int[11], int[12], int[13]>, CountHolder, 1>::rightBase::leftBase c = 8; выдает ошибку no viable conversion from 'int' to 'GenCustomHierarchy<TypeList<int, int [2], int [3], int [4], int [5], int [6], int [7], int [8], int [9], int [10], int [11], int [12], int [13]>, CountHolder, 1>::rightBase::leftBase' (aka 'GenCustomHierarchy<TypeList<int [13]>, CountHolder, 4 + 1>')
