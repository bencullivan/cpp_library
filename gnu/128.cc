using i128 = __int128;
std::istream& operator>>(std::istream& is, i128& i) {
    std::int64_t l;
    is >> l;
    i = l;
    return is;
}
std::ostream& operator<<(std::ostream& os, i128 i) {
    if (i == 0) return os << 0;
    if (i < 0) {
        os << '-';
        i = -i;
    }
    i128 r = 0;
    while (i > 0) {
        r *= 10;
        r += i % 10;
        i /= 10;
    }
    while (r > 0) {
        os << int(r % 10);
        r /= 10;
    }
    return os;
}