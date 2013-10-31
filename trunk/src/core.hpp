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
/// \file core.hpp
/// \brief Include file for the \b core components of \b Maral.
///
/// \b core.hpp is the include file for the core components of \b Maral.

#ifndef MARAL_CORE_HPP_INCLUDED_
#define MARAL_CORE_HPP_INCLUDED_

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

namespace maral
{

////////////////////////////////////////////////////////////////////////////////
/// \brief Namespace for the core components of \b Maral.
///
/// Namespace for the for the core components of \b Maral.

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
    { for (auto node : children_) delete node; }

    composite_node<Component>* parent_;
    typename Component::hierarchy_type children_;

private:
    virtual const typename Component::hierarchy_type*
        get_children() const
    { return &children_; }

    virtual composite_node<Component>* get_parent() const
    { return parent_; }

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
    { return nullptr; }

    virtual composite_node<Component>* get_parent() const
    { return parent_; }

    virtual composite_node<Component>*
        do_change_parent(composite_node<Component>* new_parent)
    {
        composite_node<Component>* old_parent = parent_;
        parent_ = new_parent;
        return old_parent;
    }

protected:
    composite_node<Component>* parent_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename Component>
class root_node
:   public composite_node<Component>
{
// Implementation
private:
    virtual composite_node<Component>* get_parent() const
    { return nullptr; }

    virtual composite_node<Component>*
        do_change_parent(composite_node<Component>* new_parent)
    {
        BOOST_ASSERT_MSG(false, "root node has no parent!");
        return nullptr;
    }
};

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
    typedef abstract_node* node_type;
    typedef std::list<node_type> hierarchy_type;

////////////////////////////////////////////////////////////////////////////////

    class const_iterator
    :   public boost::iterator_facade
        <
            const_iterator
        ,   node_type const
        ,   boost::forward_traversal_tag
        ,   node_type
        >
    {
    public:
        const_iterator()
        {}

        explicit const_iterator(const node_type node, bool start_at_end = false)
        :   pos_(node->children()->cbegin())
        ,   end_pos_(node->children()->cend())
        { if (start_at_end) pos_ = end_pos_; }

        node_type operator->()
        { return *pos_; }
        const node_type operator->() const
        { return *pos_; }

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

        node_type const dereference() const
        {
            return *pos_;
        }

        hierarchy_type::const_iterator pos_;
        hierarchy_type::const_iterator end_pos_;
        std::list<hierarchy_type::const_iterator> lifo_;
    };

////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    class const_type_iterator
    :   public boost::iterator_facade
        <
            const_type_iterator<T>
        ,   T* const
        ,   boost::forward_traversal_tag
        ,   T*
        >
    {
    public:
        const_type_iterator()
        {}

        explicit const_type_iterator(const node_type node,
                                     bool start_at_end = false)
        :   pos_(node->children()->cbegin())
        ,   end_pos_(node->children()->cend())
        {
            if (start_at_end)
            {
                pos_ = end_pos_;
                return;
            }

            if (pos_ == end_pos_)
                return;

            while (pos_ != end_pos_ && !dynamic_cast<T*>(*pos_))
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
        }

        T* operator->()
        { return reinterpret_cast<T*>(*pos_); }
        const T* operator->() const
        { return reinterpret_cast<T*>(*pos_); }

    private:
        friend class boost::iterator_core_access;

        void increment()
        {
            do
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
            } while (pos_ != end_pos_ && !dynamic_cast<T*>(*pos_));
        }

        bool equal(const_type_iterator const& other) const
        {
            return (this->pos_ == other.pos_);
        }

        T* const dereference() const
        {
            return reinterpret_cast<T*>(*pos_);
        }

        hierarchy_type::const_iterator pos_;
        hierarchy_type::const_iterator end_pos_;
        std::list<hierarchy_type::const_iterator> lifo_;
    };

////////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
    class const_filter_iterator
    :   public boost::iterator_facade
        <
            const_filter_iterator<T, U>
        ,   T* const
        ,   boost::forward_traversal_tag
        ,   T*
        >
    {
    public:
        const_filter_iterator()
        {}

        explicit const_filter_iterator(const node_type node,
                                     U f,
                                     bool start_at_end = false)
        :   pos_(node->children()->cbegin())
        ,   end_pos_(node->children()->cend())
        ,   f_(f)
        {
            if (start_at_end)
            {
                pos_ = end_pos_;
                return;
            }

            if (pos_ == end_pos_)
                return;

            while (pos_ != end_pos_
                && !dynamic_cast<T*>(*pos_)
                && !f_(reinterpret_cast<T*>(*pos_)))
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
        }

        explicit const_filter_iterator(const node_type node,
                                     bool start_at_end = false)
        :   end_pos_(node->children()->cend())
        ,   pos_(end_pos_)
        {}

        T* operator->()
        { return reinterpret_cast<T*>(*pos_); }
        const T* operator->() const
        { return reinterpret_cast<T*>(*pos_); }

    private:
        friend class boost::iterator_core_access;

        void increment()
        {
            do
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
            } while (pos_ != end_pos_
                &&   !dynamic_cast<T*>(*pos_)
                &&   !f_(reinterpret_cast<T*>(*pos_)));
        }

        bool equal(const_filter_iterator const& other) const
        {
            return (this->pos_ == other.pos_);
        }

        T* const dereference() const
        {
            return reinterpret_cast<T*>(*pos_);
        }

        hierarchy_type::const_iterator pos_;
        hierarchy_type::const_iterator end_pos_;
        U f_;
        std::list<hierarchy_type::const_iterator> lifo_;
    };

////////////////////////////////////////////////////////////////////////////////

//    template <typename T> using const_iterator = const_type_iterator<T>;

/// \name Attributes
//@{
    template<typename T>
    const_type_iterator<T> begin() const
    {
        const_type_iterator<T> itr(const_cast<node_type>(this));
        return itr;
    }

    template<typename T>
    const_type_iterator<T> end() const
    {
        const_type_iterator<T> itr(const_cast<node_type>(this), true);
        return itr;
    }

    template<typename T, typename U>
    const_filter_iterator<T, U> begin(U f) const
    {
        const_filter_iterator<T, U> itr(const_cast<node_type>(this), f);
        return itr;
    }

    template<typename T, typename U>
    const_filter_iterator<T, U> end(U f) const
    {
        const_filter_iterator<T, U> itr(const_cast<node_type>(this), f, true);
        return itr;
    }

//    template<typename T>
//    const_node_iterator<T> cbegin() const
//    {
//        const_node_iterator<T> itr(const_cast<node_type>(this));
//        return itr;
//    }
//
//    template<typename T>
//    const_node_iterator<T> cend() const
//    {
//        const_node_iterator<T> itr(const_cast<node_type>(this), true);
//        return itr;
//    }

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

//    const_iterator cbegin() const
//    {
//        const_iterator itr(const_cast<node_type>(this));
//        return itr;
//    }
//
//    const_iterator cend() const
//    {
//        const_iterator itr(const_cast<node_type>(this), true);
//        return itr;
//    }

    int operator[](unsigned idx)
    {
        return idx;
    }


//    size_t size() const
//    {
//        if (children())
//        {
//            for (auto node : *this)
//        }
//    }

    const hierarchy_type* children() const
    { return get_children(); }

    composite_node<abstract_node>* parent() const
    { return parent(); }

    composite_node<abstract_node>*
        change_parent(composite_node<abstract_node>* new_parent)
    { return do_change_parent(new_parent); }

//    bool has_name() const
//    { return check_has_name(); }
//
//    std::string name() const
//    { return get_name(); }
//
//    void set_name(const std::string& name)
//    { do_set_name(name); }
//
//    unsigned ordinal() const
//    { return get_ordinal(); }
//
//    void set_ordinal(unsigned ordinal)
//    { do_set_ordinal(ordinal); }
//@}


// Implementation
    virtual ~abstract_node() {};

private:
    virtual const hierarchy_type* get_children() const = 0;
    virtual composite_node<abstract_node>* get_parent() const = 0;
    virtual composite_node<abstract_node>*
        do_change_parent(composite_node<abstract_node>* new_parent) = 0;
//    virtual bool check_has_name() const
//    { return false; }
//    virtual std::string get_name() const
//    { return "anonymous"; }
//    virtual void do_set_name(const std::string& name)
//    { BOOST_ASSERT_MSG(false, "node has no name!"); }
//    virtual unsigned get_ordinal() const
//    { return 0; }
//    virtual void do_set_ordinal(unsigned ordinal)
//    { BOOST_ASSERT_MSG(false, "node has no ordinal!"); }
};

//template <typename T>
//struct has_ordinal
//{
//    explicit has_ordinal(unsigned ordinal)
//    :   ordinal_(ordinal) {}
//  bool operator()(const T* node) { return (node->ordinal() == ordinal_); }
//  unsigned ordinal_;
//};

////////////////////////////////////////////////////////////////////////////////

//class child
//{
///// \name Construction
////@{
//    child(composite_node<abstract_node>* parent = nullptr)
//    : parent_(parent) {}
////@}
//
//// Implementation
//private:
//    virtual composite_node<abstract_node>* get_parent() const
//    { return parent_; }
//
//    virtual composite_node<abstract_node>*
//        do_change_parent(composite_node<abstract_node>* new_parent)
//    {
//        composite_node<abstract_node>* old_parent = parent_;
//        parent_ = new_parent;
//        return old_parent;
//    }
//
//protected:
//    composite_node<abstract_node>* parent_;
//};

////////////////////////////////////////////////////////////////////////////////

class has_name
{
public:
/// \name Construction
//@{
    has_name(const std::string& name)
    : name_(name) {}
//@}

/// \name Attributes
//@{
    std::string name() const
    { return name_; }

    void set_name(const std::string& name)
    { name_ = name; }
//@}

// Implementation
protected:
    std::string name_;
};

////////////////////////////////////////////////////////////////////////////////

class ordered
{
public:
/// \name Construction
//@{
    ordered(unsigned ordinal)
    : ordinal_(ordinal) {}
//@}

/// \name Attributes
//@{
    unsigned ordinal() const
    { return ordinal_; }

    void set_ordinal(unsigned ordinal)
    { ordinal_ = ordinal; }
//@}

// Implementation
protected:
    unsigned ordinal_;
};

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    T,
    typename... Policies
>
class atom_node
:   public leaf_node<T>
,   public has_name
,   public ordered
,   public Policies...
{
public:
/// \name Construction
//@{
//    atom_node(const std::string& name,
//              unsigned ordinal = 1)
//    :   has_name(name)
//    ,   ordered(ordinal)
//    {}

    atom_node(Policies&&... policies,
              const std::string& name,
              unsigned ordinal = 1)
    :   Policies(policies)...
    ,   has_name(name)
    ,   ordered(ordinal)
    {}
//@}
};

////////////////////////////////////////////////////////////////////////////////

typedef atom_node
<
    abstract_node
>
atom;

////////////////////////////////////////////////////////////////////////////////

template
<
    typename    T,
    typename... Policies
>
class molecule_node
:   public composite_node<T>
,   public has_name
,   public ordered
,   public Policies...
{
public:
/// \name Construction
//@{
    molecule_node(Policies&&... policies,
                  const std::string& name,
                  unsigned ordinal = 1)
    :   Policies(policies)...
    ,   has_name(name)
    ,   ordered(ordinal)
    {}
//@}
};

////////////////////////////////////////////////////////////////////////////////

typedef molecule_node
<
    abstract_node
>
molecule;

inline std::ostream& operator<< (
    std::ostream& out,
    abstract_node::node_type node)
//template <typename T>
//std::ostream& operator<< (
//    std::ostream& out,
//    typename T::node_type node)
{
    BOOST_ASSERT_MSG(node, "null pointer!");
    has_name* named = dynamic_cast<has_name*>(node);
    ordered* numbered = dynamic_cast<ordered*>(node);
    if (named && numbered)
        out << named->name() << ", " << numbered->ordinal();
    else if (named)
        out << named->name();
    else if (numbered)
        out << numbered->ordinal();
    else
        out << node;
    return out;
}

    }    // namespace core
}    // namespace maral

#endif    // MARAL_CORE_HPP_INCLUDED_

