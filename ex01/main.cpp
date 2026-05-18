#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data data;
	data.id = 0;
	data.name = "Ior Bock";
	data.ufology_grade = 42000.0;

	std::cout << "Original data address: " << &data << std::endl;
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized address (uintptr_t): " << raw << std::endl;
	Data* deserialized_ptr = Serializer::deserialize(raw);
	std::cout << "Deserialized address: " << deserialized_ptr << std::endl;
	std::cout << "\nVerifying data integrity: " << std::endl;
	std::cout << "ID: " << deserialized_ptr->id << std::endl;
	std::cout << "Name: " << deserialized_ptr->name << std::endl;
	std::cout << "Ufology Grade: " << deserialized_ptr->ufology_grade << std::endl;
	return 0;
}