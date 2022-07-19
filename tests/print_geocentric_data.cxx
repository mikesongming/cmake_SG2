#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

int main(int argc, char const *argv[])
{
    int64_t offset, delta, count;
    ifstream gc_data;
    gc_data.open("geocentric.data", ios::binary | ios::in);
    gc_data.read(reinterpret_cast<char *>(&offset), 8);
    gc_data.read(reinterpret_cast<char *>(&delta), 8);
    gc_data.read(reinterpret_cast<char *>(&count), 8);

    cout << offset << ", " << delta << ", " << count << endl;
    cout << "======= sinL, cosL, R ======" << endl;

    for (size_t i = 0; i < count; i++)
    {
        double sinL, cosL, R;
        gc_data.read(reinterpret_cast<char *>(&sinL), 8);
        gc_data.read(reinterpret_cast<char *>(&cosL), 8);
        gc_data.read(reinterpret_cast<char *>(&R), 8);

        cout << sinL << ", " << cosL << ", " << R << endl;
    }

    return 0;
}

