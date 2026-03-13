#pragma once

#include <string>
#include <vector>
#include <cassert>

namespace html
{

enum class AlignValue
{
    CENTER,
    LEFT,
    RIGHT
};

enum class VAlignValue
{
    MIDDLE,
    BOTTOM,
    TOP,
};

namespace html_attributed_
{

template<typename Derived>
class HTMLAttributed
{
  protected:
    struct HTMLAttr {
        HTMLAttr( std::string key,
                  std::string value)
         :  key( key ),
            value( value )
        {
        }

        std::string key;
        std::string value;
    };

    std::vector<HTMLAttr> attributes_;

  public:
    Derived&
    setAligned( AlignValue value ) &
    {
        switch ( value )
        {
            case AlignValue::CENTER: { attributes_.emplace_back( HTMLAttr( "ALIGN", "CENTER" ) ); break; }
            case AlignValue::LEFT:   { attributes_.emplace_back( HTMLAttr( "ALIGN",   "LEFT" ) ); break; }
            case AlignValue::RIGHT:  { attributes_.emplace_back( HTMLAttr( "ALIGN",  "RIGHT" ) ); break; }
        }
        return static_cast<Derived&>( *this );
    }

    Derived&
    setBGColor( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr(  "BGCOLOR", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setBorder( uint8_t value ) &
    {
        attributes_.emplace_back( HTMLAttr( "BORDER", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setCellBorder( uint8_t value ) &
    {
        assert( value < 128 );
        attributes_.emplace_back( HTMLAttr( "CELLBORDER", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setCellSpacing( uint8_t value ) &
    {
        assert( value < 128 );
        attributes_.emplace_back( HTMLAttr( "CELLSPACING", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setColor( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "COLOR", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setFixedSize( bool value ) &
    {
        attributes_.emplace_back( HTMLAttr( "FIXEDSIZE", (value ? "TRUE" : "FALSE") ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setGradientAngle( uint32_t value ) &
    {
        assert( value <= 360 );
        attributes_.emplace_back( HTMLAttr( "GRADIENTANGLE", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setHeight( uint16_t value ) &
    {
        attributes_.emplace_back( HTMLAttr( "HEIGHT", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setHREF( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "HREF", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setID( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "ID", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setPort( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "PORT", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setSides( std::string value ) &
    {
        for ( char c : value )
        {
            assert( c == 'L' || c == 'R' || c == 'T' || c == 'B' );
        }

        attributes_.emplace_back( HTMLAttr( "SIDES", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setTarget( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "TARGET", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setTitle( std::string value ) &
    {
        attributes_.emplace_back( HTMLAttr( "TITLE", std::move( value ) ) );
        return static_cast<Derived&>( *this );
    }

    Derived&
    setTooltip( std::string value ) &
    {
        return setTitle( std::move( value ) ); // Alias for title
    }

    Derived&
    setVAlign( VAlignValue value ) &
    {
        switch ( value )
        {
            case VAlignValue::MIDDLE: { attributes_.emplace_back( HTMLAttr( "VALIGN", "MIDDLE" ) ); break; }
            case VAlignValue::BOTTOM: { attributes_.emplace_back( HTMLAttr( "VALIGN", "BOTTOM" ) ); break; }
            case VAlignValue::TOP:    { attributes_.emplace_back( HTMLAttr( "VALIGN",    "TOP" ) ); break; }
        }
        return static_cast<Derived&>( *this );
    }

    Derived&
    setWidth( uint16_t value ) &
    {
        attributes_.emplace_back( HTMLAttr( "WIDTH", std::to_string( value ) ) );
        return static_cast<Derived&>( *this );
    }
};

} // namespace html_attributed_
} // namespace html
