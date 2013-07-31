////////////////////////////////////////////////////////////////////////////////
//
//     Molecular Animation, Graphics and Modeling Application Framework
//                                  MAGMA
//
//        Copyright (C) by Armin Madadkar-Sobhani arminms@gmail.com
//
//                 See the LICENSE file for terms of use
//
//------------------------------------------------------------------------------
// $Id$
//------------------------------------------------------------------------------
/// \file core.hpp
/// \brief Include file for the \b core components of \b Magma.
///
/// \b core.hpp is the include file for the core components of \b Magma.

#ifndef MAGMA_CORE_HPP_INCLUDED_
#define MAGMA_CORE_HPP_INCLUDED_

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <boost/noncopyable.hpp>
//#include <boost/ptr_container/ptr_list.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include "mtl/point.hpp"

namespace magma
{

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the core components of \b Magma.
///
/// Namespace for the for the core components of \b Magma.

    namespace core
    {

template<class T>
struct _Unique_if
{
    typedef std::unique_ptr<T> _Single_object;
};

template<class T>
struct _Unique_if<T[]>
{
    typedef std::unique_ptr<T[]> _Unknown_bound;
};

template<class T, size_t N> struct _Unique_if<T[N]>
{
    typedef void _Known_bound;
};

template<class T, class... Args>
    typename _Unique_if<T>::_Single_object
    make_node(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
    typename _Unique_if<T>::_Unknown_bound
    make_node(size_t n)
    {
        typedef typename std::remove_extent<T>::type U;
        return std::unique_ptr<T>(new U[n]());
    }

template<class T, class... Args>
    typename _Unique_if<T>::_Known_bound
    make_node(Args&&...) = delete;

template <typename T> using node = std::unique_ptr<T>;


    class composite_node;

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstract base class for all molecular hierarchy nodes used in \b
/// Magma.
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
//    typedef boost::ptr_list<abstract_node> hierarchy_type;
//    typedef hierarchy_type::auto_type node_type;
//    typedef std::unique_ptr<abstract_node> node_type;
//    typedef std::list<node_type> hierarchy_type;
    typedef abstract_node* node_type;
    typedef std::list<node_type> hierarchy_type;

    class const_iterator
    :   public boost::iterator_facade
        <
            const_iterator
        ,   node_type const
        ,   boost::forward_traversal_tag
        >
    {
    public:
        const_iterator()
        {}

        explicit const_iterator(const node_type node, bool start_at_end = false)
        :   pos_(node->children()->cbegin())
        ,   end_pos_(node->children()->cend())
        { if (start_at_end) pos_ = end_pos_; }

    private:
        friend class boost::iterator_core_access;

        void increment()
        {
            if ((*pos_)->children())
            {
                lifo_.push_back(end_pos_);
                lifo_.push_back(pos_);
                end_pos_ = (*pos_)->children()->cend();
                pos_ = (*pos_)->children()->cbegin();
            }
            else
                ++pos_;

            while (pos_ == end_pos_ && !lifo_.empty())
            {
                pos_ = lifo_.back();
                lifo_.pop_back();
                ++pos_;
                end_pos_ = lifo_.back();
                lifo_.pop_back();
            }
        }

        bool equal(const_iterator const& other) const
        {
            return (this->pos_ == other.pos_);
        }

        node_type const& dereference() const
        {
            return *pos_;
        }

        hierarchy_type::const_iterator pos_;
        hierarchy_type::const_iterator end_pos_;
        std::list<hierarchy_type::const_iterator> lifo_;
    };

    virtual ~abstract_node() {}

/// \name Attributes
//@{
    const_iterator begin() const
    {
        const_iterator itr(const_cast<node_type>(this));
        return itr;
    }

    const_iterator end() const
    {
        const_iterator itr(const_cast<node_type>(this), true);
        return itr;
    }

    const_iterator cbegin() const
    {
        const_iterator itr(const_cast<node_type>(this));
        return itr;
    }

    const_iterator cend() const
    {
        const_iterator itr(const_cast<node_type>(this), true);
        return itr;
    }

    const hierarchy_type* children() const
    { return get_children(); }

    composite_node* parent() const
    { return parent(); }

    composite_node* change_parent(composite_node* new_parent)
    { return do_change_parent(new_parent); }

    bool has_name() const
    { return check_has_name(); }

    std::string name() const
    { return get_name(); }

    void set_name(const std::string& name)
    { do_set_name(name); }

    unsigned ordinal() const
    { return get_ordinal(); }

    void set_ordinal(unsigned ordinal)
    { do_set_ordinal(ordinal); }
//@}


// Implementation
private:
    virtual const hierarchy_type* get_children() const
    { return nullptr; }
    virtual composite_node* get_parent() const
    { return nullptr; }
    virtual composite_node* do_change_parent(composite_node* new_parent)
    {
        BOOST_ASSERT_MSG(false, "root node has no parent!");
        return nullptr;
    }
    virtual bool check_has_name() const
    { return false; }
    virtual std::string get_name() const
    { return "anonymous"; }
    virtual void do_set_name(const std::string& name)
    { BOOST_ASSERT_MSG(false, "node has no name!"); }
    virtual unsigned get_ordinal() const
    { return 0; }
    virtual void do_set_ordinal(unsigned ordinal)
    { BOOST_ASSERT_MSG(false, "node has no ordinal!"); }
};

inline std::ostream& operator<< (
    std::ostream& out,
    const abstract_node* n)
{
    out << n->name() << ", " << n->ordinal();
    return out;
}

////////////////////////////////////////////////////////////////////////////////

class composite_node
:   public virtual abstract_node
{
public:
    virtual ~composite_node()
    { for (auto node : children_) delete node; }

// Implementation
private:
    virtual const hierarchy_type* get_children() const
    { return &children_; }

protected:
    hierarchy_type children_;
};

////////////////////////////////////////////////////////////////////////////////

class child_node
:   public virtual abstract_node
{
public:
    virtual ~child_node()
    {}

// Implementation
private:
    virtual composite_node* get_parent() const
    { return parent_; }

    virtual composite_node* do_change_parent(composite_node* new_parent)
    {
        composite_node* old_parent = parent_;
        parent_ = new_parent;
        return old_parent;
    }

protected:
    composite_node* parent_;
};

////////////////////////////////////////////////////////////////////////////////

class named_node
:   public virtual abstract_node
{
public:
/// \name Construction
//@{
    named_node(const std::string& name)
    : name_(name) {}
//@}

    virtual ~named_node()
    {}

// Implementation
private:
    virtual bool check_has_name() const
    { return true; }

    virtual std::string get_name() const
    { return name_; }

    virtual void do_set_name(const std::string& name)
    { name_ = name; }

protected:
    std::string name_;
};

////////////////////////////////////////////////////////////////////////////////

class ordinal_node
:   public virtual abstract_node
{
public:
/// \name Construction
//@{
    ordinal_node(unsigned ordinal)
    : ordinal_(ordinal) {}
//@}

    virtual ~ordinal_node()
    {}

// Implementation
private:
    virtual unsigned get_ordinal() const
    { return ordinal_; }

    virtual void do_set_ordinal(unsigned ordinal)
    { ordinal_ = ordinal; }

protected:
    unsigned ordinal_;
};

////////////////////////////////////////////////////////////////////////////////

class atom
:   public child_node
,   public named_node
,   public ordinal_node
{
public:
/// \name Construction
//@{
    atom(const std::string& name, unsigned ordinal = 1)
    : named_node(name)
    , ordinal_node(ordinal) {}
//@}

    virtual ~atom()
    {}
};

////////////////////////////////////////////////////////////////////////////////

class atom2
:   public abstract_node
{
public:
/// \name Construction
//@{
    atom2(const std::string& name)
    { name_ = name; }
//@}

    virtual ~atom2()
    {}

    composite_node* parent_;
    std::string name_;
    unsigned ordinal_;
};

////////////////////////////////////////////////////////////////////////////////

class molecule
:   public composite_node
,   public named_node
,   public ordinal_node
{
public:
/// \name Construction
//@{
    molecule(const std::string& name, unsigned ordinal = 1)
    : named_node(name)
    , ordinal_node(ordinal) {}
//@}

    virtual ~molecule()
    {}

    template<typename T>
    void add(node<T> node)
    {
        do_add(node.get());
        node.release();
    }

// Implementation
private:
    virtual void do_add(node_type node)
    {
        children_.push_back(node);
    }
};

    }    // namespace mtl
}    // namespace magma

#endif    // MAGMA_CORE_HPP_INCLUDED_

