template <typename T1, typename T2>
class Tuple {
public:
    T1 First;
    T2 Second;

    Tuple(const T1& val1, const T2& val2) : First(val1), Second(val2) {}
};