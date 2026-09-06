template <typename T>
bool esAVLRec(const Abin<T>& A,
              typename Abin<T>::nodo n,
              const T* minimo,
              const T* maximo,
              int& altura)
{
    if (n == Abin<T>::NODO_NULO)
    {
        altura = -1;
        return true;
    }

    T e = A.elemento(n);

    if ((minimo != nullptr && e <= *minimo) ||
        (maximo != nullptr && e >= *maximo))
        return false;

    int alturaIzq, alturaDer;

    if (!esAVLRec(A, A.hijoIzqdo(n),
                  minimo, &e, alturaIzq))
        return false;

    if (!esAVLRec(A, A.hijoDrcho(n),
                  &e, maximo, alturaDer))
        return false;

    altura = 1 + std::max(alturaIzq, alturaDer);

    return std::abs(alturaIzq - alturaDer) <= 1;
}
