// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_HIERARCHICAL_HPP
#define MARAL_HIERARCHICAL_HPP

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <iterator>
#include <stack>

#include <boost/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

#ifndef MARAL_MAKE_HPP
#include <maral/make.hpp>
#endif // MARAL_MAKE_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b data \b models supported by \b Maral.
///
/// Namespace for collection of concepts and rules used in defining different \b
/// data \b models supported by \b Maral. Data model fundamentally determines in
/// which manner data can be stored, organized and manipulated. Two major data
/// models supported by \b Maral are \b hierarchical and \b relational.

namespace datamodel {

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
    class composite_node
:   public Component
{
public:
    composite_node()
    :   Component()
    ,   parent_(nullptr)
    {}

    template<typename T>
    T* add(entity<T> node)
    {
        if (node)
        {
            T* ptr = node.get();
            do_add(ptr);
            node.release();
            return ptr;
        }
        else
            return nullptr;
    }

    //template<typename T>
    //void add(entity<T> nodes, std::size_t size)
    //{
    //    for (auto i = 0; i < size; ++i)
    //        do_add(&nodes[i]);
    //    nodes.release();
    //}

    template<typename ConstIterator, typename T>
    T* insert(
        ConstIterator pos
    ,   entity<T> node)
    {
        if (node)
        {
            //typename Component::node_type node_ptr = node.release();
            T* ptr =  node.release();
            BOOST_ASSERT_MSG(ptr, "null pointer!");
            ptr->change_parent(this);
#if BOOST_WORKAROUND(__GLIBCXX__, BOOST_TESTED_AT(20130909))
            typename std::list<typename Component::node_type>::iterator
                itr(children_.begin());
            std::advance(itr, std::distance
                <typename Component::hierarchy_type::const_iterator>(itr, pos));
            children_.insert(itr, ptr);
#else
            children_.insert(pos, ptr);
#endif  //__GLIBCXX__
            return ptr;
        }
        else
            return nullptr;
    }

    template<typename T>
    entity<T> remove(T* node)
    {
        std::unique_ptr<T> free_node(nullptr);
        if (do_remove(node))
            free_node.reset(node);
        return free_node;
    }

    template<typename Iterator>
    Iterator erase(Iterator& pos)
    {
        typename Component::node_type node = *pos;
        BOOST_ASSERT_MSG(node, "null pointer!");
        if (this == node->parent()
        &&  node->change_parent(nullptr))
        {
#if BOOST_WORKAROUND(__GLIBCXX__, BOOST_TESTED_AT(20130909))
            // because of libstdc++ bug #57158
            // this is the only workaround and because it's a linear time
            // algorithm, must be replaced as soon as the bug is fixed
            typename std::list<typename Component::node_type>::iterator itr(children_.begin());
            std::advance(itr, std::distance<typename Component::hierarchy_type::const_iterator>(itr, pos));
            pos = children_.erase(itr);
#else
            pos = children_.erase(pos);
#endif  //__GLIBCXX__
        }
        return pos;
    }

// Implementation
    virtual ~composite_node()
    {   do_clear();  }

protected:
    composite_node<Component>* parent_;
    typename Component::hierarchy_type children_;

private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    {   return &children_;  }

    virtual composite_node<Component>* get_parent() const
    {   return parent_; }

    virtual bool
        do_change_parent(composite_node<Component>* new_parent)
    {
            parent_ = new_parent;
            return true;
    }

    virtual void do_add(typename Component::node_type node)
    {
        BOOST_ASSERT_MSG(node, "null pointer!");
        if (node->change_parent(this))
            children_.push_back(node);
    }

    virtual bool do_remove(typename Component::node_type node)
    {
        BOOST_ASSERT_MSG(node, "null pointer!");
        if (this == node->parent()
        &&  node->change_parent(nullptr))
        {
            children_.remove(node);
            return true;
        }
        return false;
    }

    virtual void do_clear()
    {   for (auto node : children_) delete node;    }
};

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
    class leaf_node
:   public Component
{
public:
    leaf_node()
    :   Component()
    ,   parent_(nullptr)
    {}

// Implementation
protected:
    composite_node<Component>* parent_;
    static typename Component::hierarchy_type empty_;

private:
    virtual const typename Component::hierarchy_type*
    get_children() const
    {   return &empty_; }
    //{   return get_empty(); }

    //static const typename Component::hierarchy_type*
    //    get_empty()
    //{
    //    static typename Component::hierarchy_type empty;
    //    return &empty;
    //}

    virtual composite_node<Component>* get_parent() const
    {   return parent_; }

    virtual bool
    do_change_parent(composite_node<Component>* new_parent)
    {
        parent_ = new_parent;
        return true;
    }

    virtual void do_clear()
    {}
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

    virtual bool
        do_change_parent(composite_node<Component>* new_parent)
    {
        BOOST_ASSERT_MSG(false, "root node has no parent!");
        return false;
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
    class const_reverse_iterator;
    template <typename T> class const_type_iterator;
    template <typename T> class const_reverse_type_iterator;

    const_iterator begin() const;
    const_reverse_iterator rbegin() const;
    const_iterator end() const;
    const_reverse_iterator rend() const;
    boost::iterator_range<const_iterator> range() const;
    boost::iterator_range<const_reverse_iterator> reverse_range() const;

    template < typename Type >
        const_type_iterator<Type> begin() const;
    template < typename Type >
        const_reverse_type_iterator<Type> rbegin() const;
    template < typename Type >
        const_type_iterator<Type> end() const;
    template < typename Type >
        const_reverse_type_iterator<Type> rend() const;
    template < typename Type >
        boost::iterator_range< const_type_iterator<Type> >
            range() const;
    template < typename Type >
        boost::iterator_range< const_reverse_type_iterator<Type> >
            reverse_range() const;

/// \name Attributes
//@{
    const hierarchy_type* children() const
    {   return get_children();  }

    composite_node<abstract_node>* parent() const
    {   return get_parent(); }
//@}

/// \name Operations
//@{
    void clear()
    {   do_clear();   }

    bool change_parent(composite_node<abstract_node>* new_parent)
    {   return do_change_parent(new_parent); }

    void print(std::ostream& out) const
    {   return do_print(out);   }

    void scan(std::istream& in)
    {   return do_scan(in);   }

    composite_node<abstract_node>* root() const
    {   return parent() ? parent()->root() : (decltype(parent()))this; }

    bool is_ancestor_of(abstract_node* node) const
    {
        auto p = node->parent();
        while (p)
        {
            if (p == this)
                return true;
            else
                p = p->parent();
        }
        return false;
    }

    composite_node<abstract_node>* common_ancestor(abstract_node* node) const
    {
        auto p = parent();
        while (p)
        {
            if (p->is_ancestor_of(node))
                return p;
            else
                p = p->parent();
        }
        return nullptr;
    }
//@}

// Implementation
    virtual ~abstract_node() {};

private:
    virtual const hierarchy_type* get_children() const = 0;
    virtual composite_node<abstract_node>* get_parent() const = 0;
    virtual bool do_change_parent(
           composite_node<abstract_node>* new_parent) = 0;
    virtual void do_print(std::ostream& out) const = 0;
    virtual void do_scan(std::istream& in) = 0;
    virtual void do_clear() = 0;
};

typedef abstract_node hierarchical;

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the node type to output.
/// \remarks
/// Outputs a string representation of the given node to the
/// given output stream.

std::ostream& operator<< (
    std::ostream& out
,   const hierarchical* node)
{
    BOOST_ASSERT_MSG(node, "null pointer!");
    node->print(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
/// \return \p in after it has been written to.
/// \param in the stream to read from.
/// \param node the node to read.
/// \remarks
/// Reads the node from given input stream.

std::istream& operator>> (
    std::istream& in
,   hierarchical* node)
{
    BOOST_ASSERT_MSG(node, "null pointer!");
    node->scan(in);
    return in;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation

#include <maral/hierarchical.ipp>

}    // namespace datamodel

typedef datamodel::abstract_node hierarchical;

}    // namespace maral

#endif    // MARAL_HIERARCHICAL_HPP
