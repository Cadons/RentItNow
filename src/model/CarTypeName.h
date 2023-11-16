#ifndef CARTYPENAME_H
#define CARTYPENAME_H

#include <stdexcept>
#include <string>
enum CarTypeName{ECO, MID_CLASS ,DELUXE};
inline std::string CarTypeNameToString(CarTypeName e) throw()
{
    switch (e)
    {
    case CarTypeName::ECO: return "ECO";
    case CarTypeName::MID_CLASS: return "MID-CLASS";
    case CarTypeName::DELUXE: return "DELUXE";
    default: throw std::invalid_argument("Unimplemented type");

    }

}
#endif // CARTYPENAME_H
