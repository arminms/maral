// Boost.Maral library (Molecular Archiving, Retrieval & Algorithm Library)
//
// Copyright (C) 2014 Armin Madadkar Sobhani
//
// Distributed under the Boost Software License Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef MARAL_POLICIES_COORDINATES_HPP
#define MARAL_POLICIES_COORDINATES_HPP

#include <vector>

#ifndef MARAL_TRAITS_HPP
#include <maral/traits.hpp>
#endif // MARAL_TRAITS_HPP

#ifndef MARAL_HAS_POLICY_HPP
#include <maral/has_policy.hpp>
#endif // MARAL_HAS_POLICY_HPP

namespace maral { namespace policy {

template <typename T>
    struct coordinates_repository
{
    coordinates_repository()
    :   ref_count_(0)
    {}

    ~coordinates_repository()
    {   frames_.clear();    }

    std::size_t ref_count_;
    std::vector<std::unique_ptr<std::vector<T>>> frames_;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Structural policy for assigning position to nodes.
///
/// \param T Type of the point to be used for the position (e.g. mtl::point3f,
/// mtl::point2d, ...).
/// \remarks
/// \b position is a structural policy class that allows assigning a position to
/// a node, so it can be accessed or changed later.

template <typename T>
    class coordinates
{
    static_assert(
        pntvec_traits<T>::extent::den > 1,
        "need a fixed-size vector type :(");

public:
/// \name Construction
//@{
    coordinates()
    {}
    //coordinates(std::size_t num = 1, std::size_t size = 10000)
    //{   add_frame(num, size);   }
    ~coordinates()
    {   frames_.clear();    }
//@}

/// \name Attributes
//@{
    static std::size_t frames_size()
    {   return frames_.size();  }

    static std::size_t coords_size()
    {   return frames_.empty() ? 0 : frames_[0]->size();  }

    static void reserve_frames_size(std::size_t size)
    {   frames_.reserve(size);  }

    static void reserve_coords_size(std::size_t size)
    {   if (!frames_.empty()) frames_[0]->reserve(size);  }
//@}

/// \name Operations
//@{
    static void add_frame(std::size_t num = 1, std::size_t size = 10000)
    {
        //if (1 == frames_.size())
        //    frames_[0]->shrink_to_fit();
        if (!frames_.empty())
            size = frames_[0]->size();
        for (std::size_t i = 0; i < num; ++i)
        {
            frames_.push_back(std::unique_ptr<std::vector<T>>
                (new std::vector<T>()));
            frames_.back()->reserve(size);
        }
    }

    static std::size_t add_coord(const T& coord)
    {
        if (frames_.empty())
            add_frame();
        frames_.front()->push_back(coord);
        return (frames_.front()->size() - 1);
    }

    static std::size_t add_coord(const T& coord, std::size_t frame)
    {
        if (frames_.empty())
            add_frame();
        frames_[frame]->push_back(coord);
        return (frames_[frame]->size() - 1);
    }

    static T& coord(std::size_t cidx)
    {   return frames_.front()->at(cidx);    }

    static T& coord(std::size_t cidx, std::size_t fidx)
    {   return frames_[fidx]->at(cidx);     }

    //static void set_coord(const T& coord, std::size_t cidx)
    //{   frames_.back()->at(cidx) = coord;   }

    //static void set_coord(const T& coord, std::size_t cidx, std::size_t fidx)
    //{   frames_[fidx]->at(cidx) = coord;    }

    static void clear_frames()
    {   frames_.clear();    }
//@}

// Implementation
private:
    static std::vector<std::unique_ptr<std::vector<T>>> frames_;
};

template <typename T>
    std::vector<std::unique_ptr<std::vector<T>>> coordinates<T>::frames_;

}   // namespace policy

GENERATE_HAS_POLICY(coordinates)   // creates has_policy_coordinates

}    // namespace maral

#endif    // MARAL_POLICIES_COORDINATES_HPP

