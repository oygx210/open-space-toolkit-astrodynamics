////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Astrodynamics
/// @file           bindings/python/src/OpenSpaceToolkitAstrodynamicsPy/Trajectory/Orbit.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitAstrodynamicsPy/Trajectory/Orbit/Pass.cpp>
#include <OpenSpaceToolkitAstrodynamicsPy/Trajectory/Orbit/Models.cpp>
#include <OpenSpaceToolkitAstrodynamicsPy/Trajectory/Orbit/Model.cpp>

#include <OpenSpaceToolkit/Astrodynamics/Trajectory/Orbit/Models/Kepler.hpp>
#include <OpenSpaceToolkit/Astrodynamics/Trajectory/Orbit/Model.hpp>
#include <OpenSpaceToolkit/Astrodynamics/Trajectory/Orbit.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitAstrodynamicsPy_Trajectory_Orbit ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::Integer ;
    using ostk::core::ctnr::Array ;

    using ostk::physics::env::obj::Celestial ;

    using ostk::astro::trajectory::State ;
    using ostk::astro::trajectory::Orbit ;
    using ostk::astro::trajectory::orbit::models::Kepler ;
    using ostk::astro::trajectory::orbit::models::SGP4 ;

    scope in_Orbit = class_<Orbit, bases<ostk::astro::Trajectory>>("Orbit", init<const ostk::astro::trajectory::orbit::Model&, const Shared<const Celestial>&>())

        .def(init<const Array<State>&, const Integer&, const Shared<const Celestial>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Orbit::isDefined)

        .def("accessModel", &Orbit::accessModel, return_value_policy<reference_existing_object>())
        .def("accessKeplerModel", +[] (const Orbit& anOrbit) -> const Kepler& { return anOrbit.accessModel().as<Kepler>() ; }, return_value_policy<reference_existing_object>()) // [TBR]
        .def("accessSGP4Model", +[] (const Orbit& anOrbit) -> const SGP4& { return anOrbit.accessModel().as<SGP4>() ; }, return_value_policy<reference_existing_object>()) // [TBR]

        .def("getRevolutionNumberAt", &Orbit::getRevolutionNumberAt)
        .def("getPassAt", &Orbit::getPassAt)
        .def("getPassWithRevolutionNumber", &Orbit::getPassWithRevolutionNumber)
        .def("getOrbitalFrame", &Orbit::getOrbitalFrame)

        .def("Undefined", &Orbit::Undefined).staticmethod("Undefined")
        .def("Circular", &Orbit::Circular).staticmethod("Circular")
        .def("Equatorial", &Orbit::Equatorial).staticmethod("Equatorial")
        .def("CircularEquatorial", &Orbit::CircularEquatorial).staticmethod("CircularEquatorial")
        .def("SunSynchronous", &Orbit::SunSynchronous).staticmethod("SunSynchronous")

    ;

    enum_<Orbit::FrameType>("FrameType")

        .value("Undefined", Orbit::FrameType::Undefined)
        .value("NED", Orbit::FrameType::NED)
        .value("LVLH", Orbit::FrameType::LVLH)
        .value("LVLHGD", Orbit::FrameType::LVLHGD)
        .value("VVLH", Orbit::FrameType::VVLH)
        .value("QSW", Orbit::FrameType::QSW)
        .value("TNW", Orbit::FrameType::TNW)
        .value("VNC", Orbit::FrameType::VNC)

    ;

    OpenSpaceToolkitAstrodynamicsPy_Trajectory_Orbit_Model() ;
    OpenSpaceToolkitAstrodynamicsPy_Trajectory_Orbit_Models() ;
    OpenSpaceToolkitAstrodynamicsPy_Trajectory_Orbit_Pass() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
