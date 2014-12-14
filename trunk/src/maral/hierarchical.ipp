// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

class abstract_node::const_iterator
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
    {   if (start_at_end) pos_ = end_pos_;  }

    node_type operator->()
    { return *pos_; }
    const node_type operator->() const
    { return *pos_; }

    void operator= (const hierarchy_type::const_iterator pos)
    { pos_ = pos; }
    operator hierarchy_type::const_iterator() const
    { return pos_; }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        if ((*pos_)->children()->empty())
            ++pos_;
        else
        {
            lifo_.push(end_pos_);
            lifo_.push(pos_);
            end_pos_ = (*pos_)->children()->cend();
            pos_ = (*pos_)->children()->cbegin();
        }

        while (pos_ == end_pos_ && !lifo_.empty())
        {
            pos_ = lifo_.top();
            lifo_.pop();
            ++pos_;
            end_pos_ = lifo_.top();
            lifo_.pop();
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


    void advance(difference_type n)
    {
        BOOST_ASSERT_MSG(n >= 0, "negative advance not supported!");
        for (auto i = 0; i < n; ++i)
            increment();
    }

    hierarchy_type::const_iterator pos_;
    hierarchy_type::const_iterator end_pos_;
    std::stack<hierarchy_type::const_iterator> lifo_;
};

////////////////////////////////////////////////////////////////////////////////

class abstract_node::const_reverse_iterator
:   public boost::iterator_facade
<
    const_reverse_iterator
,   node_type const
,   boost::forward_traversal_tag
,   node_type
>
{
public:
    const_reverse_iterator()
    {}

    explicit const_reverse_iterator(const node_type node
    ,   bool start_at_end = false)
    :   pos_(node->children()->crbegin())
    ,   end_pos_(node->children()->crend())
    {   if (start_at_end) pos_ = end_pos_;  }

    node_type operator->()
    { return *pos_; }
    const node_type operator->() const
    { return *pos_; }

    void operator= (const hierarchy_type::const_reverse_iterator pos)
    { pos_ = pos; }
    operator hierarchy_type::const_reverse_iterator() const
    { return pos_; }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        if ((*pos_)->children()->empty())
            ++pos_;
        else
        {
            lifo_.push(end_pos_);
            lifo_.push(pos_);
            end_pos_ = (*pos_)->children()->crend();
            pos_ = (*pos_)->children()->crbegin();
        }

        while (pos_ == end_pos_ && !lifo_.empty())
        {
            pos_ = lifo_.top();
            lifo_.pop();
            ++pos_;
            end_pos_ = lifo_.top();
            lifo_.pop();
        }
    }

    bool equal(const_reverse_iterator const& other) const
    {
        return (this->pos_ == other.pos_);
    }

    node_type const dereference() const
    {
        return *pos_;
    }

    void advance(difference_type n)
    {
        BOOST_ASSERT_MSG(n >= 0, "negative advance not supported!");
        for (auto i = 0; i < n; ++i)
            increment();
    }

    hierarchy_type::const_reverse_iterator pos_;
    hierarchy_type::const_reverse_iterator end_pos_;
    std::stack<hierarchy_type::const_reverse_iterator> lifo_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
    class abstract_node::const_type_iterator
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

    explicit const_type_iterator(
        const node_type node,
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
            if ((*pos_)->children()->empty())
                ++pos_;
            else
            {
                lifo_.push(end_pos_);
                lifo_.push(pos_);
                end_pos_ = (*pos_)->children()->cend();
                pos_ = (*pos_)->children()->cbegin();
            }

            while (pos_ == end_pos_ && !lifo_.empty())
            {
                pos_ = lifo_.top();
                lifo_.pop();
                ++pos_;
                end_pos_ = lifo_.top();
                lifo_.pop();
            }
        }
    }

    T* operator->()
    {   return reinterpret_cast<T*>(*pos_);     }
    const T* operator->() const
    {   return reinterpret_cast<T*>(*pos_);     }

    void operator= (const hierarchy_type::const_iterator pos)
    {
        pos_ = pos;
        if (pos_ != end_pos_ && !dynamic_cast<T*>(*pos_))
            increment();
    }
    operator hierarchy_type::const_iterator() const
    { return pos_; }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        do
        {
            if ((*pos_)->children()->empty())
                ++pos_;
            else
            {
                lifo_.push(end_pos_);
                lifo_.push(pos_);
                end_pos_ = (*pos_)->children()->cend();
                pos_ = (*pos_)->children()->cbegin();
            }

            while (pos_ == end_pos_ && !lifo_.empty())
            {
                pos_ = lifo_.top();
                lifo_.pop();
                ++pos_;
                end_pos_ = lifo_.top();
                lifo_.pop();
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

    void advance(const_iterator::difference_type n)
    {
        BOOST_ASSERT_MSG(n >= 0, "negative advance not supported!");
        for (auto i = 0; i < n; ++i)
            increment();
    }

    hierarchy_type::const_iterator pos_;
    hierarchy_type::const_iterator end_pos_;
    std::stack<hierarchy_type::const_iterator> lifo_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
    class abstract_node::const_reverse_type_iterator
:   public boost::iterator_facade
<
    const_reverse_type_iterator<T>
,   T* const
,   boost::forward_traversal_tag
,   T*
>
{
public:
    const_reverse_type_iterator()
    {}

    explicit const_reverse_type_iterator(
        const node_type node,
        bool start_at_end = false)
    :   pos_(node->children()->crbegin())
    ,   end_pos_(node->children()->crend())
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
            if ((*pos_)->children()->empty())
                ++pos_;
            else
            {
                lifo_.push(end_pos_);
                lifo_.push(pos_);
                end_pos_ = (*pos_)->children()->crend();
                pos_ = (*pos_)->children()->crbegin();
            }

            while (pos_ == end_pos_ && !lifo_.empty())
            {
                pos_ = lifo_.top();
                lifo_.pop();
                ++pos_;
                end_pos_ = lifo_.top();
                lifo_.pop();
            }
        }
    }

    T* operator->()
    {   return reinterpret_cast<T*>(*pos_);     }
    const T* operator->() const
    {   return reinterpret_cast<T*>(*pos_);     }

    void operator= (const hierarchy_type::const_reverse_iterator pos)
    {
        pos_ = pos;
        if (pos_ != end_pos_ && !dynamic_cast<T*>(*pos_))
            increment();
    }
    operator hierarchy_type::const_reverse_iterator() const
    { return pos_; }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        do
        {
            if ((*pos_)->children()->empty())
                ++pos_;
            else
            {
                lifo_.push(end_pos_);
                lifo_.push(pos_);
                end_pos_ = (*pos_)->children()->crend();
                pos_ = (*pos_)->children()->crbegin();
            }

            while (pos_ == end_pos_ && !lifo_.empty())
            {
                pos_ = lifo_.top();
                lifo_.pop();
                ++pos_;
                end_pos_ = lifo_.top();
                lifo_.pop();
            }
        } while (pos_ != end_pos_ && !dynamic_cast<T*>(*pos_));
    }

    bool equal(const_reverse_type_iterator const& other) const
    {
        return (this->pos_ == other.pos_);
    }

    T* const dereference() const
    {
        return reinterpret_cast<T*>(*pos_);
    }

    void advance(const_reverse_iterator::difference_type n)
    {
        BOOST_ASSERT_MSG(n >= 0, "negative advance not supported!");
        for (auto i = 0; i < n; ++i)
            increment();
    }

    hierarchy_type::const_reverse_iterator pos_;
    hierarchy_type::const_reverse_iterator end_pos_;
    std::stack<hierarchy_type::const_reverse_iterator> lifo_;
};

////////////////////////////////////////////////////////////////////////////////

inline abstract_node::const_iterator abstract_node::begin() const
{
    const_iterator itr(const_cast<node_type>(this));
    return itr;
}

inline abstract_node::const_reverse_iterator abstract_node::rbegin() const
{
    const_reverse_iterator itr(const_cast<node_type>(this));
    return itr;
}

inline abstract_node::const_iterator abstract_node::end() const
{
    const_iterator itr(const_cast<node_type>(this), true);
    return itr;
}

inline abstract_node::const_reverse_iterator abstract_node::rend() const
{
    const_reverse_iterator itr(const_cast<node_type>(this), true);
    return itr;
}

inline boost::iterator_range< abstract_node::const_iterator >
    abstract_node::range() const
{
    return make_iterator_range(begin(), end());
}

inline boost::iterator_range< abstract_node::const_reverse_iterator >
    abstract_node::reverse_range() const
{
    return make_iterator_range(rbegin(), rend());
}

template < typename Type >
inline abstract_node::const_type_iterator<Type> abstract_node::begin() const
{
    const_type_iterator<Type> itr(const_cast<node_type>(this));
    return itr;
}

template < typename Type >
inline abstract_node::const_reverse_type_iterator<Type>
       abstract_node::rbegin() const
{
    const_reverse_type_iterator<Type> itr(const_cast<node_type>(this));
    return itr;
}

template < typename Type >
inline abstract_node::const_type_iterator<Type> abstract_node::end() const
{
    const_type_iterator<Type> itr(const_cast<node_type>(this), true);
    return itr;
}

template < typename Type >
inline abstract_node::const_reverse_type_iterator<Type>
       abstract_node::rend() const
{
    const_reverse_type_iterator<Type> itr(const_cast<node_type>(this), true);
    return itr;
}

template < typename Type >
inline boost::iterator_range< abstract_node::const_type_iterator<Type> >
    abstract_node::range() const
{
    return make_iterator_range(begin<Type>(), end<Type>());
}

template < typename Type >
inline boost::iterator_range< abstract_node::const_reverse_type_iterator<Type> >
    abstract_node::reverse_range() const
{
    return make_iterator_range(rbegin<Type>(), rend<Type>());
}
