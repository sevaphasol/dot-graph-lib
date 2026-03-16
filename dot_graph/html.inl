#pragma once

#include <string>
#include <vector>
#include <cassert>

#include "dot_graph/html.h"

namespace html
{

//
// Cell
//

HTMLCell::HTMLCell( std::string placeholder )
 :  placeholder_( placeholder )
{
}

HTMLCell::
operator std::string() const
{
    std::string output( "        <TD" );
    if ( !attributes_.empty() )
    {
        output += "\n";
        for ( const auto& attr : attributes_ )
        {
            output += "            " + attr.key + "=\"" + attr.value + "\"\n";
        }
        output += "        >\n";
    } else
    {
        output += ">";
    }

    if ( !attributes_.empty() )
    {
        output += "        " + placeholder_;
        output += "\n        </TD>";
    } else
    {
        output += placeholder_;
        output += "</TD>";
    }
    return output;
}

HTMLCell&
HTMLCell::setStyle( std::string value ) &
{
    assert( value == "RADIAL" );
    attributes_.emplace_back( HTMLAttr( "STYLE", std::move( value ) ) );
    return *this;
}

HTMLCell&
HTMLCell::setColSpan( uint16_t value ) &
{
    attributes_.emplace_back( HTMLAttr( "COLSPAN", std::to_string( value ) ) );
    return *this;
}

HTMLCell&
HTMLCell::setRowSpan( uint16_t value ) &
{
    attributes_.emplace_back( HTMLAttr( "ROWSPAN", std::to_string( value ) ) );
    return *this;
}

//
// Row
//

HTMLRow::
operator std::string() const
{
    std::string output( "    <TR>\n" );
    for ( const auto& cell : cells_ )
    {
        output += static_cast<std::string>( cell ) + "\n";
    }
    output += "    </TR>";
    return output;
}

HTMLCell&
HTMLRow::addCell( std::string placeholder) &
{
    cells_.emplace_back( HTMLCell( placeholder ) );
    return cells_.back();
}

//
// Table
//

HTMLTable::
operator std::string() const
{
    std::string output( "<TABLE" );
    if ( !attributes_.empty() )
    {
        output += '\n';
        for ( const auto& attr : attributes_ )
        {
            output += attr.key + "=\"" + attr.value + "\"\n";
        }
    }
    output += ">\n";

    for ( const auto& row : rows_ )
    {
        output += static_cast<std::string>( row ) + "\n";
    }

    output += "</TABLE>\n";
    return output;
}

HTMLRow&
HTMLTable::addRow() &
{
    rows_.emplace_back( HTMLRow() );
    return rows_.back();
}

HTMLTable&
HTMLTable::setColumns( std::string value ) &
{
    assert( value == "*" ); // The only legal value for this
    attributes_.emplace_back( HTMLAttr( "COLUMNS", std::move( value ) ) );
    return *this;
}

HTMLTable&
HTMLTable::setRows( std::string value ) &
{
    assert( value == "*" ); // The only legal value for this
    attributes_.emplace_back( HTMLAttr( "ROWS", std::move( value ) ) );
    return *this;
}

HTMLTable&
HTMLTable::setStyle( std::string value ) &
{
    assert( value == "RADIAL" || value == "ROUNDED" );
    attributes_.emplace_back( HTMLAttr( "STYLE", std::move( value ) ) );
    return *this;
}

} // namespace html
