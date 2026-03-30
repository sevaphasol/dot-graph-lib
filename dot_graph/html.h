#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "html_attributed.h"

namespace html
{

class HTMLCell final : public html_attributed_::HTMLAttributed<HTMLCell> {
  private:
    std::string placeholder_{};

  public:
    explicit HTMLCell( std::string placeholder);

    explicit
    operator std::string() const;

  //
  // Html attributes only for cells
  //
  public:
    HTMLCell&
    setStyle( std::string value ) &;

    HTMLCell&
    setColSpan( std::uint16_t value ) &;

    HTMLCell&
    setRowSpan( std::uint16_t value ) &;
};

class HTMLRow final {
  private:
    std::vector<HTMLCell> cells_{};

  public:
    explicit
    operator std::string() const;

    HTMLCell&
    addCell( std::string placeholder) &;
};

class HTMLTable final : public html_attributed_::HTMLAttributed<HTMLCell> {
  private:
    std::vector<HTMLRow> rows_{};

  public:
    explicit
    operator std::string() const;

    HTMLRow&
    addRow() &;

  //
  // Html attributes only for tables
  //
  public:
    HTMLTable&
    setColumns( std::string value ) &;

    HTMLTable&
    setRows( std::string value ) &;

    HTMLTable&
    setStyle( std::string value ) &;
};

} // namespace html

#include "dot_graph/html.inl"
