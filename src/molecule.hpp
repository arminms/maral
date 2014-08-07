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
/// \file molecule.hpp
/// \brief Include file for \b molecule nodes of different \b models.
///
/// \b molecule.hpp is the include file that defines \b molecule nodes of
/// different \b data \b models (e.g. molecule_h_node, molecule_r_node,
/// molecule_n_node, etc).

#ifndef MARAL_MOLECULE_HPP_INCLUDED_
#define MARAL_MOLECULE_HPP_INCLUDED_

#include <type_traits>

namespace maral {

//template
//<
//    typename    Model,
//    typename    StringType,
//    typename    OrdinalType,
//    typename    FloatType,
//    template    <class> class VectorType,
//    typename... Policies
//>
//class molecule_h_node
//    : public model::composite_node<Model>
//    , public policies::named<StringType>
//    , public Policies...
//{
//public:
//    typedef StringType string_type;
//    typedef VectorType ordinal_type;
//    typedef FloatType float_type;
//    typedef VectorType vector_type;
//
///// \name Construction
////@{
//    molecule_h_node(
//        const StringType& name)
//    :   policies::named<StringType>(name)
//    {}
////@}
//};

template
<
    typename    Model,
    typename... Policies
>
    class molecule_h_node
:   public model::composite_node<Model>
,   public policies::named<std::string>
,   public policies::ordered<unsigned>
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_h_node(
        //Policies&&... policies,
        const std::string& name,
        unsigned ordinal = 1)
    //:   Policies(policies)...
    :   named(name)
    ,   ordered(ordinal)
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        auto parent = model::composite_node<Model>::parent();
        std::string trail = (parent->children()->back() == this)
                          ? "---\\"
                          : "---+";
        while (parent)
        {
            auto prev_parent = parent;
            parent = parent->parent();
            if (parent)
                trail += (parent->children()->back() == prev_parent)
                       ? "    "
                       : "   |";
        }
        boost::reverse(trail);
        out << trail
            << std::setw(4) << ordinal() << ". "
            << name();

        print_position(out,
            std::is_base_of<policies::position<mtl::point3f>,
                molecule_h_node<Model, Policies...> >());
    }

private:
    //template<typename T>
    void print_position(std::ostream& out, std::true_type) const
    {
        out << mtl::horizontal << mtl::delimiters('[', ']') << mtl::separator(' ')
            << ' ' << policies::position<mtl::point3f>::get_center();
    }

    //template<typename T>
    void print_position(std::ostream& out, std::false_type) const
    {
    }
};

}    // namespace maral

#endif    // MARAL_MOLECULE_HPP_INCLUDED_
