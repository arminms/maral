////////////////////////////////////////////////////////////////////////////////
//
//                                  MARAL
//            (Molecular Architectural Record & Assembly Library)
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file units.hpp
/// \brief Include file for dealing with all quantities that have units.
///
/// \b units.hpp is the include file that defines all quantities that have
/// units.

#ifndef MARAL_UNITS_HPP
#define MARAL_UNITS_HPP

#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/angle/gradians.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/base_units/metric/angstrom.hpp> 
#include <boost/units/systems/si/io.hpp>

namespace boost { namespace units 
{ 
    typedef metric::angstrom_base_unit::unit_type angstrom_unit; 
    BOOST_UNITS_STATIC_CONSTANT(angstrom, angstrom_unit); 
    BOOST_UNITS_STATIC_CONSTANT(angstroms, angstrom_unit); 

    typedef scaled_base_unit<si::meter_base_unit, 
            scale<10, static_rational<-9> > > nanometer_base_unit; 
    typedef nanometer_base_unit::unit_type nanometer_unit; 
    BOOST_UNITS_STATIC_CONSTANT(nanometer, nanometer_unit); 
    BOOST_UNITS_STATIC_CONSTANT(nanometers, nanometer_unit); 

}}  // namespace boost::units 

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for units, quantities and unit system support.
///
/// Namespace for supporting units, quantities, unit system and dimensional
/// analysis. It is based on Boost.Units. Some terminology from Boost.Units:
///
/// \li \b Unit: A set of base units raised to rational exponents, e.g. m^1,
/// kg^1, m^1/s^2.
/// \li \b Quantity: A quantity represents a concrete amount of a unit. Thus,
/// while the meter is the base unit of length in the SI system, 5.5 meters is a
/// quantity of length in that system.
/// \li \b System: A unit system is a collection of base units representing all
/// the measurable entities of interest for a specific problem.
///
/// Maral uses SI unit system by default.

namespace units {

////////////////////////////////////////////////////////////////////////////////
// Units for Angle

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing angles in
/// radians.
///
/// \param Type Value type of the angle (e.g. int, float, double, ...).
/// \remarks
/// \par
/// A partial specialization of boost::units::quantity for storing angle values
/// in radians.
/// \see radians, to_radians

template <typename Type>
using angle_in_radians =
    boost::units::quantity<boost::units::si::plane_angle, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing angles in
/// degrees.
///
/// \param Type Value type of the angle (e.g. int, float, double, ...).
/// \remarks
/// \par
/// A partial specialization of boost::units::quantity for storing angle values
/// in degrees.
/// \see degrees, to_degrees

template <typename Type>
using angle_in_degrees =
    boost::units::quantity<boost::units::degree::plane_angle, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing angles in
/// gradians.
///
/// \param Type Value type of the angle (e.g. int, float, double, ...).
/// \remarks
/// \par
/// A partial specialization of boost::units::quantity for storing angle values
/// in gradians.
/// \see degrees, to_degrees

template <typename Type>
using angle_in_gradians =
    boost::units::quantity<boost::units::gradian::plane_angle, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \return Created angle in raidans as a boost::units::quantity object.
/// \param rad Angle value in radians.
/// \remarks
/// Type-safe factory method for creating an angle in radians from a value
/// specified.
/// \see to_radians

template <typename Type>
inline
angle_in_radians<Type> radians(Type rad)
{
    return angle_in_radians<Type>(rad * boost::units::si::radians);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Created angle in degrees as a boost::units::quantity object.
/// \param deg Angle value in degrees.
/// \remarks
/// Type-safe factory method for creating an angle in degrees from a value
/// specified.
/// \see to_degrees

template <typename Type>
inline
angle_in_degrees<Type> degrees(Type deg)
{
    return angle_in_degrees<Type>(deg * boost::units::degree::degrees);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Created angle in gradians as a boost::units::quantity object.
/// \param grd Angle value in gradians.
/// \remarks
/// Type-safe factory method for creating an angle in gradians from a value
/// specified.
/// \see to_gradians

template <typename Type>
inline
angle_in_gradians<Type> gradians(Type grd)
{
    return angle_in_degrees<Type>(grd * boost::units::gradian::gradians);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in radians.
/// \param ang Reference to an angle quantity object.
/// \remarks
/// Conversion method for getting angle quantity in radians.
/// \see radians

template <typename Unit, typename Type>
inline
angle_in_radians<Type> to_radians(
    const boost::units::quantity<Unit, Type>& ang)
{
    return static_cast< angle_in_radians<Type> > (ang);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in degrees.
/// \param ang Reference to an angle quantity object.
/// \remarks
/// Conversion method for getting angle quantity in degrees.
/// \see degrees

template <typename Unit, typename Type>
inline
angle_in_degrees<Type> to_degrees(
    const boost::units::quantity<Unit, Type>& ang)
{
    return static_cast< angle_in_degrees<Type> > (ang);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in gradians.
/// \param ang Reference to an angle quantity object.
/// \remarks
/// Conversion method for getting angle quantity in gradians.
/// \see gradians

template <typename Unit, typename Type>
inline
angle_in_gradians<Type> to_gradians(
    const boost::units::quantity<Unit, Type>& ang)
{
    return static_cast< angle_in_gradians<Type> > (ang);
}

////////////////////////////////////////////////////////////////////////////////
// Units for Length

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing length in
/// Angstroms.
///
/// \param Type Value type of the length (e.g. int, float, double, ...).
/// \remarks
/// \par
/// An alias of boost::units::quantity for storing length values in Angstroms.
/// \see angstroms, to_angstroms

template <typename Type>
using length_in_angstroms =
    boost::units::quantity<boost::units::angstrom_unit, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing length in
/// nanometers.
///
/// \param Type Value type of the length (e.g. int, float, double, ...).
/// \remarks
/// \par
/// An alias of boost::units::quantity for storing length values in nanometers.
/// \see nanometers, to_nanometers

template <typename Type>
using length_in_nanometers =
    boost::units::quantity<boost::units::nanometer_unit, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \brief Specialization of boost::units::quantity for storing angles in
/// gradians.
///
/// \param Type Value type of the angle (e.g. int, float, double, ...).
/// \remarks
/// \par
/// A partial specialization of boost::units::quantity for storing angle values
/// in gradians.
/// \see degrees, to_degrees

//template <typename Type>
//using angle_in_gradians =
//    boost::units::quantity<boost::units::gradian::plane_angle, Type>;

////////////////////////////////////////////////////////////////////////////////
/// \return Created length in Angstroms as a boost::units::quantity object.
/// \param ang Length value in Angstroms.
/// \remarks
/// Type-safe factory method for creating a length in Angstroms from a value
/// specified.
/// \see to_angstroms

template <typename Type>
inline
length_in_angstroms<Type> angstroms(Type ang)
{
    return length_in_angstroms<Type>(ang * boost::units::angstroms);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Created length in nanometers as a boost::units::quantity object.
/// \param len Length value in nanometers.
/// \remarks
/// Type-safe factory method for creating a length in nanometers from a value
/// specified.
/// \see to_nanometers

template <typename Type>
inline
length_in_nanometers<Type> nanometers(Type len)
{
    return length_in_nanometers<Type>(len * boost::units::nanometers);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Created angle in gradians as a boost::units::quantity object.
/// \param grd Angle value in gradians.
/// \remarks
/// Type-safe factory method for creating an angle in gradians from a value
/// specified.
/// \see to_gradians

//template <typename Type>
//inline
//angle_in_gradians<Type> gradians(Type grd)
//{
//    return angle_in_degrees<Type>(grd * boost::units::gradian::gradians);
//}

////////////////////////////////////////////////////////////////////////////////
/// \return Length in Angstroms.
/// \param len Reference to a length quantity object.
/// \remarks
/// Conversion method for getting length quantity in Angstroms.
/// \see angstroms

template <typename Unit, typename Type>
inline
length_in_angstroms<Type> to_angstroms(
    const boost::units::quantity<Unit, Type>& len)
{
    return static_cast< length_in_angstroms<Type> > (len);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Length in nanometers.
/// \param len Reference to a length value.
/// \remarks
/// Conversion method for getting a length quantity in nanometers.
/// \see nanometers

template <typename Unit, typename Type>
inline
length_in_nanometers<Type> to_nanometers(
    const boost::units::quantity<Unit, Type>& len)
{
    return static_cast< length_in_nanometers<Type> > (len);
}

////////////////////////////////////////////////////////////////////////////////
/// \return Angle in gradians.
/// \param ang Reference to an angle quantity object.
/// \remarks
/// Conversion method for getting angle quantity in gradians.
/// \see gradians

//template <typename Unit, typename Type>
//inline
//angle_in_gradians<Type> to_gradians(
//    const boost::units::quantity<Unit, Type>& ang)
//{
//    return static_cast< angle_in_gradians<Type> > (ang);
//}

}}    // namespace maral::units

#endif    // MARAL_UNITS_HPP
