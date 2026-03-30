#pragma once

#include <sstream>
#include <string>
#include <utility>

#include "dot_graph/graph.h"

namespace dot_graph {

namespace detail {

inline void
indent( std::ostream& os, std::size_t width )
{
    for ( std::size_t i = 0; i < width; ++i )
    {
        os << ' ';
    }
}

} // namespace detail

inline void
Attributes::Entry::write( std::ostream& os, std::size_t width ) const
{
    detail::indent( os, width );

    os << key << '=';

    switch ( kind )
    {
        case Attributes::ValueKind::QUOTED:
            os << '"' << value << '"';
            break;
        case Attributes::ValueKind::RAW:
            os << value;
            break;
        case Attributes::ValueKind::HTML:
            os << '<' << value << '>';
            break;
    }
}

inline Attributes::Entry&
Attributes::upsert( std::string_view key )
{
    for ( auto& entry : entries_ )
    {
        if ( entry.key == key )
        {
            return entry;
        }
    }

    entries_.push_back( Entry{ std::string( key ), {}, {} } );
    return entries_.back();
}

inline Attributes&
Attributes::set( std::string_view key, std::string_view value, ValueKind kind )
{
    auto& entry = upsert( key );
    entry.value = std::string( value );
    entry.kind  = kind;
    return *this;
}

inline Attributes&
Attributes::setQuoted( std::string_view key, std::string_view value ) &
{
    return set( key, value, ValueKind::QUOTED );
}

inline Attributes&
Attributes::setRaw( std::string_view key, std::string_view value ) &
{
    return set( key, value, ValueKind::RAW );
}

inline Attributes&
Attributes::setHtml( std::string_view key, std::string_view value ) &
{
    return set( key, value, ValueKind::HTML );
}

inline Attributes&
Attributes::setBool( std::string_view key, bool value ) &
{
    auto& entry = upsert( key );
    entry.value = value ? "true" : "false";
    entry.kind  = ValueKind::RAW;
    return *this;
}

inline Attributes&
Attributes::setQuotedLabel( std::string_view value ) &
{
    return setQuoted( "label", value );
}

inline Attributes&
Attributes::setHtmlLabel( std::string_view value ) &
{
    return setHtml( "label", value );
}

inline Attributes&
Attributes::setColor( std::string_view value ) &
{
    return setQuoted( "color", value );
}

inline Attributes&
Attributes::setFillColor( std::string_view value ) &
{
    return setQuoted( "fillcolor", value );
}

inline Attributes&
Attributes::setFontColor( std::string_view value ) &
{
    return setQuoted( "fontcolor", value );
}

inline Attributes&
Attributes::setFontName( std::string_view value ) &
{
    return setQuoted( "fontname", value );
}

inline Attributes&
Attributes::setFontSize( std::size_t value ) &
{
    return setRaw( "fontsize", std::to_string( value ) );
}

inline Attributes&
Attributes::setShape( std::string_view value ) &
{
    return setQuoted( "shape", value );
}

inline Attributes&
Attributes::setStyle( std::string_view value ) &
{
    return setQuoted( "style", value );
}

inline Attributes&
Attributes::setPenWidth( std::size_t value ) &
{
    return setRaw( "penwidth", std::to_string( value ) );
}

inline Attributes&
Attributes::setWeight( std::size_t value ) &
{
    return setRaw( "weight", std::to_string( value ) );
}

inline Attributes&
Attributes::setConstraint( bool value ) &
{
    return setBool( "constraint", value );
}

inline bool
Attributes::empty() const
{
    return entries_.empty();
}

inline const std::vector<Attributes::Entry>&
Attributes::entries() const &
{
    return entries_;
}

inline void
Attributes::write( std::ostream& os, std::size_t width ) const
{
    detail::indent( os, width );

    os << '[';

    bool first = true;
    for ( const auto& entry : entries_ )
    {
        if ( !first )
        {
            os << ", ";
        }
        first = false;

        entry.write( os );
    }

    os << ']';
}

inline
Node::Node( std::string id ) : id_( std::move( id ) ) {}

inline const std::string&
Node::id() const &
{
    return id_;
}

inline void
Node::write( std::ostream& os, std::size_t width ) const
{
    detail::indent( os, width );

    os << id_;
    if ( !attributes_.empty() )
    {
        os << ' ';
        attributes_.write( os );
    }
    os << ";\n";
}

inline
Edge::Edge( std::string from, std::string to )
    : from_( std::move( from ) ), to_( std::move( to ) )
{
}

inline const std::string&
Edge::from() const &
{
    return from_;
}

inline const std::string&
Edge::to() const &
{
    return to_;
}

inline void
Edge::write( std::ostream& os, [[maybe_unused]] std::size_t width ) const
{
    os << from_ << " -> " << to_;
    if ( !attributes_.empty() )
    {
        os << ' ';
        attributes_.write( os );
    }
    os << ";\n";
}

inline Subgraph::Subgraph( std::string id ) : id_( std::move( id ) ) {}

inline const std::string&
Subgraph::id() const &
{
    return id_;
}

inline Subgraph&
Subgraph::addSubgraph( std::string id ) &
{
    subgraphs_.push_back( Subgraph( std::move( id ) ) );
    return subgraphs_.back();
}

inline Node&
Subgraph::addNode( std::string id ) &
{
    nodes_.push_back( Node( std::move( id) ) );
    return nodes_.back();
}

inline const std::vector<Subgraph>&
Subgraph::subgraphs() const &
{
    return subgraphs_;
}

inline const std::vector<Node>&
Subgraph::nodes() const &
{
    return nodes_;
}

inline void
Subgraph::write( std::ostream& os, std::size_t width ) const
{
    detail::indent( os, width );
    os << "subgraph " << id_ << " {\n";

    for ( const auto& entry : attributes_.entries() )
    {
        entry.write( os, width + 2 );
        os << ";\n";
    }

    for ( const auto& nested_subgraph : subgraphs_ )
    {
        nested_subgraph.write( os, width + 2 );
    }

    for ( const auto& node : nodes_ )
    {
        node.write( os, width + 2 );
    }

    detail::indent( os, width );
    os << "}\n";
}

inline Graph::Graph( std::string id ) : id_( std::move( id ) ) {}

inline Attributes&
Graph::graphAttributes()
{
    return graph_attributes_;
}

inline Attributes&
Graph::nodeAttributes()
{
    return node_attributes_;
}

inline Attributes&
Graph::edgeAttributes()
{
    return edge_attributes_;
}

inline Subgraph&
Graph::addSubgraph( std::string id )
{
    subgraphs_.push_back( Subgraph( std::move( id) ) );
    return subgraphs_.back();
}

inline Node&
Graph::addNode( std::string id )
{
    nodes_.push_back( Node( std::move( id ) ) );
    return nodes_.back();
}

inline Edge&
Graph::addEdge( std::string from, std::string to )
{
    edges_.push_back( Edge( std::move( from), std::move( to ) ) );
    return edges_.back();
}

inline Graph::
operator std::string() const
{
    std::ostringstream os;

    os << "digraph \"" << id_ << "\" {\n";

    if ( !graph_attributes_.empty() )
    {
        detail::indent( os, 2 );
        os << "graph ";
        graph_attributes_.write( os );
        os << ";\n";
    }

    if ( !node_attributes_.empty() )
    {
        detail::indent( os, 2 );
        os << "node ";
        node_attributes_.write( os );
        os << ";\n";
    }

    if ( !edge_attributes_.empty() )
    {
        detail::indent( os, 2 );
        os << "edge ";
        edge_attributes_.write( os );
        os << ";\n";
    }

    for ( const auto& subgraph : subgraphs_ )
    {
        subgraph.write( os );
    }

    for ( const auto& node : nodes_ )
    {
        node.write( os );
    }

    for ( const auto& edge : edges_ )
    {
        edge.write( os );
    }

    os << "}\n";

    return os.str();
}

inline void
Graph::translateWithDot( const std::string& filename,
                         const std::string& out_type) const
{
    std::string cmd = "dot -T" + out_type + " -o " + filename;

    FILE* pipe = popen( cmd.c_str(), "w" );
    if ( !pipe )
    {
        throw std::runtime_error( "Failed to open pipe" );
    }

    std::string dot_graph_str = static_cast<std::string>( *this);

    std::fwrite( dot_graph_str.c_str(), 1, dot_graph_str.size(), pipe );

    int status = pclose( pipe );
    if ( status != 0 )
    {
        throw std::runtime_error( "Graphviz rendering failed" );
    }
}

template<typename TOutStream>
TOutStream&
operator<<( TOutStream& os, const Graph& graph )
{
    return os << static_cast<std::string>( graph );
}

} // namespace dot_graph
