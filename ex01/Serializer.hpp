
#include <stdint.h> //contains uintptr_t

struct Data; //forward declaration to allow struct usage

class Serializer
{
private:
	Serializer() = delete;
	Serializer(const Serializer &source) = delete;
	Serializer &operator=(const Serializer &source) = delete;
	~Serializer() = delete;

public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

/*
	Notes: 
	1. since the Serializer class only deals with Data pointers, it doesn't need
	to know what's inside them. Therefore we don't need to include Data.hpp -a forward
	declaration of the struct is enough.

	2.uintptr_t is guaranteed by the compiler to be the exact same size as a pointer
	on any given machine

	3. a memory address is just an unsigned integer value, and uintptr_t is the specific data
	type guaranteed to be large enough to safely contain it without data loss

	4. reinterpret_cast doesn't change the bits of the data being cast, it just tells 
	the compiler to "pretend" one data type is another -> super efficient, since it performs
	no operations at runtime ->generally risky, but the only option here
*/