import std.core;

import cmoon.core;

import cmoon.docs;

int main()
{
    std::cout << cmoon::html::indentation(4);
    std::cout << cmoon::docs::doc_template{};
}