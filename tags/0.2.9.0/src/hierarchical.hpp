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
/// \file hierarchical.hpp
/// \brief Include file for all objects acting as a \b node in the molecular
/// hierarchy.
///
/// \b hierarchical.hpp is the include file for all objects acting as a \b node in the
/// molecular hierarchy.

#ifndef MARAL_HIERARCHICAL_HPP_INCLUDED_
#define MARAL_HIERARCHICAL_HPP_INCLUDED_

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <stack>

#include <boost/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b data \b models supported by \b Maral.
///
/// Namespace for collection of concepts and rules used in defining different \b
/// data \b models supported by \b Maral. Data model fundamentally determines in
/// which manner data can be stored, organized and manipulated. Two major data
/// models supported by \b Maral are \b hierarchical and \b relational.

namespace model {

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
    class composite_node
:   public Component
{
public:
    template<typename T>
        void add(node<T> node)
    {
        do_add(node.get());
        node.release();
    }

// Implementation
protected:
    virtual ~composite_node()
    {   for (auto node : children_) delete node; }

    composite_node<Component>* parent_;
    typename Component::hierarchy_type children_;

private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    {   return &children_; }

    virtual composite_node<Component>* get_parent() const
    {   return parent_; }

    virtual composite_node<Component>*
        do_change_parent(composite_node<Component>* new_parent)
    {
        composite_node<Component>* old_parent = parent_;
        parent_ = new_parent;
        return old_parent;
    }

    virtual void do_add(typename Component::node_type node)
    {
        children_.push_back(node);
    }
};

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
    class leaf_node
:   public Component
{
// Implementation
private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    {   return &empty_; }

    virtual composite_node<Component>* get_parent() const
    {   return parent_; }

    virtual composite_node<Component>*
        do_change_parent(composite_node<Component>* new_parent)
    {
        composite_node<Component>* old_parent = parent_;
        parent_ = new_parent;
        return old_parent;
    }

protected:
    composite_node<Component>* parent_;
    static typename Component::hierarchy_type empty_;
};

template <typename Component>
    typename Component::hierarchy_type
    leaf_node<Component>::empty_;

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
    class root_node
:   public composite_node<Component>
{
// Implementation
private:
    virtual composite_node<Component>* get_parent() const
    {   return nullptr; }

    virtual composite_node<Component>*
        do_change_parent(composite_node<Component>* new_parent)
    {
        BOOST_ASSERT_MSG(false, "root node has no parent!");
        return nullptr;
    }
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstract base class for all molecular hierarchy nodes used in \b
/// Maral.
///
/// \remarks
/// In \b Design \b Patterns terminology abstract_node acts as a \e Component
/// for \e Composite pattern, i.e. it is abstract base class for all molecular
/// hierarchy nodes.
/// \author Armin Madadkar Sobhani

class abstract_node
:   boost::noncopyable
{
public:
    typedef abstract_node* node_type;
    typedef std::list<node_type> hierarchy_type;

    class const_iterator;
    template <typename T> class const_type_iterator;

/// \name Attributes
//@{
    const_iterator begin() const;
    const_iterator end() const;
    boost::iterator_range< const_iterator > range();

    template < typename Type >
        const_type_iterator<Type> begin() const;
    template < typename Type >
        const_type_iterator<Type> end() const;
    template < typename Type >
        boost::iterator_range< const_type_iterator<Type> > range();

//    int operator[](unsigned idx)
//    {
//        return idx;
//    }

    const hierarchy_type* children() const
    {   return get_children();  }

    composite_node<abstract_node>* parent() const
    {   return parent(); }

    composite_node<abstract_node>*
        change_parent(composite_node<abstract_node>* new_parent)
    {   return do_change_parent(new_parent); }

    void print(std::ostream& out) const
    {   return do_print(out);   }
//@}


// Implementation
    virtual ~abstract_node() {};

private:
    virtual const hierarchy_type* get_children() const = 0;
    virtual composite_node<abstract_node>* get_parent() const = 0;
    virtual composite_node<abstract_node>*
        do_change_parent(composite_node<abstract_node>* new_parent) = 0;
    virtual void do_print(std::ostream& out) const = 0;
};

typedef abstract_node hierarchical;

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include "hierarchical.ipp"

}    // namespace model

typedef model::abstract_node hierarchical;

}    // namespace maral

#endif    // MARAL_HIERARCHICAL_HPP_INCLUDED_

