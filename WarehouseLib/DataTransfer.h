#pragma once
#include "Warehouse.h"

//DONE

class DataTransfer {
public:
    static void saveToJson(const Warehouse& warehouse, const std::string& filename);
    static Warehouse loadFromJson(const std::string& filename);
};
