#pragma once
// Copyright (c) 2014 Alf P. Steinbach.

#include <thisApp/model/card/Id.h>                      // card::Id
#include <thisApp/support/With_relops_from_compare_.h>  // cppx::With_relops_from_compare_

namespace view{
    using cppx::With_relops_from_compare_;

    class Card_image_id
        : public With_relops_from_compare_<Card_image_id>
    {
    private:
        bool            is_backside_;
        union Id_union
        {
            card::Id        card;
            int             back_image;

            Id_union( card::Id const id ): card( id ) {}
            Id_union( int const id ): back_image( id ) {}
        }               id_;

    public:
        auto is_backside() const        -> bool { return is_backside_; }
        auto is_frontside() const       -> bool { return !is_backside_; }

        auto back_image_id() const
            -> int
        {
            assert( is_backside() );
            return id_.back_image;
        }

        auto card_id() const
            -> card::Id
        {
            assert( is_frontside() );
            return id_.card;
        }

        friend
        auto compare( Card_image_id const a, Card_image_id const b )
            -> int
        {
            if( int const x = a.is_backside_ - b.is_backside_ )
            {
                return x;
            }
            return (0?0
                : a.is_backside_? a.id_.back_image - b.id_.back_image
                : compare( a.id_.card, b.id_.card )
                );
        }

        Card_image_id( int const back_image_id = 0 )
            : is_backside_( true )
            , id_( back_image_id )
        {}

        Card_image_id( card::Id const card_id )
            : is_backside_( false )
            , id_( card_id )
        {}
    };

}  // namespace view
