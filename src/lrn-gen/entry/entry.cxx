#include <iostream>

#include <chr>
#include <fmt/printf.h>

#include <pugixml.hpp>

static chr::str RandomXml_ = "<file arg1='hello there :D'>"
                             "   <test>"
                             "   </test>"
                             "</file>";

auto LevelToTabs_(int level) -> chr::str
{
    chr::strs ss;
    for (int i = 0; i < level; i++)
        ss << "\t";
    return ss.str();
}

auto PrintNode_(const pugi::xml_node& n, int level = 0) -> void;
auto PrintNodes_(const pugi::xml_object_range<pugi::xml_node_iterator>& children, int level = 0) -> void;
auto PrintDoc_(const pugi::xml_document& n, int level = 0) -> void;

auto PrintNode_(const pugi::xml_node& n, int level) -> void
{
    auto tabs = LevelToTabs_(level);
    auto name = n.name();
    chr::strs attributes_;
    for (const auto& a : n.attributes())
    {
        if (a.hash_value()) attributes_ << fmt::format(" {0}=\"{1}\"", a.name(), a.value());
        else attributes_ << fmt::format(" {0}", a.name());
    }
    auto attributes = attributes_.str();
    auto children = n.children();

    if (!children.empty())
    {
        fmt::print("{tabs}<{name}{attributes}>\n", fmt::arg("tabs", tabs), fmt::arg("name", name),
            fmt::arg("attributes", attributes));
        PrintNodes_(children, level + 1);
        fmt::print("{tabs}</{name}>\n", fmt::arg("tabs", tabs), fmt::arg("name", name));
    }
    else
    {
        fmt::print("{tabs}<{name}{attributes}/>\n", fmt::arg("tabs", tabs), fmt::arg("name", name),
            fmt::arg("attributes", attributes));
    }
}

auto PrintNodes_(const pugi::xml_object_range<pugi::xml_node_iterator>& children, int level) -> void
{
    using namespace fmt::literals;

    for (auto& c : children)
    {
        PrintNode_(c, level);
    }
}

auto PrintDoc_(const pugi::xml_document& n, int level) -> void { PrintNodes_(n.children(), level); }

auto main() -> int
{
    pugi::xml_document doc {};
    if (!doc.load_string(RandomXml_.c_str())) throw chr::err("doc.load failed.");

    PrintDoc_(doc);

    return 0;
}