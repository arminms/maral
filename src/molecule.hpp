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

template
<
    template <class> class PolicyType
,   typename ParamType
,   typename ArgType
>
struct triad
{
    typedef PolicyType<ParamType> policy_type;
    typedef ParamType param_type;
    typedef ArgType arg_type;
};

template
<
    class    Model
,   class ...Triad
>
class molecule_base
:   public model::composite_node<Model>
,   public Triad...
{
public:
    virtual void do_print(std::ostream& out) const
    {}
};

template
<
    class   Model
,   template <class> class Pt
,   class   Pp
,   class   Pa
,   template <template <class> class, class, class> class ...Triad
>
class molecule_base<Model, Triad<Pt, Pp, Pa>...>
:   public model::composite_node<Model>
,   public Triad<Pt, Pp, Pa>::policy_type...
{
public:
/// \name Construction
//@{
    molecule_base(
        const typename Triad<Pt, Pp, Pa>::arg_type&... args)
    :   Triad<Pt, Pp, Pa>::policy_type(args)...
    {}
//@}

    virtual void do_print(std::ostream& out) const
    {
        using namespace policies;
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
            << std::setw(4) << this->ordinal() << ". "
            << this->name();
    }
};

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
