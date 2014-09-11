// Boost.Maral library (Molecular Architecture Recording & Assembly Library)
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

#include <stack>

#include <boost/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

#ifndef MARAL_NODE_HPP
#include <maral/node.hpp>
#endif // MARAL_NODE_HPP

namespace maral {

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the different \b data \b models supported by \b Maral.
///
/// Namespace for collection of concepts and rules used in defining different \b
/// data \b models supported by \b Maral. Data model fundamentally determines in
/// which manner data can be stored, organized and manipulated. Two major data
/// models supported by \b Maral are \b hierarchical and \b relational.

namespace data_model {

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
    void add(node<T> node)
    {
        do_add(node.get());
        node.release();
    }

    //template<typename T>
    //void add(node<T> nodes, std::size_t size)
    //{
    //    for (auto i = 0; i < size; ++i)
    //        do_add(&nodes[i]);
    //    nodes.release();
    //}

    template<typename ConstIterator, typename T>
    void insert(
        ConstIterator pos
    ,   node<T> node)
    {
        typename Component::node_type node_ptr = node.release();
        BOOST_ASSERT_MSG(node_ptr, "null pointer!");
        node_ptr->change_parent(this);
#if BOOST_WORKAROUND(__GLIBCXX__, BOOST_TESTED_AT(20130909))
        typename std::list<typename Component::node_type>::iterator itr(children_.begin());
        std::advance(itr, std::distance<typename Component::hierarchy_type::const_iterator>(itr, pos));
        children_.insert(itr, node_ptr);
#else
        children_.insert(pos, node_ptr);
#endif  //__GLIBCXX__
    }

    template<typename T>
    node<T> remove(T* node)
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
protected:
    virtual ~composite_node()
    {
        for (auto node : children_) delete node;
    }

    composite_node<Component>* parent_;
    typename Component::hierarchy_type children_;

private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    {
            return &children_;
    }

    virtual composite_node<Component>* get_parent() const
    {
        return parent_;
    }

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
private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    {   return &empty_; }
    //{   return get_empty(); }

    virtual composite_node<Component>* get_parent() const
    {   return parent_; }

    virtual bool
        do_change_parent(composite_node<Component>* new_parent)
    {
        parent_ = new_parent;
        return true;
    }

    //static const typename Component::hierarchy_type*
    //    get_empty()
    //{
    //    static typename Component::hierarchy_type empty;
    //    return &empty;
    //}

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
    template <typename T> class const_type_iterator;

/// \name Attributes
//@{
    const_iterator begin() const;
    const_iterator end() const;
    boost::iterator_range< const_iterator > range() const;

    template < typename Type >
        const_type_iterator<Type> begin() const;
    template < typename Type >
        const_type_iterator<Type> end() const;
    template < typename Type >
        boost::iterator_range< const_type_iterator<Type> > range() const;

//    int operator[](unsigned idx)
//    {
//        return idx;
//    }

    const hierarchy_type* children() const
    {   return get_children();  }

    composite_node<abstract_node>* parent() const
    {   return get_parent(); }

    bool change_parent(composite_node<abstract_node>* new_parent)
    {   return do_change_parent(new_parent); }

    void print(std::ostream& out) const
    {   return do_print(out);   }

    void scan(std::istream& in)
    {   return do_scan(in);   }
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
};

typedef abstract_node hierarchical;

////////////////////////////////////////////////////////////////////////////////
/// \return \p out after it has been written to.
/// \param out the stream to write to.
/// \param p the node type to output.
/// \remarks
/// Outputs a string representation of the given node to the
/// given output stream.

inline std::ostream& operator<< (
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

inline std::istream& operator>> (
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

}    // namespace data_model

typedef data_model::abstract_node hierarchical;

}    // namespace maral

#endif    // MARAL_HIERARCHICAL_HPP
