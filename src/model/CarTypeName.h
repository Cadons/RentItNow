#ifndef CARTYPENAME_H
#define CARTYPENAME_H

#include <stdexcept>
#include <string>
enum CarTypeName{ECO, MID_CLASS ,DELUXE};
inline std::string CarTypeNameToString(CarTypeName e) throw()
{
    switch (e)
    {
    case CarTypeName::ECO: return "Eco";
    case CarTypeName::MID_CLASS: return "Mid Class";
    case CarTypeName::DELUXE: return "Deluxe";
    default: throw std::invalid_argument("Unimplemented type");

    }

}
#endif // CARTYPENAME_H
