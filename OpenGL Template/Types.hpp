#pragma once

#include <cstdint>
#include <bitset>

// Entity Type Alias
using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES = 5000;

// Component Type Alias
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

// Signature Type Alias
using Signature = std::bitset<MAX_COMPONENTS>;