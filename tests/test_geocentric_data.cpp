#include <cstdint>
#include <cstdio>

extern "C" {
    extern int64_t _sg2_gc_data_sz();
    extern int64_t _sg2_gc_offset();
    extern int64_t _sg2_gc_delta();
    extern int64_t _sg2_gc_count();
    extern double _sg2_gc_sinL(unsigned l);
    extern double _sg2_gc_cosL(unsigned l);
    extern double _sg2_gc_R(unsigned l);
}


int main(int argc, char const *argv[])
{
    printf("bytes: %ld\n", static_cast<long int>(_sg2_gc_data_sz()));

    printf("offset: %ld, ", static_cast<long int>(_sg2_gc_offset()));
    printf("delta: %ld, ", static_cast<long int>(_sg2_gc_delta()));
    printf("count: %ld\n", static_cast<long int>(_sg2_gc_count()));

    printf("================ geocentric data ================\n");
    for (size_t i = 0; i < _sg2_gc_count(); i++)
    {
        printf("%05lu, ", i);
        printf("sinL: %0.9g, ", _sg2_gc_sinL(i));
        printf("cosL: %0.9g, ", _sg2_gc_cosL(i));
        printf("R: %0.9g\n", _sg2_gc_R(i));
    }

    return 0;
}

