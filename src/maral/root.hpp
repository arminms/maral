// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_ROOT_HPP
#define MARAL_ROOT_HPP

#include <boost/any.hpp>

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class  root_node
:   public Policies...
{};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename ...Policies
>
    class root_node
    <
        data_model::hierarchical
    ,   Policies...
    >
:   public data_model::root_node<data_model::hierarchical>
,   public Policies...
{
public:
    typedef root_node<data_model::hierarchical, Policies...> self_type;
    //typedef std::remove_reference<decltype(*this)>::type self_type;

/// \name Construction
//@{
    root_node()
    {   set_name(boost::any("ROOT"), has_policy_named<self_type>()); }

    root_node(const boost::any& name)
    {   set_name(name, has_policy_named<self_type>());   }
//@}

//public:
//    virtual ~root_node<data_model::hierarchical, Policies...>()
//    {   clear_coords(has_policy_coordinates<root_node<data_model::hierarchical, Policies...>>());   }
//
//private:
//    void clear_coords(std::true_type)   {   clear_frames();    }
//    void clear_coords(std::false_type)  {}

    virtual void do_print(std::ostream& out) const
    {   format_traits<root_node>::type::print_root(out, this);  }

    virtual void do_scan(std::istream& in)
    {   format_traits<root_node>::type::scan_root(in, this);  }

private:
    void set_name(const boost::any& name, std::true_type)
    {
        if (boost::any_cast<const char *>(&name))
            this->name(boost::any_cast<const char *>(name));
        else
            this->name(boost::any_cast<std::string>(name));
    }
    void set_name(const boost::any& name, std::false_type)
    {}
};

////////////////////////////////////////////////////////////////////////////////

//template
//<
//    typename StringType
//,   typename ...Policies
//>
//    class root_node
//    <
//        data_model::hierarchical
//    ,   policy::named<StringType>
//    ,   Policies...
//    >
//:   public data_model::root_node<data_model::hierarchical>
//,   public policy::named<StringType>
//,   public Policies...
//{
//public:
///// \name Construction
////@{
//    root_node(
//        const StringType& name = "ROOT")
//    :   policy::named<StringType>(name)
//    {}
////@}
//
//private:
//    virtual void do_print(std::ostream& out) const
//    {   format_traits<root_node>::type::print_root(out, this);  }
//
//    virtual void do_scan(std::istream& in)
//    {   format_traits<root_node>::type::scan_root(in, this);  }
//};

}    // namespace maral

#endif    // MARAL_ROOT_HPP
